#include "../include/highway.hpp"

Highway::Highway(int lanes, int lenght, int maximumSpeed, double slowDownLikelyhood, bool changeLanesOn){
    this->slowDownLikelyhood = slowDownLikelyhood;
    this->maximumSpeed = maximumSpeed;
    this->lanes = lanes;
    this->lenght = lenght;
    this->changeLanesOn = changeLanesOn;

    srand(time(NULL)); // seed for rand
    
    try{
        this->highway = new Car**[this->lanes];
        for (int i = 0; i < this->lanes; i++){
            this->highway[i] = new Car*[this->lenght];
        }
        for (int i = 0; i < this->lanes; i++)
            for (int j = 0; j < this->lenght; j++)
                this->highway[i][j] = nullptr;  
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n.";
        exit(EXIT_FAILURE);
    }
}

void Highway::generateCars(){
    for (int i = 0; i < this->lanes; i++){
        int rand = std::rand() % 100;
        if (rand > (-5)*(i - this->lanes)){
            if (this->highway[i][0] == nullptr){
                this->highway[i][0] = new Car(this, this->maximumSpeed - 1);
            }
        }
    }
}

void Highway::applyRules(){
    for (int j = 0; j < this->lenght; j++){
        for (int i = 0; i < this->lanes; i++){
            if (this->highway[i][j] != nullptr){
                this->highway[i][j]->setDanger(false);
                int distance = this->ruleOne(i, j);
                if (changeLanesOn)
                    if (this->ruleTwo(i, j)){
                        // all rules must apply to this position, even after changing lanes
                        i = this->ruleThree(i, j, distance);
                    }
                this->ruleSeven(i, j);
                this->ruleEight(i, j, this->slowDownLikelyhood);
            }
        }
    }
    // move
    for (int j = this->lenght - 1; j >= 0; j--){
        for (int i = 0; i < this->lanes; i++){
            if (this->highway[i][j] != nullptr){
                this->ruleNine(i, j);
            }
        }
    }
}

/**
 * @brief Increase speed if possible.
 * 
 */
int Highway::ruleOne(int i, int j){ 
    int speed = this->highway[i][j]->getSpeed();
    // check area in from of the car
    for (int area = 1; area < speed + 1 && j + area < this->lenght; area++){
        if (this->highway[i][j+area] != nullptr){
            this->highway[i][j]->setDanger(true);
            return area;
        }                    
    }
    if (speed >= this->maximumSpeed)
        return 0;
    this->highway[i][j]->setSpeed(speed+1);
    return 0;
}

/**
 * @brief Check danger.
 * 
 * @return true if car is in danger, proceed to rule three
 * @return false if no danger imminent, proceed to rule sevem
 */
bool Highway::ruleTwo(int i, int j){
    return this->highway[i][j]->getDangerStatus();
}

int Highway::ruleThree(int i, int j, int distance){  
    if (i == 0){
        if (this->highway[i+1][j] != nullptr)
            return i;
        else {
            if (this->ruleFour(i+1, j, distance))
                if (this->ruleFive(i+1, j)){
                    //ruleSix
                    this->highway[i+1][j] = this->highway[i][j];
                    this->highway[i][j] = nullptr; 
                    return i + 1;      
                }
        }
    }
    else if (i == this->lanes-1){
        if (this->highway[i-1][j] != nullptr)
            return i;
        else{
            if (this->ruleFour(i-1, j, distance))
                if (this->ruleFive(i-1, j)){
                    // ruleSix
                    this->highway[i-1][j] = this->highway[i][j];
                    this->highway[i][j] = nullptr;
                    return i - 1;
                }
        }
    }
    else{
        if (this->highway[i-1][j] != nullptr && this->highway[i+1][j] != nullptr)
            return i;

        //check "left" side (i - 1)
        if (this->highway[i-1][j] != nullptr)
            if (this->ruleFour(i-1, j, distance))
                if (this->ruleFive(i-1, j)){
                    // ruleSix
                    this->highway[i-1][j] = this->highway[i][j];
                    this->highway[i][j] = nullptr;  
                    return i - 1; 
                }
        //check "right" side (i + 1)
        else if (this->highway[i+1][j] != nullptr)
            if (this->ruleFour(i+1, j, distance))
                if (this->ruleFive(i+1, j)){
                    //ruleSix
                    this->highway[i+1][j] = this->highway[i][j];
                    this->highway[i][j] = nullptr;  
                    return i + 1;   
                }
    }
    return i;
}

bool Highway::ruleFour(int i, int j, int originalDistance){
    for (int safeDistance = 1; safeDistance < originalDistance && j + safeDistance < this->lenght; safeDistance++){
        if (this->highway[i][j+safeDistance] != nullptr)
            return false;
    }
    return true;
}

bool Highway::ruleFive(int i, int j){
    for (int backView = 1; backView < this->maximumSpeed && j - backView > 0; backView++){
        if (this->highway[i][j-backView] != nullptr){
            int backCarSpeed = this->highway[i][j-backView]->getSpeed();
            if (backCarSpeed - backView >= 0){  // j - backView + backCarSpeed >= j
                return false;
            }
            else return true;
        }
    }
    return true;
}

void Highway::ruleSeven(int i, int j){
    int speed = this->highway[i][j]->getSpeed();
    // check area in from of the car
    for (int area = 1; area <= speed  && j + area < this->lenght; area++){
        if (this->highway[i][j+area] != nullptr){
            this->highway[i][j]->setSpeed(area-1);     
        }                    
    }
}

void Highway::ruleEight(int i, int j, double slowDownLikelyhood){
    double rand = std::rand() % 100;
    if (rand < this->slowDownLikelyhood){
        int speed = this->highway[i][j]->getSpeed();
        if (speed > 0)
            this->highway[i][j]->setSpeed(speed - 1);
    }
}

void Highway::ruleNine(int i, int j){
    int speed  = this->highway[i][j]->getSpeed();
    if (j + speed > this->lenght){
        delete [] this->highway[i][j];
        this->highway[i][j] = nullptr;
    }   
    else{
        if (speed != 0){
            this->highway[i][j+speed] = this->highway[i][j];
            this->highway[i][j] = nullptr;
        }
    }
}

void Highway::printHighway(){
    for (int i = 0; i < this->lanes; i++){
        for (int j = 0; j < this->lenght; j++){
            Car *point = this->highway[i][j];
            if (point == nullptr){ 
                std::cout << '.';
                continue;
            }
            std::cout << point->getSpeed();
        }
        std::cout << "\n";
    }       
    std::cout << "\n";
}

void Highway::clearMemory(){
     for (int i = 0; i < this->lanes; i++){
        for (int j = 0; j < this->lenght; j++){
            if (this->highway[i][j] != nullptr)
                delete [] this->highway[i][j]; 
        }
        delete [] this->highway[i];
     }
     delete [] this->highway;
}

int Highway::getLanes(){
    return this->lanes;
}

int Highway::getLenght(){
    return this->lenght;
}
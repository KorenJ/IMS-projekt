#include "../include/highway.hpp"

Highway::Highway(int lanes, int lenght){
    this->lanes = lanes;
    this->lenght = lenght;
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
};

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
};

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
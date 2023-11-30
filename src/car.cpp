#include "../include/highway.hpp"

Car::Car(Highway* highway, int speed){
    this->highway = highway;
    this->speed = speed;
}

void Car::setDanger(bool status){
    this->danger = status;
}

bool Car::getDangerStatus(){
    return this->danger;
}

void Car::setSpeed(int newSpeed){
    this->speed = newSpeed;
}

int Car::getSpeed(){
    return this->speed;
}
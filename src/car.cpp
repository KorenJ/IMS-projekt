#include "../include/highway.hpp"

Car::Car(Highway* highway, int speed){
    this->highway = highway;
    this->speed = speed;
}

int Car::getSpeed(){
    return this->speed;
}
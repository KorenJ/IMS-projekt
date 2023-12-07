/**
 * file for Car params
 * @author Jakub Kořínek (xkorin17), Martin Benovič (xbenov00)
 */

#include "../include/highway.hpp"

Car::Car(Highway* highway, int speed){
    this->highway = highway;
    this->speed = speed;
    this->stopTime = 0;
    this->noted = false;
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

int Car::getStopTime(){
    return this->stopTime;
}

void Car::setStopTime(int value){
    this->stopTime = value;
}

bool Car::isNoted(){
    return this->noted;
}

void Car::noteCar(){
    this->noted = true;
}

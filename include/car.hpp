#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>

class Highway;

#include "highway.hpp"

class Car{
    private:
        int speed;
        bool danger;
        Highway* highway;

    public:
        Car(Highway* highway, int speed);
        void setDanger(bool status);
        bool getDangerStatus();
        int getSpeed();
        void setSpeed(int newSpeed);
};

#endif
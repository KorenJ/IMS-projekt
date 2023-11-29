#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>

class Highway;

#include "highway.hpp"

class Car{
    private:
        int speed;
        Highway* highway;

    public:
        Car(Highway* highway, int speed);
        int getSpeed();
};

#endif
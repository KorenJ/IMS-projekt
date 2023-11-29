#ifndef HIGHWAY_HPP
#define HIGHWAY_HPP

#include <iostream>
#include <string>

#include "car.hpp"

class Highway{
    private:   
        Car*** highway;
        int lanes;
        int lenght;

    public:
        Highway(int lanes, int lenght);
        void printHighway();
        void clearMemory();
        int getLanes();
        int getLenght();
};

#endif
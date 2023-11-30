#ifndef HIGHWAY_HPP
#define HIGHWAY_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "car.hpp"

class Highway{
    private:   
        Car*** highway;
        int lanes;
        int lenght;
        int maximumSpeed;
        double slowDownLikelyhood;
        bool changeLanesOn;

    public:
        Highway(int lanes, int lenght, int maximumSpeed, double slowDownLikelyhood, bool changeLanesOn);

        void generateCars();

        void applyRules();
        int ruleOne(int i, int j);
        bool ruleTwo(int i, int j);
        int ruleThree(int i, int j, int distance);
        bool ruleFour(int i, int j, int originalDistance);
        bool ruleFive(int i, int j);
        // void ruleSix(int i, int j);
        void ruleSeven(int i, int j);
        void ruleEight(int i, int j, double slowDownLikelyhood);
        void ruleNine(int i, int j);

        void printHighway();
        void clearMemory();
        int getLanes();
        int getLenght();
};

#endif
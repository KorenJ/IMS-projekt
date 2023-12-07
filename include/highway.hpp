/**
 * header file for Highway initialization
 * @author Jakub Kořínek (xkorin17), Martin Benovič (xbenov00)
 */

#ifndef HIGHWAY_HPP
#define HIGHWAY_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "car.hpp"

#define accidentTime 30

#define logPlace 50

class Highway{
    private:   
        Car*** highway;
        int lanes;
        int lenght;
        int maximumSpeed;
        double slowDownLikelyhood;
        double accidentLikelyhood;
        bool changeLanesOn;
        double traffic;
        double avgSpeed;

        int carFlow;

    public:
        Highway(int lanes, int lenght, int maximumSpeed, double slowDownLikelyhood, double accidentLikelyhood, bool changeLanesOn, double traffic);

        void generateCars();

        double applyRules();
        int ruleOne(int i, int j);
        bool ruleTwo(int i, int j);
        int ruleThree(int i, int j, int distance);
        bool ruleFour(int i, int j, int originalDistance);
        bool ruleFive(int i, int j);
        // void ruleSix(int i, int j);
        void ruleSeven(int i, int j);
        void ruleEight(int i, int j, double slowDownLikelyhood);
        void ruleEight2(int i, int j, double accidentLikelyhood);
        void ruleNine(int i, int j);
        void handleLogs();
        void printHighway();
        void clearMemory();
        int getLanes();
        int getLenght();
        int getCarFlow();
};

#endif

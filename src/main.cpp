/**
 * main file
 * @author Jakub Kořínek (xkorin17), Martin Benovič (xbenov00)
 */

#include "../include/highway.hpp"
#include <vector>
#include <thread>
#include <chrono>

#define HighwayLenght 150
#define defaultLanes 2
#define defaultVelocity 5
#define defaultSlowdownLikelyhood 20.0
#define defaultAccidentLikelyhood 0.0
#define defaultSpeedofSim 200
#define defaultTraffic 0.3
#define cycles 100

void printHelp(){
    std::cout << "Usage:\n" 
              << "./ims [-l lanes] [-p traffic] [-s slowdown] [-a accident] [-g speed of simulation] [-v velocity] [-c]\n"
              << "Lanes define number of highway lanes. Max 5.\n"
              << "Traffic defines chosen density. (0 <= p <= 1)\n"
              << "Slowdown defines the propability of a driver randomly slowing down (simulates human error in traffic), in %. Max 80.\n"
              << "Accident defines the probability of an accident occuring to each car, in ‰. Max 10.\n"
              << "Speed of simulation in miliseconds.\n"
              << "Velocity defines car's velocity in simulation. 1 repesents 25km/h, that is 1cell/tick. Max 9.\n"
              << "-c flag turns off the ability of drivers to change lanes.\n";
}

int main(int argc, char **argv){

    int lanes = defaultLanes;
    double traffic = defaultTraffic;
    double slowdownLikelyhood = defaultSlowdownLikelyhood;
    double accidentLikelyhood = defaultAccidentLikelyhood;
    int speedOfSim = defaultSpeedofSim;
    int lenght = HighwayLenght;
    int velocity = defaultVelocity;
    bool changeLanesOn = true; 
    bool logMode = false;

    std::vector<std::string> args;
    for (int i=1; i<argc; i++){
        args.push_back(argv[i]);
    }

    for (std::string arg : args){
        if (arg == "-h" || arg == "--help"){
            printHelp();
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < args.size(); i++){
        if (args[i] == "-l"){
            lanes = stoi(args[++i]);
            if (lanes > 5) lanes = 5;
            if (lanes < 1) lanes = 1;
        }
        else if (args[i] == "-c"){
            changeLanesOn = false;
        }
        else if (args[i] == "-p"){
            traffic = stod(args[++i]);
            if (traffic > 1) traffic = 1.0;
            if (traffic < 0) traffic = 0.0;
        }
        else if (args[i] == "-s"){
            slowdownLikelyhood = stod(args[++i]);
            if (slowdownLikelyhood > 80) slowdownLikelyhood = 80.0;
            if (slowdownLikelyhood < 0) slowdownLikelyhood = 0.0;
        }
        else if (args[i] == "-a"){
            accidentLikelyhood = stod(args[++i]);
            if (accidentLikelyhood > 10) accidentLikelyhood = 10.0;
            if (accidentLikelyhood < 0) accidentLikelyhood = 0.0;
        }
        else if (args[i] == "-g"){
            speedOfSim = stoi(args[++i]);
        }
        else if (args[i] == "-v"){
            velocity = stoi(args[++i]);
            if (velocity < 1) velocity = 1;
            if (velocity > 9) velocity = 9;
        }
        else if (args[i] == "--log"){
            logMode = true;
        }
        else{
            printHelp();
            exit(EXIT_SUCCESS);
        } 
    }

    int cycle = 1;
    double speedAll = 0.0;
    double avgSpeed = 0.0;
    char flowValue[1024];

    if (logMode){
        FILE *speed;
        FILE *flow;
        speed = fopen("output/speed.txt", "w");
        flow = fopen("output/flow.txt", "w");
        for (double tr = 0; tr <= 1; tr = tr + 0.001){
            Highway *highway = new Highway(lanes, lenght, velocity, slowdownLikelyhood, accidentLikelyhood, changeLanesOn, tr);
            while (cycle++ != cycles){
                speedAll += highway->applyRules();
                highway->generateCars();
            }
            avgSpeed = speedAll/cycles;

            fprintf(speed, "%.2f ", avgSpeed);
            fprintf(flow, "%d ", highway->getCarFlow());

            highway->clearMemory();
            delete highway;
            cycle = 1;
            avgSpeed = 0.0;
            speedAll = 0.0;
        }
        fclose(speed);
        fclose(flow);
    }
    else{
        Highway *highway = new Highway(lanes, lenght, velocity, slowdownLikelyhood, accidentLikelyhood, changeLanesOn, traffic);
        highway->printHighway();
        while (cycle++ != cycles){
            std::this_thread::sleep_for(std::chrono::milliseconds(speedOfSim));
            highway->applyRules();
            highway->generateCars();
            highway->printHighway();
        }
        highway->clearMemory();
        delete highway;
    }    

    return EXIT_SUCCESS;
}

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
#define defaultTraffic "M"

void printHelp(){
    std::cout << "Usage:\n" 
              << "./ims [-l lanes] [-p traffic] [-s slowdown] [-a accident] [-g speed of simulation] [-v velocity] [-c]\n"
              << "Lanes define number of highway lanes. Max 5.\n"
              << "Traffic defines how heavy traffic is, choose from L (low), M (medium), H (high), E (extreme).\n"
              << "Slowdown defines the propability of a driver randomly slowing down (simulates human error in traffic), in %. Max 80.\n"
              << "Accident defines the probability of an accident occuring to each car, in ‰. Max 10.\n"
              << "Speed of simulation in miliseconds.\n"
              << "Velocity defines car's velocity in simulation. 1 repesents 25km/h, that is 1cell/tick. Max 9.\n"
              << "-c flag turns off the ability of drivers to change lanes.\n";
}

int main(int argc, char **argv){

    int lanes = defaultLanes;
    std::string traffic = defaultTraffic;
    double slowdownLikelyhood = defaultSlowdownLikelyhood;
    double accidentLikelyhood = defaultAccidentLikelyhood;
    int speedOfSim = defaultSpeedofSim;
    int lenght = HighwayLenght;
    int velocity = defaultVelocity;
    bool changeLanesOn = true; 

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
            traffic = args[++i];
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
        else{
            printHelp();
            exit(EXIT_SUCCESS);
        } 
    }

    Highway *highway = new Highway(lanes, lenght, velocity, slowdownLikelyhood, accidentLikelyhood, changeLanesOn);

    highway->printHighway();

    int cycle = 1;
    while (cycle++){
        std::this_thread::sleep_for(std::chrono::milliseconds(speedOfSim));
        highway->applyRules();
        highway->generateCars();
        highway->printHighway();
    }    
        
    highway->clearMemory();

    return EXIT_SUCCESS;
}
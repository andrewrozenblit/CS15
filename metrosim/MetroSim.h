/*
 *  MetroSim.h
 *  Andrew Rozenblit 
 *  02/14/24
 *
 *  CS 15 Project 1 MetroSimulation
 *
 *  Purpose: Interface of the Simulation 
 *
 */
#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"

// Put any other necessary includes here
#include <fstream>
#include "PassengerQueue.h"
#include <list>
#include <vector>
#include <sstream>
#include <string>

// Put any other structs you need here

class MetroSim
{
public:
    //method that runs the simulation 
    void prompt_and_execute(int argc, char *argv[]);
private:
    //private helper functions
    void createStations(char *filename);
    void printStations(int currstation);
    std::string figureInput(bool file, std::istream &infile);
    std::string processInput(std::istream &infile);
    void printPassengersOnTrain(int stationNum);
    void newPassenger(int passCount, std::string input);
    void moveStation(int stationNum, std::ostream &output);
    void simLoop(std::istream &instream, std::ostream &output);
    void putOnTrain(int stationNum);
    void takingOffTrain(int stationNum, std::ostream &output);
    
    //struct to represent each station 
    struct Station {
        std::string name; //name of the station
        int id; //station id 
        //queue of passengers getting off at this station
        PassengerQueue gettingOff; 
        //queue of passengers getting on at this station
        PassengerQueue queued;
    };
    //vector of all stations 
    std::vector<Station> stations;

};

#endif

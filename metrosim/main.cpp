/*
 *  main.cpp
 *  Andrew Rozenblit 
 *  02/14/24
 *
 *  CS 15 Project 1 MetroSimulation
 *
 *  Purpose: driver of the simulation 
 *
 */
#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

/*
 * name:      main
 * purpose:   acts as a driver for the MetroSim simulation prorgam 
 * arguments: an int, argc, storing the total amount of arguments the user 
 *            passed in when running the executable, a char pointer argv 
 *            storing the names of things that the user is passing in when 
 *            running the executable 
 * returns:   returns 0
 * effects:   begins the simulation 
 */
int main(int argc, char *argv[])
{
   //if not enough arguments provuded
   if (argc < 3) {
      cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]\n";
      exit(EXIT_FAILURE);
   }
   //create the instance 
   MetroSim train;
   //run the simulation
   train.prompt_and_execute(argc,argv);
   return 0;       
}

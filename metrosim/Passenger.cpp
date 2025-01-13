/*
 *  Passenger.cpp
 *  Andrew Rozenblit 
 *  02/11/24
 *
 *  CS 15 Project 1 - MetroSim
 *
 *  Implementation of the Passenger Class 
 *
 */


#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print
 * purpose:   prints the id and the arrival and depature station of the 
 *            passenger 
 * arguments: an output stream to print the information to 
 * returns:   none
 * effects:   none
*/
void Passenger::print(std::ostream &output)
{
        //prints the information to the output stream 
        output << "[" << id << ", " << from << "->" << to << "]";
}

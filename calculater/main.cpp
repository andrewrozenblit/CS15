/*
 *  main.cpp
 *  Andrew Rozenblit 
 *  02/28/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Purpose: Driver of CalcYouLater program 
 *           Program runs a calculator that is able to process postfix input,
 *           file input, and genral values, as well as complete certain 
 *           functions on the input.
 *
 */
#include <iostream>
#include <fstream>
#include <string>

#include "RPNCalc.h"

using namespace std;


/*
 * name:      main
 * purpose:   start the program and call the RPNCalc class
 * arguments: none
 * returns:   an int, always 0
 * effects:   none
*/
int main() {
    RPNCalc x; //create instance of the program 
    x.run(); //run the query loop
    return 0;
}
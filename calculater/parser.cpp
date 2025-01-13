/*
 *  parser.cpp
 *  Andrew Rozenblit 
 *  02/28/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Purpose: implementation of parser.h
 *          reads in an RPN String inputted by the user  
 *
 */



#include <string>
#include <iostream>
using namespace std;


/*
 * name:      parseRString
 * purpose:   processes the input for an inputted rString
 * arguments: an istream, input, from where to read the rString     
 * returns:   a string holding the inputted rString
 * effects:   none
*/
std::string parseRString(std::istream &input) {
    string rpn = "{"; //all rStrings start with '{'
    string temp; 
    int i = 1; //i will track how many {}, already one { so starts at 1
    while(i != 0) { //stop running when i hits 0 (meaning equal num of { and })
        input >> temp; //put next thing into temp
        if (temp == "{") { //if temp is a { increment i 
            i++;
        } else if (temp == "}") { //if temp is a { decrement i 
            i--;
        }
        rpn += " "; //include a space between things
        rpn += temp; //add temp to the end of rpn
    }
    return rpn; //return rpn 
}
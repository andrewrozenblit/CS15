/*
 *  main.cpp
 *  Andrew Rozenblit 
 *  03/28/24
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: simple driver function that calls either the encode, decode, or
 *  prints an error depending on the users run command.
 *
 */

#include <iostream>
#include <string>
#include "HuffmanCoder.h"


/*
 * name:      main
 * purpose:   drives the zap program
 * arguments: an int with the number of command line argumetns and an array of
 *            the commands provided
 * returns:   none
 * effects:   strats the encoding or decoding 
*/
int main(int argc, char *argv[]) {
    //if invalid amount of commands 
    if (argc != 4) {
        std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
        return 0;
    }
    std::string input = argv[2]; //put the name of input file into input
    std::string output = argv[3]; //put the name of output file into ouput
    HuffmanCoder instance; //create instance of HuffmanCoder class
    std::string given = argv[1]; //put the command of what to do into given
    //if told to zap then call encoder and pass input and output
    if (given == "zap") { 
        instance.encoder(input,output);
    //if told to unzap then call decoder and pass input and output
    } else if (given == "unzap") { 
        instance.decoder(input, output);
    } else { //otehrwise print error message
        std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
    }
}
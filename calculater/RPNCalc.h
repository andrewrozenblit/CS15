/*
 *  RPNCalc.h
 *  Andrew Rozenblit 
 *  02/28/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Purpose: interface of the RPNCalc class
 *           An instance of this class creates a calculator where the user is 
 *           able to provide input in the form of Datum (which can be a bool,
 *           int, or rString) and this data will be stored, with the most 
 *           recent at the top and the oldest input at the bottom. Also,
 *           the user is able to input commands that wille be completement on 
 *           the top and potentially second or third elements. These commands 
 *           included arithmetic and boolean calculations, removal or addition
 *           of new elements, manipulation of the placement of elements, and 
 *           execution of a RPN string being stored. It is implemented with the
 *           use of an instance of DatumStack to achieve the First in and First
 *           out effect, where the top most element is the most recent element
 *           inputted. 
 *
 */


#ifndef _RPNCALC_H_
#define _RPNCALC_H_

// Put any necessary includes here
#include <string>
#include <sstream>
#include <iostream>
#include <string>
#include "parser.h"
#include "DatumStack.h"
#include "Datum.h"

// Put any other structs you need here

class RPNCalc
{
public:
    RPNCalc();
    void run();
private:
    //private helper functions
    DatumStack stack;

    bool got_int(std::string s, int *resultp);
    void process_input(std::string input, std::istream &inputStream);
    void process_input2(std::string input, std::istream &inputStream);
    //small tasks
    void pushNum(int num);
    void addTrue();
    void addFalse();
    void notCommand();
    void print();
    void clear();
    void drop();
    void dup();
    void swap();
    void arithmetic_operators(std::string input);
    void bool_operators(std::string input);
    void double_equal_operator();
    void rString(std::istream &input);
    void exec();
    void file();
    void ifCommand();

};

#endif

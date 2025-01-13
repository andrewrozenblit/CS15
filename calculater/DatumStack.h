/*
 *  DatumStack.h
 *  Andrew Rozenblit 
 *  02/14/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Purpose: Interface of the DatumStack data structure 
 *           The DatumStack class represents a stack storing Datum. It is able
 *           to push new elements to the top, pop top elements off, pop all 
 *           elements off (clear), give the user the size, top elements, and 
 *           a bool whether it is empty. It is represented using a list of 
 *           type Datum.
 *
 */


#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include "Datum.h"

// Put any other necessary includes here
#include <fstream>
#include "Datum.h"
#include <list>
#include <vector>
#include <sstream>
#include <string>

class DatumStack
{
public:
    DatumStack();
    DatumStack(Datum arr[], int size);
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum newDatum);
private:
    //list 
    std::list<Datum> stack; 
    

};

#endif

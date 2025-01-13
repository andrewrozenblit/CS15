/*
 *  DatumStack.cpp
 *  Andrew Rozenblit 
 *  02/21/24
 *
 *  CS 15 Project 2 - CalcuLater
 *
 *  Implementation of the DatumStack Class 
 *
*/

#include "DatumStack.h"
using namespace std;

/*
 * name:      DatumStack default Constructor 
 * purpose:   creates new empty instance of the DatumStack class
 * arguments: none
 * returns:   none
 * effects:   none
*/
DatumStack::DatumStack() {
    
}

/*
 * name:      DatumStack Constructor 
 * purpose:   creates new instance of the DatumStack class with the values from
 *            the array
 * arguments: an array of Datum to be pushed on, and int of the amount of Datum
 *            stored on the array
 * returns:   none
 * effects:   none
*/
DatumStack::DatumStack(Datum arr[], int size) {
    //traverse the array pushing each element onto the stack
    for (int i = 0; i < size; i++) {
        stack.push_back(arr[i]);
    }
}

/*
 * name:      isEmpty 
 * purpose:   Determines if there are elenments on the stack
 * arguments: none
 * returns:   a bool, true if no Datum on stack, false otherwise 
 * effects:   none
*/
bool DatumStack::isEmpty() {
    if (stack.empty()) { //if nothing on the stack
        return true;
    } else {
        return false;
    }
}

/*
 * name:      clear 
 * purpose:   removes all elements from stack
 * arguments: none
 * returns:   none 
 * effects:   stack now empty 
*/
void DatumStack::clear() {
    stack.clear();
}

/*
 * name:      size 
 * purpose:   gives the user the amount of elements on the stack
 * arguments: none
 * returns:   an int, storing the amount of Datum on the stack 
 * effects:   none 
*/
int DatumStack::size() {
    return stack.size();
}

/*
 * name:      top 
 * purpose:   gives the user the Datum at the top of the stack
 * arguments: none
 * returns:   a Datum, storing the element at the top of the stack
 * effects:   none 
*/
Datum DatumStack::top() {
    //if empty stack throw error 
    if (stack.empty()) {
        throw std::runtime_error("empty_stack\n");
    }
    return stack.back(); //back of the list =  top of the stack 
}

/*
 * name:      pop 
 * purpose:   removes the top element of the stack
 * arguments: none
 * returns:   none
 * effects:   top of the stack now second to top element  
*/
void DatumStack::pop() {
    //if empty stack throw error 
    if (stack.empty()) {
        throw std::runtime_error("empty_stack\n");
    }
    stack.pop_back(); //back of the list =  top of the stack 
}

/*
 * name:      push 
 * purpose:   adds new element to the top of the stack
 * arguments: a Datum, storing the new Datum to be added to the stack
 * returns:   none
 * effects:   new element at the top of the stack
*/
void DatumStack::push(Datum newDatum) {
    stack.push_back(newDatum);
}
/*
 *  unit_test.h
 *  Andrew Rozenblit 
 *  02/23/24
 *
 *  CS 15 Project 2 - CalcYouLater
 *
 *  A unit testing file for the CalcYouLater project
 */

#include "Datum.h"
#include "parser.h"
#include "DatumStack.h"
#include "RPNCalc.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//PARSER CLASS TESTS 

// //test when RPN all in one line
void parseRString_test1() {
    //create a fake input 
    std::istringstream fakeInput(" 2 3 + }");
    //call parseRstring and put return into r  
    string r = parseRString(fakeInput);
    //check the parsed string
    assert(r == "{ 2 3 + }");
}

//test when RPN input in mutliple lines 
void parseRString_test2() {
    //create fake input
    std::istringstream fakeInput(" yeet }");
    //call parseRstring and put return into r  
    string r = parseRString(fakeInput);
    //check the parsed string
    assert(r == "{ yeet }");

}

//test when RPN is nested 
void parseRString_test3() {
    //create fake input
    std::istringstream fakeInput(" 2 \n 3 \n   +  \n");
    //call parseRstring and put return into r  
    string r = parseRString(fakeInput);
    //check the parsed string
    assert(r == "{ 2 3 + ");
}

//DATUMSTACK TESTS

//check that d can be created by the default constructor
void dStack_default() {
    //create instance 
    DatumStack d;
}

//check other constructor 
void dStack_arrayconstructor() {
    //create some Datum
    Datum x(1);
    Datum y(true);
    Datum z(2);
    //put them into an array 
    Datum arr[3] = {x,y,z};
    //create an instance 
    DatumStack d(arr,3);
}

//checks if isEmpty() returns false when stack is not empty 
void isEmpty_true() {
    DatumStack d; //create instance 
    assert(d.isEmpty()); //assert 
}

//checks if isEmpty() returns true when stack is empty 
void isEmpty_false() {
    //create an array of datum 
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[3] = {x,y,z};
    //create instance of DatumStack using the array
    DatumStack d(arr,3);
    assert(not d.isEmpty()); //assert that its false 
}

//check that size() returns correct size 
void test_size() {
    //create an array of datum 
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[3] = {x,y,z};
    //create instance of DatumStack using the array
    DatumStack d(arr,3);
    assert(d.size() == 3); //assert that its 3 
}

//check that clear() removes all elements 
void clear() {
    //create an array of datum 
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[3] = {x,y,z};
    //create instance of DatumStack using the array
    DatumStack d(arr,3);
    d.clear(); //call clear 
    assert(d.isEmpty()); //assert that instance now empty 
}

//confirm top returns correct Datum 
void top() {
    //create an array of datum 
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[3] = {x,y,z};
    //create instance of DatumStack using the array
    DatumStack d(arr,3);
    //make sure last element of the array is top of stack 
    assert(d.top().getInt() == z.getInt());
}

//check that top throws correct error when empty stack
void top_error() {
    DatumStack d;

    //initializes error variables
    bool runtime_error_thrown = false; //is an error being thrown
    std::string error_message = ""; //message of the error

    try { //attempt this
        d.top(); //calls top() 
    }
    catch (const std::runtime_error &e) { //if the runtime error is thrwon
        runtime_error_thrown = true; //error was thrown so make true
        error_message = e.what(); //hold the error message
    }

    assert(runtime_error_thrown); //was the error thrown
    //was this the message thrown
    assert(error_message == "empty_stack\n");
}

//confirm pop removes the last element 
void test_pop() {
    //create an array of datum 
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[3] = {x,y,z};
    //create instance of DatumStack using the array
    DatumStack d(arr,3);
    d.pop(); //remove the top element 
    //is the top element now true 
    assert(d.top().getBool() == y.getBool());
}

//does pop throw correct error when empty stck 
void pop_error() {
    DatumStack d;

    //initializes error variables
    bool runtime_error_thrown = false; //is an error being thrown
    std::string error_message = ""; //message of the error

    try { //attempt this
        d.pop(); //calls pop() 
    }
    catch (const std::runtime_error &e) { //if the runtime error is thrwon
        runtime_error_thrown = true; //error was thrown so make true
        error_message = e.what(); //hold the error message
    }

    assert(runtime_error_thrown); //was the error thrown
    //was this the message thrown
    assert(error_message == "empty_stack");
}

//test that push adds element to the top 
void test_push() {
    //create an array of datum
    Datum x(1);
    Datum y(true);
    Datum z(2);
    Datum arr[2] = {x,y};
    //create instance using that array
    DatumStack d(arr,2);
    //push z onto the stop
    d.push(z);
    //is the top element now z 
    assert(d.top().getInt() == z.getInt());
}

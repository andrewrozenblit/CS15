/*
 *  unit_test.h
 *  Andrew Rozenblit 
 *  02/11/24
 *
 *  CS 15 Project 1 - MetroSim
 *
 *  A unit testing file for the MetroSim project
 */

#include "PassengerQueue.h"
#include "MetroSim.h"
#include "Passenger.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Check if a PassenegerQueue can be created
void createQueue() {
    //create instance of PassengerQueue
    PassengerQueue newQueue; 
}

//Check if a Passeneger can be created Default
void createPassengerDefault() {
    //create default instance of Passenger
    Passenger newPass;
}

//Check if a Passeneger can be created
void createPassenger() {
    //create instance of Passenger
    Passenger newPass(1, 0, 4);
}

//check if the enqueue function will throw errors
void checkEnqueue() {
    //create a Passenger
    Passenger newPass;
    //create the queue
    PassengerQueue newQueue; 
    //use enqueue to put the passenger in the queue
    newQueue.enqueue(newPass);
}

//check that Front returns the proper id of the first Passenger
void checkFront_ID() {
    //create two passengers 
    Passenger newPass(1, 0, 4);
    Passenger newPass1(2, 4, 5);
    //create the queue 
    PassengerQueue newQueue; 
    //add the passengers to the queue
    newQueue.enqueue(newPass);
    newQueue.enqueue(newPass1);

    //confirm that the proper id is returned 
    assert(newQueue.front().id == 1);
}

//checks that Front returns the proper arrival station number of the first 
//Passenger 
void checkFront_A() {
    //create two passengers 
    Passenger newPass(1, 0, 4);
    Passenger newPass1(2, 4, 5);
    //create the queue 
    PassengerQueue newQueue; 
    //add the passengers to the queue
    newQueue.enqueue(newPass);
    newQueue.enqueue(newPass1);

    //confirm that the proper departure station number is returned 
    assert(newQueue.front().from == 0);
}

//checks that Front returns the proper departure station number of the first 
//Passenger 
void checkFront_D() {
    //create two passengers 
    Passenger newPass(1, 0, 4);
    Passenger newPass1(2, 4, 5);
    //create the queue 
    PassengerQueue newQueue; 
    //add the passengers to the queue
    newQueue.enqueue(newPass);
    newQueue.enqueue(newPass1);

    //confirm that the proper arrival station number is returned 
    assert(newQueue.front().to == 4);
}

//checks that the proper size is returned
void checkSize() {
    //create 4 Passengers
    Passenger newPass1;
    Passenger newPass2;
    Passenger newPass3;
    Passenger newPass4;
    //create a queue
    PassengerQueue newQueue; 
    //add the passengers to queue
    newQueue.enqueue(newPass4);
    newQueue.enqueue(newPass1);
    newQueue.enqueue(newPass2);
    newQueue.enqueue(newPass3);

    //check that the size of the queue is 4
    assert(newQueue.size() == 4);
}

// checks that the first passenger was removed 
void checkDequeue() {
    //create 4 Passengers
    Passenger newPass1(1,2,3);
    Passenger newPass2(2,4,2);
    Passenger newPass3(3,4,22);
    Passenger newPass4(4,22,4);
    //create a queue
    PassengerQueue newQueue; 
    //add the passengers to queue
    newQueue.enqueue(newPass1);
    newQueue.enqueue(newPass2);
    newQueue.enqueue(newPass3);
    newQueue.enqueue(newPass4);
    //remoce the last passenger added
    newQueue.dequeue();
    //check that a passenger was removed
    assert(newQueue.size() == 3);
    //define output stream
    ostringstream output;
    //call print
    newQueue.print(output);
    string out = output.str();
    //check to make sure it was the first one 
    assert(out == "[2, 4->2][3, 4->22][4, 22->4]");
}

//checks that the print function in Passenger class works 
void checkPrint() {
    //create passenger
    Passenger newPass(2,6,7);
    //define the stream
    ostringstream output;
    //call print
    newPass.print(output);
    //transfer the output from the stream to string variable
    string out = output.str();
    //check to make sure printed the right thing
    assert(out == "[2, 6->7]");
   
}





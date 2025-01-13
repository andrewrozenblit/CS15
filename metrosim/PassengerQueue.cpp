/*
 *  PassengerQueue.cpp
 *  Andrew Rozenblit 
 *  02/11/24
 *
 *  CS 15 Project 1 - MetroSim
 *
 *  Implementation of the PassengerQueue Class 
 *
 */


#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include "PassengerQueue.h"
#include <algorithm>
#include <list>
using namespace std;

/*
 * name:      front
 * purpose:   returns the first passenger in the queue
 * arguments: none
 * returns:   the Passenger at the front of the queue
 * effects:   none
 */
Passenger PassengerQueue::front() {
    //check that the queue isn't empty
    if (queue.size() == 0) {
        throw runtime_error("cannot get first of empty Queue");
    }
    //return the front passenger 
    return queue.front();
}

/*
 * name:      dequeue
 * purpose:   removes the first passenger from the queue
 * arguments: none
 * returns:   none
 * effects:   decreases the list by one since the first one is removed
 */
void PassengerQueue::dequeue(){
    //check that the queue isn't empty
    if(queue.size() == 0){ 
        throw runtime_error("cannot dequeue from empty queue");
    }
    //removes the first Passenger in the list
    queue.pop_front();
}

/*
 * name:      enqueue
 * purpose:   adds a Passenger to the back of the queue
 * arguments: an instance of the Passenger class to add to the list
 * returns:   none
 * effects:   increases the list by 1 since a new Passenger is being added
 */
void PassengerQueue::enqueue(const Passenger &passenger){
    //push the passed in passenger to the back of the list
    queue.push_back(passenger);
}

/*
 * name:      size
 * purpose:   gives the user the size of the list
 * arguments: none
 * returns:   an int storing the size of the list
 * effects:   none
 */
int PassengerQueue::size(){
    //return the list size
    return queue.size();
}

/*
 * name:      print
 * purpose:   prints the id and the arrival and depature station of each 
 *            passenger stored in the queue to the provided output stream
 * arguments: an output stream to print the information to 
 * returns:   none
 * effects:   none
 */
void PassengerQueue::print(std::ostream &output){
    //define an iterator variable to traverse the list
    std::list<Passenger>::iterator it;
    //for loop that traverses each element of the list 
    for (it = queue.begin(); it != queue.end(); it++){
        //retrieves the passenger at the current iteration of it 
        Passenger& currentPassenger = *it;
        //calls the Print function in the Passenger function 
        currentPassenger.print(output);
    }
}
/*
 *  PassengerQueue.h
 *  Andrew Rozenblit 
 *  02/11/24
 *
 *  CS 15 Project 1 - MetroSim
 *
 *  Interface of the PassengerQueue Class
 *
 */



#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream>
#include "Passenger.h"
#include <algorithm>
#include <iostream>
#include <list>

class PassengerQueue {
    public: 
        Passenger front();
        void dequeue();
        void enqueue(const Passenger &passenger);
        int size();
        void print(std::ostream &output);

    private:
        //list 
        std::list<Passenger> queue; 
};
#endif

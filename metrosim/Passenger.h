/*
 *  Passenger.h
 *  Andrew Rozenblit 
 *  02/11/24
 *
 *  CS 15 Project 1 - MetroSim
 *
 *   Interface of the Passenger Class
 *
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif

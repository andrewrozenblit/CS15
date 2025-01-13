/*
 *  MetroSim.cpp
 *  Andrew Rozenblit 
 *  02/14/24
 *
 *  CS 15 Project 1 MetroSimulation
 *
 *  Purpose: Implementation of the Simulation 
 *
 */

#include "MetroSim.h"
using namespace std;

/*
 * name:      prompt_and_execute
 * purpose:   runs the MetroSim simulation prorgam 
 * arguments: an int, argc, storing the total amount of arguments the user 
 *            passed in when running the executable, a char pointer argv 
 *            storing the names of things that the user is passing in when 
 *            running the executable 
 * returns:   none
 * effects:   begins the simulation and initializes all relevant values 
 */
void MetroSim::prompt_and_execute(int argc, char *argv[]) {
    //open the output stream
    ofstream outstream;
    outstream.open(argv[2]);
    //creates the vector of station Structs 
    createStations(argv[1]); //create the stations and put them into the vector
    //set up input
    ifstream instream;
    //if read in from command file
    if (argc == 4) {
        instream.open(argv[3]); //open the read in file
        //if file can not be opened print error and quit 
        if (not instream.is_open()) {
            cerr << "Error: could not open file " << argv[3]  << endl;
            exit(EXIT_FAILURE);
        }
        simLoop(instream, outstream);
    } else {
        simLoop(cin, outstream);
    }
    
    //final message 
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
    //close all open files
    outstream.close();
    if (argc == 4) instream.close();
}

/*
 * name:      simLoop
 * purpose:   runs the MetroSim simulation query loop 
 * arguments: a bool called file, true if reading from file, and false if 
 *            reading from terminal, an istream called instream to read from if
 *            if reading from file, and an ostream called output of where to   
 *            output when not print to terminal.
 * returns:   none
 * effects:   begins the simulation loop 
 */
void MetroSim::simLoop(std::istream &instream, std::ostream &output) 
{   
    //initialize all variables 
    string input = "";
    int stationNum = 0;
    int passCount = 1;
    //begin the loop that finishes when f last thing inputted is f or if
    //a command file provided, then when end of that file
    //print the passengers currently on the train
    printPassengersOnTrain(stationNum);
    //print the stations and the people who are waiting there 
    printStations(stationNum);
    while (input != "m f" and getline(instream,input)) {
        
        if (input[0] == 'p') { //if the first thing inputted was p 
            newPassenger(passCount, input); //create a new Passenger
            passCount++; //update passCount -- serves to track id numbers
        } else if (input[0] == 'm') { //if the first thing inputted was m
            if (input[2] == 'm') { //if second was also m 
                moveStation(stationNum, output); //move the station
                if (stationNum == stations.size()-1) {
                    stationNum = 0; //if at the end of the sim loop to front
                }
                else stationNum++; //update the station sim is on
            }
        } 
        if (input[input.size()-1] != 'f') {
            //print the passengers currently on the train
            printPassengersOnTrain(stationNum);
            //print the stations and the people who are waiting there 
            printStations(stationNum);
        }
    }
}

/*
 * name:      figureInput
 * purpose:   determines whether to take input from file or std::cin 
 * arguments: a bool called file, true if reading from file, and false if 
 *            reading from terminal, and an istream called instream to read 
 *            from if reading from file
 * returns:   returns the string that processInput read in 
 */
std::string MetroSim::figureInput(bool file, std::istream &infile) {
    //if reading in from file pass the file into processInput
    if (file) {
        return processInput(infile);
    } 
    //otherwise passin standard input (cin)
    else {
        return processInput(cin);
    }
}

/*
 * name:      processInput
 * purpose:   reads in input from the provided istream 
 * arguments: an istream called infile storing the stream to read in from 
 * returns:   the string that was read in 
 */
std::string MetroSim::processInput(std::istream &infile) {
    string input; //initialize input 
    infile >> input; //read and store into input 
    return input; //return input 
}

/*
 * name:      createStations
 * purpose:   creates the vector full of Station structs 
 * arguments: a string, filename, storing the name of the stations file 
 * returns:   none 
 */
void MetroSim::createStations(char *filename) {
    ifstream infile; //create a var type instream
    infile.open(filename); //open the file 

    //if file did not open print an error message 
    if (not infile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string current_line; 
    int id = 0;
    //loop until end of the file 
    while (getline(infile, current_line)) {
        Station newStat; //initialize Station 
        newStat.name = current_line; //set name to what was read in 
        newStat.id = id; //set id to the number of the station 
        stations.push_back(newStat); //add Station to the back of the vector 
        id++; //increment id
    }

    infile.close(); //close the file 
}

/*
 * name:      printStations
 * purpose:   prints all stations and the people queued at them  
 * arguments: an int storing the id of the current station the sim is on 
 * returns:   none 
 */
void MetroSim::printStations(int currstation) {
    //for loop that does through each index of the vector 
    for (int i = 0; i < stations.size(); i++) {
        //set loopstation to the station at that index 
        Station loopstation = stations.at(i); 
        //if simulation at that station print Train
        if (currstation == loopstation.id) {
            std::cout << "TRAIN: ";
        }
        //otherwise print a gap
        else {
            cout << "       ";
        }
        //print the name of the station 
        cout << "[" << i << "] " << loopstation.name << " {";  
        //print the passenger who are going to get on at that station
        loopstation.queued.print(std::cout);
        cout << "}" << endl;
    }
    cout << "Command? "; //ask for the command 
}

/*
 * name:      printPassengersOnTrain
 * purpose:   prints all passengers currently on the train  
 * arguments: an int storing the id of the current station the sim is on 
 * returns:   none 
*/
void MetroSim::printPassengersOnTrain(int stationNum) {
    cout << "Passengers on the train: {";
    // int i;
    // //set i to the next station, if current station at the end set i to 0
    // if (stationNum == stations.size()-1) {
    //     i = 0;
    // }
    // //otherwise set i to 1 more than the statioNum
    // else {
    //     i = stationNum+1;
    // }
    // //loop until i is equal to stationNum 
    // while (i != stationNum) {
    //     //print the passengers getting off at this station 
    //     stations.at(i).gettingOff.print(std::cout);
    //     //increment i or set back to 0 if at last station
    //     if (i == stations.size()-1) i = 0;
    //     else i++;
    // }
    int i = 0;
    while (i < stations.size()) {
        //print the passengers getting off at this station 
        stations.at(i).gettingOff.print(std::cout);
        //increment i or set back to 0 if at last station
        i++;
    }
    cout << "}" << endl;
}

/*
 * name:      newPassenger
 * purpose:   creates a new passenger and adds them to the vector of people 
 *            queued  
 * arguments: an int, passCount, that stores what will be the id of the 
 *            Passenger, a bool called file, true if reading from file, and  
 *            false if reading from terminal, and an istream called instream  
 *            to read from if reading from file 
 * returns:   none 
*/
void MetroSim::newPassenger(int passCount, std::string input) {
    //read in where the Passenger will get on and off
    char letter;
    int getOn, getOff;
    // Create a stringstream from the input line
    std::istringstream iss(input);
    // Extract the letter and two numbers
    iss >> letter >> getOn >> getOff;
    //create a new instance of the Passenger class
    Passenger newPass(passCount, getOn, getOff);
    //add that Passenger into the vector of people getting on at that station
    stations.at(getOn).queued.enqueue(newPass);
}

/*
 * name:      moveStation
 * purpose:   moves sim to the next station 
 * arguments: an int, stationNum, storing the station sim is currently on 
 *            an ostream, output, where to print certain output
 * returns:   none 
*/
void MetroSim::moveStation(int stationNum, std::ostream &output) {
    int prevStation = stationNum;
    //adds passengers queued onto the train at the station that train left
    putOnTrain(prevStation);
    //if at the last station, next station will be 0
    if (stationNum == stations.size()-1) {
        stationNum = 0;
    }
    else {
        stationNum++; //otherwise next station will be 1 more 
    }
    //takes off the passengers getting off at the next station
    takingOffTrain(stationNum, output);
    
}

/*
 * name:      putOnTrain
 * purpose:   adds the passengers queued at the current station onto the train 
 * arguments: an int, stationNum, storing the station sim is currently on
 * returns:   none 
*/
void MetroSim::putOnTrain(int stationNum) {
    Passenger temp;
    //number of people getting on at this station
    int size = stations.at(stationNum).queued.size(); 
    //loop that adds all people getting on onto the train
    for (int i = 0; i < size; i++) {
        //stores the person at the front of the queue into temp
        temp = stations.at(stationNum).queued.front();
        //puts that passenger on the gettingOff vector of their to station
        stations.at(temp.to).gettingOff.enqueue(temp);
        //removes that passenger from queued since no longer waiting for train
        stations.at(stationNum).queued.dequeue();
    }
}

/*
 * name:      takingOffTrain
 * purpose:   removes the passengers from the train who are getting off at this
 *            station 
 * arguments: an int, stationNum, storing the station sim is currently on 
 *            an ostream, output, where to print certain output
 * returns:   none 
*/
void MetroSim::takingOffTrain(int stationNum, std::ostream &output) {
    Passenger temp;
    //get the size of the list of passengerQueue of people getting off here 
    int size = stations.at(stationNum).gettingOff.size();
    //loops through removing all people getting off this station
    for (int i = 0; i < size; i++) {
        temp = stations.at(stationNum).gettingOff.front();
        //print that passneger has left train to provided output stream 
        output << "Passenger " << temp.id << " left train at station " << 
        stations.at(stationNum).name << endl; 
        //removes the person from the queue
        stations.at(stationNum).gettingOff.dequeue(); 
    }
}


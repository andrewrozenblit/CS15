/*
 *  RPNCalc.cpp
 *  Andrew Rozenblit 
 *  02/28/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Purpose: Implementation of RPNCalc.h
 *
 */

#include "RPNCalc.h"

/*
 * name:      RPNCalc Constructor 
 * purpose:   creates new instance of the RPNCalc class
 * arguments: none
 * returns:   none
 * effects:   none
*/
RPNCalc::RPNCalc() {

}

/*
 * name:      run
 * purpose:   Begins calculator and query loop 
 * arguments: none 
 * returns:   none
 * effects:   none
*/
void RPNCalc::run() {
    //create an empty string to store the input
    std::string input = " ";
    //run the loop until quit is entered or the end of input is reached 
    while (input != "quit" and std::cin >> input) {
        //call function to process the input command
        process_input(input, std::cin);
    }
    //print goodbye message 
    std::cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name:      process_input
 * purpose:   calls the function to do the command based on the input passed in 
 * arguments: a string holding the input command, an istream from where to read
 *            the commands.  
 * returns:   none
 * effects:   none
*/
void RPNCalc::process_input(std::string input, std::istream &inputStream) {
    //try running these commands 
    try {
        //Based on the command, call the associated function to fulfill task
        if (input == "#t")                  addTrue();
        else if (input == "#f")             addFalse();
        else if (input == "print")          print();
        else if (input == "not")            notCommand();
        else if (input == "clear")          clear();
        else if (input == "drop")           drop();
        else if (input == "dup")            dup();
        else if (input == "dup")            dup();
        else if (input == "swap")           swap();
        else if (input[0] == '#') {
            throw std::runtime_error("invalid boolean #\n"); //throw error
        //call function storing the rest of the ifs 
        } else process_input2(input, inputStream);
    } 
    //if at any time a runtime error is thrown, catch it
    catch(const std::runtime_error &e) {
        //print the error message associated with the thrown exception
        std::cerr << "Error: " << e.what();
    }
}

/*
 * name:      process_input2
 * purpose:   calls the function to do the command based on the input passed in 
 * arguments: a string holding the input command, an istream from where to read
 *            the commands.  
 * returns:   none
 * effects:   none
*/
void RPNCalc::process_input2(std::string input, std::istream &inputStream) {
    int num = 0;
    if (got_int(input,&num))       pushNum(num);
    else if (input == "+" or input == "*" or input == "-" or input == "/" or
             input == "mod") 
    {
            arithmetic_operators(input);
    }
    //                          compares the ASCII Value 
    else if (input.size() <= 2 and (int)input[0] < 63 and (int)input[0] > 59)
    {
        bool_operators(input);
    }
    else if (input == "{")              rString(inputStream);
    else if (input == "exec")           exec();
    else if (input == "file")           file();
    else if (input == "if")             ifCommand();
    else if (input == "quit")           return;
    //if unknown command then print the following message to std::cerr
    else             std::cerr << input << ": unimplemented\n";
}

//SMALLER TASKS

/*
 * name:      pushNum
 * purpose:   pushes the inputted numer onto the stack 
 * arguments: an int, storing the num inputted to be pushed on the stack   
 * returns:   none
 * effects:   adds num to stack 
*/
void RPNCalc::pushNum(int num){
    //creates newDatum which stores num 
    Datum newDatum(num);
    //pushes newDatum onto the stack
    stack.push(newDatum);
}

/*
 * name:      addTrue
 * purpose:   pushes true onto the stack 
 * arguments: none   
 * returns:   none
 * effects:   adds bool true to stack 
*/
void RPNCalc::addTrue(){
    //Creates a new instance of Datum storing true
    Datum newDatum(true);
    //pushes new Datum instance storing true onto the stack
    stack.push(newDatum);
}

/*
 * name:      addFalse
 * purpose:   pushes false onto the stack 
 * arguments: none   
 * returns:   none
 * effects:   adds bool false to stack 
*/
void RPNCalc::addFalse(){
    //Creates a new instance of Datum storing false
    Datum newDatum(false);
    //pushes new Datum instance storing false onto the stack
    stack.push(newDatum);
}

/*
 * name:      notCommand
 * purpose:   pops off the top element, and if bool, pushes on the opposite 
 *            value 
 * arguments: none   
 * returns:   none
 * effects:   pops off element, and pushes on opposite value if bool  
*/
void RPNCalc::notCommand(){
    //store top value in temp
    Datum temp = stack.top();
    //remove top element 
    drop();
    //check if temp is bool
    if (not temp.isBool()) {
        throw std::runtime_error("datum_not_bool\n"); //throw error
    }
    //store the bool values in fin
    bool fin = not temp.getBool();
    //create new Datum instance storing the opposite value
    Datum newTemp(fin);
    //push new Datum instance onto the stack
    stack.push(newTemp);
} 

/*
 * name:      print
 * purpose:   prints the top element on the stack 
 * arguments: none   
 * returns:   none
 * effects:   none
*/
void RPNCalc::print() {
    //puts the top element into temp
    Datum temp = stack.top();
    //if its a bool
    if (temp.isBool()) {
        //if true 
        if (temp.getBool()) {
            std::cout << "#t" << endl; //print "#t"
        } else {
            std::cout << "#f" << endl; //print "#f"
        }
    //if its an int 
    } else if (temp.isInt()) {
        std::cout << temp.getInt() << endl; //print the int
    //else must be an RString
    } else {
        std::cout << temp.getRString() << endl; //prints the RString
    }
}  

/*
 * name:      clear
 * purpose:   removes everything off the stack 
 * arguments: none   
 * returns:   none
 * effects:   empties the stack
*/
void RPNCalc::clear() {
    stack.clear(); //call clear function of DatumStack
}

/*
 * name:      drop
 * purpose:   removes top most element off the stack 
 * arguments: none   
 * returns:   none
 * effects:   takes off the top element 
*/
void RPNCalc::drop() {
    stack.pop(); //call pop function of DatumStack
}

/*
 * name:      dup
 * purpose:   copies the top most element on the stack and pushes it on again 
 * arguments: none   
 * returns:   none
 * effects:   add the top most element to the stack again
*/
void RPNCalc::dup() {
    //store top element into temp
    Datum temp = stack.top();
    //push temp onto the stack
    stack.push(temp);
}

/*
 * name:      swap
 * purpose:   swaps the first and second elements on the stack 
 * arguments: none   
 * returns:   none
 * effects:   switches the first with second element on the stack
*/
void RPNCalc::swap() {
    //store top element into first
    Datum first = stack.top();
    drop(); //remove the element 
    //store the second from the top element into second
    Datum second = stack.top();
    drop(); //remove the element
    //pushes first onto the stack
    stack.push(first);
    //then pushes second onto the stack
    stack.push(second);
}

/*
 * name:      arithmetic_operators
 * purpose:   preforms the operation on the top two elements, assuming they 
 *            are integers 
 * arguments: a string, input, with the operator     
 * returns:   none
 * effects:   removes the top two elements and pushes the final answer
*/
void RPNCalc::arithmetic_operators(std::string input) {
    Datum first = stack.top(); //store top number in first
    drop(); //remove it to access second number
    Datum second = stack.top(); //store top number in second
    drop(); //remove it 
    if (not first.isInt() or not second.isInt()) { //if either are not ints
        throw std::runtime_error("datum_not_int\n"); //throw error
    }   
    int fin = 0; //int to hold the number produced
    //if X operation preform it on the numbers and store answer in fin
    if (input == "+")           fin = first.getInt() + second.getInt(); 
    else if (input == "-")      fin = second.getInt() - first.getInt(); 
    else if (input == "*")      fin = second.getInt() * first.getInt(); 
    else if (input == "/") {  
        int f = first.getInt();
        if (f == 0) throw runtime_error("division by 0.\n");
        fin = second.getInt() / f; 
    }
    else if (input == "mod") {          
        int f = first.getInt();
        if (f == 0) throw runtime_error("division by 0.\n");      
        fin = second.getInt() % first.getInt(); 
    }
    //create a newDatum stack instance storing fin 
    Datum newDatum(fin);
    stack.push(newDatum); //push answer onto stack 
}

/*
 * name:      bool_operators
 * purpose:   preforms the boolean operation on the top two elements
 * arguments: a string, input, with the boolean operator     
 * returns:   none
 * effects:   removes the top two elements and pushes a boolean of the final 
 *            answer 
*/
void RPNCalc::bool_operators(std::string input) {
    //if "==" operation call seperate function since == can compare any types
    if (input == "==") {
        double_equal_operator(); //call function to process ==
        return; //leave function
    } 
    Datum first = stack.top(); //store top number in first
    drop(); //remove it to access second number
    Datum second = stack.top(); //store top number in second
    drop(); //remove it 
    if (not first.isInt() or not second.isInt()){ //if either are not ints
        throw std::runtime_error("datum_not_int\n"); //throw error
    }
    bool fin = false; //bool to hold the boolean produced
    //if X operation preform it on the numbers and store bool answer in fin
    if (input == "<")           fin = second.getInt() < first.getInt(); 
    else if (input == ">")      fin = second.getInt() > first.getInt(); 
    else if (input == ">=")     fin = second.getInt() >= first.getInt(); 
    else if (input == "<=")     fin = second.getInt() <= first.getInt();
    Datum newDatum(fin); //create a newDatum stack instance storing fin 
    stack.push(newDatum); //push fin onto stack 
}

/*
 * name:      double_equal_operator
 * purpose:   preforms the "==" on the top two elements
 * arguments: none   
 * returns:   none
 * effects:   removes the top two elements and pushes a boolean of the final 
 *            answer 
*/
void RPNCalc::double_equal_operator() {
    Datum first = stack.top(); //store top number in first
    drop(); //remove it to access second number
    Datum second = stack.top(); //store top number in second
    drop(); //remove it 
    //compare first and second, put answer in temp 
    bool temp = (first == second);
    stack.push(Datum(temp)); //push Datum storing temp onto the stack
}

/*
 * name:      got_int
 * purpose:   determines if the provided string is a number
 * arguments: a string, s, which the function is testing, an integer pointer
 *            to store the number if the string can be interpreted as an int    
 * returns:   a bool of if the string can be written as an int
 *            also updates passed in pointer with the number if returns true
 * effects:   none
*/
bool RPNCalc::got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

//Harder Tasks 

/*
 * name:      rString
 * purpose:   reads in the rString and pushes it onto the stack
 * arguments: an istream from which to read the input     
 * returns:   none
 * effects:   adds the rString to the top of the stack
*/
void RPNCalc::rString(std::istream &input) {
    //passes the stream to parseRString to read in the rString 
    //stores result in result 
    string result = parseRString(input);
    stack.push(Datum(result)); //puses the rString onto the stack
}

/*
 * name:      exec
 * purpose:   processes the rString 
 * arguments: none     
 * returns:   none
 * effects:   processes the rString commands and pushes result(s) onto the 
 *            stack
*/
void RPNCalc::exec() {
    Datum top = stack.top(); //store top element in top
    drop(); //removes the rString from the stack
    //if the top elements is not a rString throw error
    if (not top.isRString()) {
        throw std::runtime_error("cannot execute non rstring\n"); 
    }
    //store the rString in process
    std::string process = top.getRString();
    std::istringstream iss(process); //create an istringstream iss 
    std::string temp;
    iss >> temp; //put the first thing in process into temp
    while (not iss.eof()) { //run loop until iss hits the end of process
        iss >> temp; //put next thing into temp
        //call process_input to take the command and process it  
        if (temp == "}") continue;
        process_input(temp, iss); 
    }
}

/*
 * name:      file
 * purpose:   opens and processes commands from file 
 * arguments: none     
 * returns:   none
 * effects:   pops off the top elements and adds the stuff from file
*/
void RPNCalc::file() {
    Datum top = stack.top(); //store top element in top
    drop(); //removes the top element 
    if (not top.isRString()) { //if its not an rString throw error 
        throw std::runtime_error("file operand not rstring\n"); 
    }
    //covert the name to a string (i.e. removes the brackets)
    std::string name = top.getRString().substr(2,top.getRString().size()-4); 
    ifstream instream; //creates instance of ifstream, instream
    instream.open(name); //opens the file
    if (instream.fail()) { //checks if file was opened, if not throws error
        std::cerr << "Unable to read " + name + "\n";
    }
    //creates an empty string
    string input = "";
    //until the end of file is hit 
    while (instream >> input) {
        //call process_input to process the command from the file 
        process_input(input, instream);
    }
    //close the file 
    instream.close();
}

/*
 * name:      ifCommand
 * purpose:   pops of top three element off the stack and runs the approprate 
 *            command depending on the condition 
 * arguments: none     
 * returns:   none
 * effects:   pops off three elements, then processes commands of the 
 *            apporpriate rString 
*/
void RPNCalc::ifCommand() {
    Datum falseCase = stack.top(); //store top element in falseCase
    drop(); //removes the top element 
    Datum trueCase = stack.top(); //store next element in trueCase
    drop(); //remove this element 
    //checks that both are rStrings, if not throw error
    Datum condition = stack.top(); //store top number in process
    drop(); //remove this element
    if (not condition.isBool()) { //checks that it is a bool, else throw error
        throw std::runtime_error("expected boolean in if test\n"); 
    } 
    if (not trueCase.isRString() or not falseCase.isRString()) {
        throw std::runtime_error("expected rstring in if branch\n"); 
    } 
    //if condition true, push trueCase rString 
    if (condition.getBool())    stack.push(trueCase);
    //if condition false, push trueCase falseCase 
    else                        stack.push(falseCase);
    exec(); //process the rString pushed onto the stack
}




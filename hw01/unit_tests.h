
/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */
#include "CharArrayList.h"
#include <cassert>
#include <iostream>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */


// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() == 
    "[CharArrayList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 10);  
    assert(test_list.toString() == 
    "[CharArrayList of size 10 <<yabczdefgh>>]"); 

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharArrayList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

// Tests is_Empty when the list is in fact empty 
void isEmpty_true() {
    CharArrayList test_list; // initialize empty list 
    assert(test_list.isEmpty()); //is true being returned
}

// Tests is_Empty when the list is not empty 
void isEmpty_false() {
    // initialize 1-element list
    CharArrayList test_list('a');
    assert(not test_list.isEmpty()); //is false being returned
}

// Tests if the clear function works
void clear_work() {
    // initialize 1-element list
    CharArrayList test_list('a');
    test_list.clear(); //calls clear
    assert(test_list.isEmpty()); //is the list now empty
}

// tests if the first function returns the first element of the list
void test_first() {
    // initialize 1-element list
    CharArrayList test_list('a');
    assert(test_list.first() == 'a'); //is the function returning 'a'

}

//tests if first function returns proper error message if the list is empty
void test_first_error() {
    // initialize empty list
    CharArrayList test_list; 

    //initializes error variables
    bool runtime_error_thrown = false; //is an error being thrown
    std::string error_message = ""; //message of the error

    try { //attempt this
        test_list.first(); //calls first() 
    }
    catch (const std::runtime_error &e) { //if the run time error is thrwon
        runtime_error_thrown = true; //error was thrown so make true
        error_message = e.what(); //hold the error message
    }

    assert(runtime_error_thrown); //was the error thrown
    //was this the message thrown
    assert(error_message == "cannot get first of empty ArrayList");

}

// tests if the last function returns the last element of the list
void test_last() {
    
    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    //initialize the list with the contents of the array
    CharArrayList test_list(test_arr, 10);
    assert(test_list.last() == 'h'); //is last() returning 'h'

}

//tests if last function returns proper error message if the list is empty
void test_last_error() {

    CharArrayList test_list; //initialize empty list 

   //initializes error variables
    bool runtime_error_thrown = false; //is an error being thrown
    std::string error_message = ""; //message of the error

    try { //attempt to call last()
        test_list.last();
    }
    catch (const std::runtime_error &e) { //if run time error thrown
        runtime_error_thrown = true; //set to true
        error_message = e.what(); //hold the error message
    }

    assert(runtime_error_thrown); //was an error thrown
    //was this the message thrown
    assert(error_message == "cannot get last of empty ArrayList");

}

// tests if toReverseString function returns the proper string
void test_toReverseString() {
    // initialize array 
    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    // initialize list with contents of array 
    CharArrayList test_list(test_arr, 10); 

    //was this string returned 
    assert(test_list.toReverseString() == 
    "[CharArrayList of size 10 <<hgfedzcbay>>]");
}

//tests if pushAtBack adds element that was passed to the back of list
void test_pushAtBack() {
    // initialize instance 
    CharArrayList test_list('a');  
    test_list.pushAtBack('b'); //add b to the back
    
    assert(test_list.last() == 'b'); //was b added to the back
}

//tests if pushAtFront adds element that was passed to the front of list
void test_pushAtFront() {
    // initialize instance with one element
    CharArrayList test_list('a');  
    test_list.pushAtFront('b'); //adds b to the front 
    
    assert(test_list.first() == 'b'); //was b added to the front 
}

//tests if insertInOrder adds element that was passed in ASCII order 
void insertInOrder_test() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; 
    //create a CharArrayList with that array
    CharArrayList test_list(test_arr,10); 
    test_list.insertInOrder('c'); //insert C in ASCII order 

    //was c placed correctly into the 2nd index
    assert(test_list.elementAt(2) == 'c'); 
}

//tests if popFromBack removes the last element 
void popFromBack_test() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' };
    //initialize CharArrayList with that array  
    CharArrayList test_list(test_arr,10); 
    test_list.popFromBack(); //remove the last element 
    
    assert(test_list.last() == 'j'); //is j now the last element instead of k
}

//tests if popFromBack throws the correct error for empty list
void popFromBack_error_test() {
    // initialize empty array 
    CharArrayList test_list;

    //initialize error variables 
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try { //attempt to pop from back 
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) { //if runtime error thrown
        runtime_error_thrown = true; //set variable to true
        error_message = e.what(); //store the error message
    }

    assert(runtime_error_thrown); //was runtime error thrown
    //was this message thrown
    assert(error_message == "cannot pop from empty ArrayList"); 
}

// tests if removeAt removes an element at the given index
void removeAt_test() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; 
    //initialize a CharArrayList with the array
    CharArrayList test_list(test_arr,10);
    test_list.removeAt(2); //remove the char at the second index

    //is toString returning the message without the third character and 
    //smaller size 
    assert(test_list.toString() == "[CharArrayList of size 9 <<abefghijk>>]");
}

// tests if removeAt throws the right error message for out of bounds index
void removeAt_test_error() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; 
    //initialize a CharArrayList with the array
    CharArrayList test_list(test_arr,10);

    //error variables 
    bool range_error_thrown = false; //was error thrown
    std::string error_message = ""; //what error message was thrown

    try { //attempt to remove letter at improper index
        test_list.removeAt(12);
    }
    catch (const std::range_error &e) { //catch range error
        range_error_thrown = true; //error was thrown so change to true
        error_message = e.what(); //hold error message
    }

    assert(range_error_thrown); //was the error thrown
    //was the proper error message thrown 
    assert(error_message == "index (12) not in range [0..10)"); 
}

//tests if replaceAt replaces the letter at the index with the parameter 
void replaceAt_test() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; 
    //initialize a CharArrayList with the array
    CharArrayList test_list(test_arr,10);
    test_list.replaceAt('c',2); //replace the letter d with c 

    //was c replaced with d in the message
    assert(test_list.toString() == "[CharArrayList of size 10 <<abcefghijk>>]");
}

//tests if replaceAt throws correct error message if given out of bounds index
void replaceAt_test_error() {
    // initialize array 
    char test_arr[10] = { 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; 
    // initializes list using the array 
    CharArrayList test_list(test_arr,10);

    //error variables 
    bool range_error_thrown = false; //was the error thrown
    std::string error_message = ""; //stores error message

    try { //attempt replaceAt with an improper index
        test_list.replaceAt('f',12);
    }
    catch (const std::range_error &e) { //if range error thrown
        range_error_thrown = true; //set to true
        error_message = e.what(); //store error message
    }

    assert(range_error_thrown); //checks if error thrown
    //checks if proper error message was thrown
    assert(error_message == "index (12) not in range [0..10)");
}

//tests if concatenate adds the second list to the end of first
void concatenate_test(){
    //initialize array
    char test_arr[8] = { 'c', 'h', 'e', 's', 'h', 'i', 'r', 'e'}; 
    //create instance with that array 
    CharArrayList test_list(test_arr,8);

    //initialize second array
    char test_arr2[3] = { 'c', 'a', 't'}; 
    //create second instance with that array
    CharArrayList test_list2(test_arr2,3);
    //create a CharArrayList pointer that points to second instance
    CharArrayList *test_list3 = &test_list2;

    //add 2nd list to the back of the first
    test_list.concatenate(test_list3);
    //were the two concatenated properly and size adjusted
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<cheshirecat>>]");
}

//tests if concatenate still runs if the second list is null
void concatenate_test_null(){
    //initialize array
    char test_arr[8] = { 'c', 'h', 'e', 's', 'h', 'i', 'r', 'e'}; 
    //create instance with that array 
    CharArrayList test_list(test_arr,8);

    //create another instance of CharArrayList class that points to a null list
    CharArrayList test_list2;
    //create a pointer that points to that instance
    CharArrayList *test_list3 = &test_list2;

    //add the null list to the back of set up list 
    test_list.concatenate(test_list3);
    //were the two concatenated properly and size adjusted
    assert(test_list.toString() == "[CharArrayList of size 8 <<cheshire>>]");
}

//tests if the deep copy overloaded assignment operator works 
void assignment_deep_copy_test(){
    //initialize array
    char test_arr[8] = { 'c', 'h', 'e', 's', 'h', 'i', 'r', 'e'}; 
    //create instance with that array 
    CharArrayList test_list(test_arr,8);

    //create a new instance of that class
    CharArrayList test_list2;
    test_list2 = test_list; //have the second one make a deep copy of the frst

    test_list2.pushAtBack('s'); //add an s to the second one 

    //check that now only the second one has an s 
    assert(test_list.toString() == "[CharArrayList of size 8 <<cheshire>>]");
    assert(test_list2.toString() == "[CharArrayList of size 9 <<cheshires>>]");

    
}

//test cocatenate edge case where ask to concatenate to itself 
void concatenate_test_edgeCase(){
    //initialize array
    char test_arr[8] = { 'c', 'h', 'e', 's', 'h', 'i', 'r', 'e'}; 
    //create instance with that array 
    CharArrayList test_list(test_arr,8);

    //create a pointer that points to the instance
    CharArrayList *test_list2 = &test_list;

    //concatenate the instance to itself 
    test_list.concatenate(test_list2);
    //were the two concatenated properly and size adjusted
    assert(test_list2->toString() == 
    "[CharArrayList of size 16 <<cheshirecheshire>>]");
}








/*
 *  CharArrayList.cpp
 *  Andrew Rozenblit
 *  1/24/23
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Implementation of a simple Character ArrayList Class.
 *
 */

#include "CharArrayList.h"
using namespace std;
#include <iostream>
#include <string>
#include <stdexcept>


/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty ArrayList
 * arguments: none
 * returns:   none
 * effects:    and capacity to 0 and arraylist to nullptr
 */
CharArrayList::CharArrayList() {
    //initializing private instance variables 
    arr = nullptr;
    numItems = 0; 
    capacity = 0; 
}

/*
 * name:      CharArrayList single argument constructor
 * purpose:   initialize an ArrayList with one item stored
 * arguments: a character, c, to store  
 * returns:   none
 * effects:   numItems and capacity to 1 and arraylist with one item
 */
CharArrayList::CharArrayList(char c){
    //initializing private instance variables 
    arr = nullptr;
    numItems = 0; 
    capacity = 0;     
    expand(); //allocates the memory for the ArrayList
    arr[0] = c; //sets the character to the 0th index
    numItems++; //increments the number of items 
}

/*
 * name:      CharArrayList full array constructor
 * purpose:   initialize an ArrayList with the elements from an array
 * arguments: an array of characters, arr, to store, and the size of that array 
 * returns:   none
 * effects:   numItems to size and arraylist with all elements from the array
 */
CharArrayList::CharArrayList(char arr[], int size){
    //initializing private instance variables 
    this->arr = nullptr;
    numItems = 0; 
    capacity = 0;
    //copies the values from the array into the list
    for (int i = 0; i < size; i++) {
        //increases space allocated on the heap
        if (numItems == capacity) expand();
        this->arr[i] = arr[i]; //sets the element from the array to the list
        numItems++; //increments the amount of items
    }
}

/*
 * name:      CharArrayList copy constructor
 * purpose: initialize an ArrayList with the elements from the other ArrayList
 * arguments: an ArrayList pointer of characters, other, to store
 * returns:   none
 * effects: numItems to the size of other and arraylist with all elements from 
 *          other 
 */
CharArrayList::CharArrayList(const CharArrayList &other){
    //allocates space on the heap
    arr = new char[other.capacity];
    //copies the values from the instance variables
    numItems = other.numItems; 
    capacity = other.capacity;
    //copies the values from the array into the list
    for (int i = 0; i < numItems; i++){
        arr[i] = other.arr[i];
    }
}

/*
 * name:      CharArrayList destructor
 * purpose:   free memory associated with the ArrayList
 * arguments: none
 * returns:   none
 * effects:   frees memory allocated by CharArrayList instances
 */
CharArrayList::~CharArrayList() {
    delete [] arr; //frees memory on the heap used by the list
}

/*
 * name:      &operator= (overload operator)
 * purpose:   overloads = operator to make deep copies of CharArrayList
 * arguments: CharArrayList other to make the deep copy from
 * returns:   the new CharArrayList deep copy 
 * effects:   the instance of the class is now a deep copy of other
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other){
    if (this == &other) { //if the instance is already the same as other
        return *this;
    }
    
    delete [] arr; //free memory currently used by the list
    arr = new char[other.capacity]; //alocate new space for memory
    //copies the values from the instance variables
    numItems = other.numItems;
    capacity = other.capacity;
    //copies the values from the array into the list
    for (int i = 0; i < numItems; i++){
        arr[i] = other.arr[i];
    }
    return *this; 
}

/*
 * name:      expand
 * purpose:   increase the capacity of the CharArrayList
 * arguments: none
 * returns:   none
 * effects:   creates new, larger array on heap, copies over elements,
 *            and recycles the old array
 */
void CharArrayList :: expand() {
    //increases the capacity
    if (capacity == 0) capacity = 1;
    else (capacity *= 2) += 2;

    //allocates space for the new array with increased capacity
    char *arr2 = new char[capacity];
    //copies over the elements 
    for (int i = 0; i < numItems; i++) {
        arr2[i] = arr[i];
    }
    if (arr != nullptr) delete [] arr; //frees old memory
    arr = arr2; //renames the instance
}

/*
 * name:      isEmpty
 * purpose:   determines if the CharArrayList is empty or not
 * arguments: none
 * returns:   true if CharArrayList contains no elements, false otherwise
 * effects:   none
 */
bool CharArrayList::isEmpty() const{
    if (numItems == 0) return true; //if no items then empty 
    return false; //else not empty 
}

/*
 * name:      clear
 * purpose:   set the size of the CharArrayList to 0 to give the impresion 
 *            that the list is empty 
 * arguments: none
 * returns:   none
 * effects:   CharArrayList is now considered empty 
 */
void CharArrayList:: clear(){
    numItems = 0; //sets the amount of items to 0
}

/*
 * name:      size
 * purpose:   determine the number of items in the int CharArrayList
 * arguments: none
 * returns:   number of elements currently stored in the CharArrayList
 * effects:   none
 */
int CharArrayList:: size() const{
    return numItems; //returns the number of items
}

/*
 * name:      first
 * purpose:   determine the first element of the CharArrayList
 * arguments: none
 * returns:   a char of the first element currently stored in the CharArrayList
 *            if the list is not empty, otherwise a runtime error 
 * effects:   none
 */
char CharArrayList:: first() const{
    //confirms that the list is not empty
    if (isEmpty()) {
        throw runtime_error("cannot get first of empty ArrayList");
    }
    return arr[0]; //returns the first element 
}

/*
 * name:      last
 * purpose:   determine the last element of the CharArrayList
 * arguments: none
 * returns:   a char of the last element currently stored in the CharArrayList
 *            if the list is not empty, otherwise a runtime error 
 * effects:   none
 */
char CharArrayList:: last() const{
    //confirms that the list is not empty
    if (isEmpty()) {
        throw runtime_error("cannot get last of empty ArrayList");
    }
    return arr[numItems-1]; //returns the last element
}

/*
 * name:      elementAt
 * purpose:   determine the char at the index provided 
 * arguments: an int, index, of the place to find the character
 * returns:   a char of the element at the index currently stored in the
 *            CharArrayList if the index is valid, otherwise a range error 
 * effects:   none
 */
char CharArrayList:: elementAt(int index) const {
    //confirms that the index is not out of range
    if (index >= numItems or index < 0) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
                         + to_string(numItems) + ")");
    }
    return arr[index]; //returns the element at the index
}

/*
 * name:      toString
 * purpose: create a string with all the elements and size of the CharArrayList
 * arguments: none
 * returns: a string with the size and elements of the list formatted
 * effects:   none
 */
std::string CharArrayList::toString() const{
    //set up the first part of the string
    string str = "[CharArrayList of size " + to_string(numItems) + " <<";
    //loops through the list
    for (int i = 0; i < numItems; i++) {
        str += arr[i]; 
    }
    str += ">>]"; //end of the string
    return str;
}

/*
 * name:    toReverseString
 * purpose: create a string with all the elements in reverse order and size of
 *          the CharArrayList
 * arguments: none
 * returns: a string with the size and elements in reverse order of the list 
 *          formatted
 * effects:   none
 */
std::string CharArrayList::toReverseString() const{
    //set up the first part of the string
    string str = "[CharArrayList of size " + to_string(numItems) + " <<";
    //loops through the list
    for (int i = numItems-1; i >= 0; i--) {
        str += arr[i];
    }
    str += ">>]"; //end of the string
    return str;
}

/*
 * name:      pushAtBack
 * purpose:   push the provided character into the back of the CharArrayList
 * arguments: a chatacter to add to the back of the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::pushAtBack(char c){
    insertAt(c, numItems); //inserts c to the back of the array
}

/*
 * name:      pushpushAtFrontAtBack
 * purpose:   push the provided character into the front of the CharArrayList
 * arguments: a chatacter to add to the front of the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::pushAtFront(char c){
    insertAt(c, 0); //inserts c to the front of the array
}

/*
 * name:      insertAt
 * purpose:   push the provided character into the provided index of the 
 *            CharArrayList
 * arguments: a chatacter to add to the list and an int where
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList::insertAt(char c, int index){ 
    //checks to see if the index is out of bounds
    if (index > numItems or index < 0) {
        throw range_error("index (" + to_string(index)+ ") not in range [0.." 
                          + to_string(numItems) + "]");
    }
    //expands if more space is required
    else if (numItems == capacity) expand(); 
    //loops through shifting down the elements after the index
    for (int i = numItems; i > index; i--) {
        arr[i] = arr[i-1];
    }
    numItems++; //increments the amount of items
    arr[index] = c; //sets the value at the index
}

/*
 * name:      insertInOrder
 * purpose:   push the provided character into the the array list in ASCII
 *            order of the 
 *            CharArrayList
 * arguments: a chatacter to add to the list
 * returns:   none
 * effects:   increases num elements of CharArrayList by 1,
 *            adds element to list
 */
void CharArrayList:: insertInOrder(char c){
    //loops through the list
    for (int i = 0; i < numItems; i++){
        //finds the place where the ascii value is less then the index
        if (c <= arr[i]){
            insertAt(c,i); //inserts the element 
            return; //takes out of the function 
        }
    }
    insertAt(c,numItems); //inserts the element at the end 
}

/*
 * name:      popFromBack
 * purpose:   remove the last item from the CharArrayList
 * arguments: none
 * returns:   none
 * effects: decreases num items of CharArrayList by 1 removes the last item
 *          from the list if list is not empty, otherwise throws runtime error
 */
void CharArrayList:: popFromBack(){
    //if the nothing to remove
    if(isEmpty()){
        throw runtime_error("cannot pop from empty ArrayList");
    }
    numItems--; //decrements number of items 
}

/*
 * name:      removeAt
 * purpose:   remove an item from the CharArrayList at the index provided
 * arguments: an int, of the index, where to remove the element
 * returns:   none
 * effects: decreases num items of CharArrayList by 1 removes the item at the
 *          index from the list if the index is valide, otherwise throws range 
 *          error
 */
void CharArrayList::removeAt(int index){
    //makes sure index if in bounds
    if (index >= numItems or index < 0) {
        throw range_error("index (" + to_string(index) + ") not in range " 
                          "[0.." + to_string(numItems) + ")");
    }
    //loops through the list
    for (int i = index; i < numItems-1; i++) {
        arr[i] = arr[i+1]; //shifts everything down
    }
    numItems--; //decrements number of items 
}

/*
 * name:      replaceAt
 * purpose:   replaces an item from the CharArrayList at the index provided
 *            with the chracter provided
 * arguments: an int, of the index, where to remove the element and character 
 *            of what to replace with
 * returns:   none
 * effects: switches the char at the index with the char provided unless
*           index is not in bounds then throws a range error
 */
void CharArrayList::replaceAt(char c, int index){
    //makes sure index if in bounds
    if (index >= numItems or index < 0) {
        throw range_error("index (" + to_string(index) + ") not in range " 
                          "[0.." + to_string(numItems) + ")");
    }
    arr[index] = c; //replaces the value
}

/*
 * name:      concatenate
 * purpose: adds the contents of the other CharArrayList to the back of this
 *          instance of the CharArrayList
 * arguments: an instancr of the CharArrayList class, other 
 * returns:   none
 * effects: increases the size and contents of the CharArrayList
 */
void CharArrayList:: concatenate(CharArrayList *other){
    int size_other = other->numItems;
    //no need to concatenate if other is null
    if(other == nullptr){
        return;
    }
    //loops through other 
    for (int i = 0; i < size_other; i++) {
        //adds each element to the back of the instance
        pushAtBack(other->elementAt(i)); 
    }
}

/*
 * name:      popFromFront
 * purpose: remove the first item in the list from the list
 * arguments: none
 * returns:   none
 * effects: decreases the amount of items as first is now gone
 */
void CharArrayList:: popFromFront(){
    //if the nothing to remove
    if(isEmpty()){
        throw runtime_error("cannot pop from empty ArrayList");
    }
    removeAt(0); //remove the first item 
}




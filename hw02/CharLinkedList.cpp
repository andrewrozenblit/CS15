/*
 *  CharLinkedList.cpp
 *  Andrew Rozenblit 
 *  01/31/24
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Implementation of a simple Character LinkedList Class
 *
 */

#include "CharLinkedList.h"
#include <sstream>
#include <string>
using namespace std;
#include <iostream>
#include <stdexcept>


/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty LinkedList
 * arguments: none
 * returns:   none
 * effects:   sets listSize 0 and the front and bakc pointers to nullptr
 */
CharLinkedList::CharLinkedList(){
    //intializes private instance variables
    listSize = 0;
    front = nullptr;
    back = nullptr;
}

/*
 * name:      CharLinkedList single element constructor
 * purpose:   initialize a LinkedList with one item
 * arguments: a character, c, to put on the list
 * returns:   none
 * effects:   sets listSize 1 and LinkedList with one element
 */
CharLinkedList::CharLinkedList(char c) {
    //intializes private instance variables
    listSize = 0; 
    front = nullptr;
    back = nullptr;
    newNode(c, nullptr, nullptr); //creates the node and pushes it on the list
}

/*
 * name:      CharLinkedList array constructor
 * purpose:   initialize a LinkedList with the elements from a array
 * arguments: an array of character, arr, to copy onto the list and and int,
 *            size, with the size of the array
 * returns:   none
 * effects:   sets listSize to size and LinkedList with the elements from
 *            array
*/
CharLinkedList::CharLinkedList(char arr[], int size) {
    //intializes private instance variables
    listSize = 0;
    front = nullptr;
    back = nullptr;
    //loops through array 
    for (int i = 0; i < size; i++) {
       pushAtBack(arr[i]); //pushes letter to the back of list
    }
}

/*
 * name:      CharLinkedList copy constructor
 * purpose: initialize an LinkedList with the elements from the other 
 *          LinkedList
 * arguments: a LinkedList pointer of characters, other, to store
 * returns:   none
 * effects: listSize to the size of other and LinkedList with all elements  
 *          from other 
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other){
    //intializes private instance variables
    listSize = 0;
    front = nullptr;
    back = nullptr;
    //loops through other LinkedList
    for (int i = 0; i < other.listSize; i++) {
        //pushes each element to the back of this instance  
        pushAtBack(other.elementAt(i)); 
    }
}


/*
 * name:      CharLinkedList destructor
 * purpose:   free memory associated with the LinkedList
 * arguments: none
 * returns:   none
 * effects:   frees memory allocated by LinkedList instances
 */
CharLinkedList::~CharLinkedList(){
    recycleRecursively(front); //calls recursive helper function
}

/*
 * name:      recycleRecursively 
 * purpose:   recusrively frees memory associated with the LinkedList
 * arguments: Node, curr, to the node that the recursion is on
 * returns:   none
 * effects:   frees memory allocated by LinkedList instances
 */
void CharLinkedList:: recycleRecursively(Node *curr){
    //base case: when curr is nullptr
    if(curr == nullptr) return; 

    else{ //otherwise
        Node *next = curr->next; //set next to the next Node
        delete curr; //delete this node
        recycleRecursively(next); //recurse and move to the next node
    }
}

/*
 * name:      &operator=
 * purpose:   overloads the = operator to make deep copies rather than shallow
 * arguments: CharlinkedList, other, to deep copy
 * returns:   returns the copied CharLinkedList
 * effects:   the instance of the class is now a deep copy of other
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other){
    if (this == &other) { //if the instance is already the same as other
        return *this;
    }
    recycleRecursively(front); //delete whats already on the list
    front = nullptr; //set front pointer to nullptr
    back = nullptr; //set back pointer to nullptr
    listSize = 0; //set list back to 0
    //loop through the other LinkedList
    for (int i = 0; i < other.listSize; i++) {
        //pushes each element to the back of this instance  
        pushAtBack(other.elementAt(i)); 
    }
    return *this; //returns the instancd 
}

/*
 * name:      isEmpty
 * purpose:   checks if the LinkedList is empty 
 * arguments: none
 * returns:   returns true if the list is empty and false otherwise
 * effects:   none
 */
bool CharLinkedList:: isEmpty() const{
    if (front == nullptr) return true; //if no front then return true
    return false; //else return false
}

/*
 * name:      clear
 * purpose:   resets the LinkedList to empty 
 * arguments: none
 * returns:   none
 * effects:   LinkedList is now empty
 */
void CharLinkedList:: clear(){
    recycleRecursively(front); //delete all Nodes on the list
    //reset private instance variables 
    front = nullptr;
    back = nullptr;
    listSize = 0;
}

/*
 * name:      size
 * purpose:   gives the user the size of the list 
 * arguments: none
 * returns:   none
 * effects:   none
 */
int CharLinkedList:: size() const {
    return listSize; //return the list size
}

/*
 * name:      first
 * purpose:   gives the user the first letter of the list
 * arguments: none
 * returns:   none
 * effects:   none
 */
char CharLinkedList:: first() const {
    if (front == nullptr) { //if empty list throw error
        throw runtime_error("cannot get first of empty LinkedList");
    }
    return front->letter; //return the error
} 

/*
 * name:      last
 * purpose:   gives the user the last letter of the list
 * arguments: none
 * returns:   none
 * effects:   none
 */
char CharLinkedList:: last() const {
    if (front == nullptr) { //if empty list throw error
        throw runtime_error("cannot get last of empty LinkedList");
    }
    return back->letter; //return last letter
}

/*
 * name:      elementAt
 * purpose:   gives the user the element at the provided index
 * arguments: an int, index, at which the element is at
 * returns:   a char with the letter at the index
 * effects:   none
 */
char CharLinkedList:: elementAt(int index) const {
    if (index >= listSize or index < 0) { //if out of bounds throw error
        throw range_error("index (" + to_string(index) + 
                          ") not in range [0.." + to_string(listSize) + ")");
    }
    return recursiveNodeAt(front,index)->letter; //recursive helper function
}

/*
 * name:      recursiveNodeAt
 * purpose:   finds the node at the desired index using recursion
 * arguments: a Node, curr, with the Node the recursion is on an int, index,
 *            at which the element is at
 * returns:   the Node at the index
 * effects:   none
 */
CharLinkedList::Node* CharLinkedList::recursiveNodeAt(Node *curr, int index) 
const {
    //base case the element at the index 
    if (index == 0) return curr;
    //recursively calls itself
    return recursiveNodeAt(curr->next,--index);
}

/*
 * name:      toString
 * purpose:   prints message with the size and letters of the list
 * arguments: none
 * returns:   a string with the message, size, and letters of the list
 * effects:   none
 */
std::string CharLinkedList::toString() const {
   //set up the first part of the string
    string str = "[CharLinkedList of size " + to_string(listSize) + " <<";
    //loops through the list
    str += recurseToString(front);
    str += ">>]"; //end of the string
    return str; 
}

/*
 * name:      recurseToString
 * purpose:   recusrively fills a string with all the letters of the list
 * arguments: A node of which element the recursion is on
 * returns:   a string with the letters of the list
 * effects:   none
 */
std::string CharLinkedList:: recurseToString(Node *curr) const {
    //base case if the list is empty 
    if (curr == nullptr) return "";
    //base case when curr is nullptr so end of list reached
    // if (curr->next == nullptr) return string(1,curr->letter);
    //add letter to the string and recurse to the next node
    return string(1,curr->letter) + recurseToString(curr->next);
}

/*
 * name:      toReverseString
 * purpose:   prints message with the size and the letters of the list in 
 *            reverse
 * arguments: none
 * returns:   a string with the message, size, and letters of the list in 
 *            reverse
 * effects:   none
 */
std::string CharLinkedList:: toReverseString() const {
    //set up the first part of the string
    string str = "[CharLinkedList of size " + to_string(listSize) + " <<";
    //loops through the list
    str += recurseReverse(back);
    str += ">>]"; //end of the string
    return str;
}

/*
 * name:      recurseReverse
 * purpose:   recursively fills a string with all the letters of the list in 
 *            reverse
 * arguments: A node of which element the recursion is on
 * returns:   a string with the letters of the list in reverse 
 * effects:   none
 */
std::string CharLinkedList:: recurseReverse(Node *curr) const {
    //set up the first part of the string
    if (curr == nullptr) return "";
    // if (curr->previous == nullptr) return string(1,curr->letter);
    return string(1,curr->letter) + recurseReverse(curr->previous);
}

/*
 * name:      pushAtBack
 * purpose:   adds the letter to the back of the lsit
 * arguments: a char, c, to add to the back
 * returns:   none
 * effects:   extends the list by 1
 */
void CharLinkedList:: pushAtBack(char c) {
    newNode(c,nullptr,back); //creates a new Node and appends it to the back
}

/*
 * name:      pushAtFront
 * purpose:   adds the letter to the front of the lsit
 * arguments: a char, c, to add to the front
 * returns:   none
 * effects:   extends the list by 1
 */
void CharLinkedList:: pushAtFront(char c) {
    newNode(c,front,nullptr); //creates a new Node and appends it to the back
}

/*
 * name:      insertAt
 * purpose:   adds a new letter to the specified index
 * arguments: a char, c, to add to the list, an int, index, where to put the 
 *            char
 * returns:   none
 * effects:   extends the list by 1
 */
void CharLinkedList:: insertAt(char c, int index) {
    //checks to see if the index is out of bounds
    if (index < 0) {
        throw range_error("index (" + to_string(index)+ ") not in range [0.." 
                          + to_string(listSize) + "]");
    }
    //if index greater than the size of the list set it to the size 
    if (index > listSize) index = listSize; 
    //initialize pointer to store the back element of the new letter
    Node *local_back = nullptr; 
    //initialize pointer to store the next element of the new letter
    Node *local_next = nullptr;
    //find the nodes that will succeed and precede the new one
    if (index > 0) local_back = recursiveNodeAt(front,index-1);
    if (index < listSize) local_next = recursiveNodeAt(front,index);
    newNode(c,local_next,local_back); //create the node
}

/*
 * name:      newNode
 * purpose:   creates a new Node
 * arguments: a char, c, to add to the list, a pointer to the Node after, and
 *            a pointer to the Node previous to the new Node
 * returns:   none
 * effects:   extends the list by 1
 */
void CharLinkedList:: newNode(char c, Node *next, Node *prev) {
    //create the node 
    Node *new_node = new Node;
    //initialize the variables inside Node struct
    new_node->letter = c;
    new_node->next = next;
    new_node->previous = prev;
    
    //if no next set newNode to back 
    if (next == nullptr) back = new_node;
    //otherwise have next point back to new Node
    else next->previous = new_node; 

    //if no back set newNode to front 
    if (prev == nullptr) front = new_node;
    //otherwise have prev point to new Node
    else prev->next = new_node; 
    listSize++; //increase the size of the list
}

/*
 * name:      insertInOrder
 * purpose:   inserts a new node in ASCII order
 * arguments: a char, c, to add to the list
 * returns:   none
 * effects:   extends the list by 1
 */
void CharLinkedList:: insertInOrder(char c) {
    //if empty list
    if(front == nullptr) {
        pushAtBack(c);
        return;
    }    
    Node *temp = front; //temp variable used to traverse the list
    //loop through the list untill ASCII value is greater than c
    while (temp !=  nullptr and temp->letter < c) {
        temp = temp->next; //move to next node
    }

    //if adding to the back use pushAtBack 
    if(temp == nullptr) pushAtBack(c);
    else if(temp == front) pushAtFront(c);
    else newNode(c, temp, temp->previous); //create a new node
}

/*
 * name:      popFromFront
 * purpose:   removes the first element of the list
 * arguments: none
 * returns:   none
 * effects:   decreases the list by 1
 */
void CharLinkedList:: popFromFront() {
    if(isEmpty()){ //if the loop is empty throw eero
        throw runtime_error("cannot pop from empty LinkedList");
    }
    Node *temp = front->next; //set temp to the second element 
    delete front; //delete front
    front = temp; //set the second element to the front
    //set the second element to point back to nullptr 
    if(front != nullptr) front->previous = nullptr; 
    else back = nullptr;
    listSize--;
}

/*
 * name:      popFromBack
 * purpose:   removes the last element of the list
 * arguments: none
 * returns:   none
 * effects:   decreases the list by 1
 */
void CharLinkedList:: popFromBack() {
    if(isEmpty()){ //if empty list
        throw runtime_error("cannot pop from empty LinkedList");
    }
    Node *temp = back->previous; //set second to the last element to temp
    delete back; //delete last element 
    back = temp; //set back to temp
    if(back != nullptr) back->next = nullptr; //have back now point to nullptr
    else front = nullptr;
    listSize--;
}

/*
 * name:      removeAt
 * purpose:   removes the element at that index
 * arguments: int, index, which element to remove
 * returns:   none
 * effects:   decreases the list by 1
 */
void CharLinkedList:: removeAt(int index) {
    //makes sure index if in bounds
    if (index >= listSize or index < 0) { //if index out of nounds
        throw range_error("index (" + to_string(index) + ") not in range " 
                          "[0.." + to_string(listSize) + ")");
    }
    //if removing first element call popFromFront
    if (index == 0) { 
        popFromFront(); 
        return;
    }
    //if removing last element call popFromBack
    if (index == listSize-1)  {
        popFromBack();
        return;
    }
    //finds the Node at that idnex
    Node *curr = recursiveNodeAt(front,index);
    Node *next = curr->next; //set element after to next
    Node *prev = curr->previous; //set element before to prev
    delete curr; //delete the element 
    next->previous = prev; //have next point back to prev
    prev->next = next; //have next point back to prev
    listSize--; //decrease numElemenets by 1
}

/*
 * name:      replaceAt
 * purpose:   replaces the letter at that index with a different letter
 * arguments: int, index, which element to replace, char c, what letter to 
 *            replace with
 * returns:   none
 * effects:   different element at the index
 */
void CharLinkedList:: replaceAt(char c, int index) {
    //makes sure index if in bounds
    if (index >= listSize or index < 0) {
        throw range_error("index (" + to_string(index) + ") not in range " 
                          "[0.." + to_string(listSize) + ")");
    }
    Node *curr =  recursiveNodeAt(front,index); //finds the Node at the index
    curr->letter = c; //resets the letter to c
}

/*
 * name:      concatenate
 * purpose:   appends the letters from other to list
 * arguments: a CharLinkedList point, other
 * returns:   none
 * effects:   new elements added to the back of the list 
 */
void CharLinkedList:: concatenate(CharLinkedList *other) {
    int size = other->listSize;
    for (int i = 0; i < size; i++) {
        pushAtBack(other->elementAt(i));
    }
}
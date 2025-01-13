/*
 *  unit_tests.h
 *  PartyPlaylist
 *  Comp 15 Lab 3
 *
 *  unit testing file for the PartyPlaylist lab.
 *  The tests here are the same as in `main.cpp'
 *
 *  Students can choose how they'd like to test!
 */

#include "CircularBuffer.h"
#include "Queue.h"
#include "Stack.h"
#include <cassert>
#include <iostream>

/* TODO: Add more tests for each class! */

/*  Purpose: Test all CircularBuffer functions are working as expected. */
void testCircularBuffer() {

    CircularBuffer myBuffer(2);
    myBuffer.addAtBack("Positions");
    myBuffer.addAtBack("Holy");


    assert(myBuffer.toString() == "1: Positions\n2: Holy\n");
}

// void testRemoveFront1() {
//     CircularBuffer myBuffer(2);
//     myBuffer.addAtBack("Positions");
//     myBuffer.addAtBack("Holy");

//     myBuffer.removeFromFront();

//     assert(myBuffer.toString() == "1: Holy\n");
// }

// void testRemoveFront2() {
//     CircularBuffer myBuffer(2);
//     myBuffer.addAtBack("Positions");
//     myBuffer.addAtBack("Holy");

//     myBuffer.removeFromFront();
//     myBuffer.addAtBack("Yeet");
    

//     assert(myBuffer.toString() == "1: Holy\n2: Yeet\n");
// }

// void testRemoveBack1() {
//     CircularBuffer myBuffer(2);
//     myBuffer.addAtBack("Positions");
//     myBuffer.addAtBack("Holy");

//     myBuffer.removeFromBack();
//     myBuffer.addAtBack("Yeet");
    

//     assert(myBuffer.toString() == "1: Positions\n2: Yeet\n");
// }

// void testRemoveBack2() {
//     CircularBuffer myBuffer(2);
//     myBuffer.addAtBack("Positions");
//     myBuffer.addAtBack("Holy");

//     myBuffer.removeFromBack();
//     myBuffer.addAtBack("Yeet");
//     myBuffer.addAtBack("HAHAHA");
    
//     std::cout << myBuffer.toString();

//     assert(myBuffer.toString() == "1: Positions\n2: Yeet\n3: HAHAHA");
// }

// void testAddAtFront() {
//     CircularBuffer myBuffer(2);
//     myBuffer.addAtBack("Positions");
//     myBuffer.addAtBack("Holy");

//     std::cout << myBuffer.toString();
//     myBuffer.addAtFront("Yeet");
//     myBuffer.addAtFront("HAHAHA");
    
//     std::cout << myBuffer.toString();
//     // assert(myBuffer.toString() == "1: HAHAHA\n2: Yeet\n3: Positions\n4: Holy");
// }


/*  Purpose: Given a string that's 'our' output, and one that's the reference
 *           output, print both for easy debugging
 */
// void printCompare(std::string ourString, std::string testStr) {
//     std::cout << "ourStr\n------\n" << ourString << "-----\n";
//     std::cout << "testStr\n------\n" << testStr << "-----\n";
// }

// /*  Purpose: Tests Stack class */
// void testStack() {
//     std::string songs[] = {"Positions", "Holy", "Mood", "Lonely", "34+35"};
//     const int   nSongs  = sizeof(songs) / sizeof(std::string);
//     std::string testStr = "";

//     Stack myStack;

//     /* add the songs to the stack, and build up the string to test against */
//     for (int i = 0; i < nSongs; i++) {
//         myStack.push(songs[i]);
//         testStr += std::to_string(i + 1) + ": " + songs[nSongs - i - 1] + "\n";
//     }
//     printCompare(myStack.toString(), testStr);
//     assert(myStack.toString() == testStr);

//     /* take a song off the stack - make sure it's right! */
//     assert(myStack.pop() == "34+35");

//     /* reset and rebuild the test string */
//     testStr = "";
//     for (int i = 0; i < nSongs - 1; i++) {
//         testStr += std::to_string(i + 1) + ": " + songs[nSongs - i - 2] + "\n";
//     }
//     assert(myStack.toString() == testStr);

//     /*
//      * Nice work! Do you think this data structure works well as
//      * a playlist for a party? Would a Queue work better or worse?
//      */
// }

// /*  Purpose: Tests Queue class. */
// void testQueue() {
//     // TODO: Write more tests for testing the queue.
//     //       Think about how a queue keeps track of the next song
//     //       and how you can test that through enqueue and dequeue
//     std::string songs[] = {"Positions", "Holy", "Mood", "Lonely", "34+35"};
//     const int   nSongs  = sizeof(songs) / sizeof(std::string);
//     std::string testStr = "";

//     Queue myQueue;

//     /* add the songs to the queue, and build up the string to test against */
//     for (int i = 0; i < nSongs; i++) {
//         myQueue.enqueue(songs[i]);
//         testStr += std::to_string(i + 1) + ": " + songs[i] + "\n";
//     }

//     /* Make sure our queue is as expected! */
//     assert(std::string(myQueue.toString()) == testStr);

//     /* play a song - make sure it's the right one! */
//     assert(myQueue.dequeue() == "Positions");

//     /* reset and rebuild the test string */
//     testStr = "";
//     for (int i = 0; i < nSongs - 1; i++) {
//         testStr += std::to_string(i + 1) + ": " + songs[i + 1] + "\n";
//     }

//     /* test our queue */
//     assert(myQueue.toString() == testStr);
// }

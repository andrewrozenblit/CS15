/*
 *  CharLinkedList.h
 *  Andrew Rozenblit 
 *  01/31/24
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Interface for a simple Character LinkedList Class
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include<string>

class CharLinkedList {
    public:
        CharLinkedList();
        CharLinkedList(char c);
        CharLinkedList(char arr[], int size);
        CharLinkedList(const CharLinkedList &other);
        ~CharLinkedList();
        CharLinkedList &operator=(const CharLinkedList &other);
        bool isEmpty() const;
        void clear();
        int size() const;
        char first() const;
        char last() const;
        char elementAt(int index) const;
        std::string toString() const;
        std::string toReverseString() const;
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int index);
        void insertInOrder(char c);
        void popFromFront();
        void popFromBack();
        void removeAt(int index);
        void replaceAt(char c, int index);
        void concatenate(CharLinkedList *other);

    private:
        struct Node {
            char letter;
            Node *next;
            Node *previous;
        };
        Node *front;
        Node *back;
        int listSize;

        //recursive destructor helper function
        void recycleRecursively(Node *curr); 
        //recursive toString helper function
        std::string recurseToString(Node *curr) const; 
        //recursive reverseToString helper function
        std::string recurseReverse(Node *curr) const;
        //function that creates a new Node and integrates into list
        void newNode(char c, Node *next, Node *back);
        //uses recursion to find the needed node
        Node* recursiveNodeAt(Node *curr, int index) const;


};

#endif

/*
 *  CharArrayList.h
 *  Andrew Rozenblit
 *  1/24/23
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Interface for a simple Character ArrayList Class.
 *
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H
#include<string>

class CharArrayList {
    public: 
        //Constructors 
        CharArrayList();
        CharArrayList(char c);
        CharArrayList(char arr[], int size);
        CharArrayList(const CharArrayList &other);

        //Destructor
        ~CharArrayList();

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
        void removeAt(int index);
        void replaceAt(char c, int index);
        void concatenate(CharArrayList *other);
        CharArrayList &operator=(const CharArrayList &other);
        void insertInOrder(char c);
        void popFromBack();
        void popFromFront();


    private:
        char *arr;
        int numItems;
        int capacity;

        void expand(); 
};

#endif

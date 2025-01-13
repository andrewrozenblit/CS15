/*
 *      AVLTree.h
 *      AVL Trees
 *      CS 15 Lab 7
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *
 *      2024-03-4 Modified by Skylar Gilfeather
 *                Edited output
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;

void print_tree_details(AVLTree &avl)
{
        avl.print_tree();
}

int main()
{
        AVLTree avl;
        int values[]  = {3, 2, 1, 4, 5, 6, 7, 16, 15, 
			 14, 13, 12, 11, 10, 9, 8};
        int numValues = sizeof(values) / sizeof(int);


        for (int i = 0; i < numValues; i++) {
                cout << "Inserting " << to_string(i) << "..." << endl;
                avl.insert(values[i]);
        }
        cout << "Finished AVL tree: " << endl;
        print_tree_details(avl);
        return 0;
}

/*
 *      AVLTree.h
 *      AVL Trees
 *      CS 15 Lab 7
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *
 *      2024-03-4 Modified by Skylar Gilfeather
 *                Edited documentation 
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>


/*
 * Purpose:  AVL Tree Node
 * Members:
 *      data - integer data value 
 *      height - height of the Node: maximum number of edges from the Node
 *               to a leaf Node.
 *      left - left child Node of the Node
 *      right - right child Node of the Node
 * Note: Defined outside of the AVLTree class so that the code in
 *       pretty_print.cpp can work with Node. This is not good abstraction–
 *       don't do this in your code!
 */
struct Node {
        int   data;
        int   height;
        Node *left;
        Node *right;
};


/* defined in pretty_print.cpp */
void printPretty(Node *root, int level, int indentSpace, std::ostream &out);


class AVLTree {
public:
        /* constructor */
        AVLTree();

        /* destructor */
        ~AVLTree();

        /*
         * insert() inserts a value into the AVL Tree and balances the
         * tree with each insertion.
         * If the value is already in the tree, insert() doesn't add it.
         */
        void insert(int value);

        /*
         * remove() removes a value from the AVL Tree
         * Checks to see if the tree needs to be balanced with each removal
         */
        bool remove(int value);

        /* print the tree (written for you) */
        void print_tree() const;

private:
        /* the root of the tree (starts as nullptr) */
        Node *root;

        /*
         * the following seven functions are private helper functions
         * for the public functions. We do not want to expose the
         * internals of the tree publicly, so we pass the root (and
         * other information in some cases) to the functions below
         * from the public functions.
         */

        /* recursively traverses the tree to find the location */
        Node *insert(Node *node, int value);


        bool remove(Node *node, int value);
        Node *balance(Node *node);
        Node *rightRotate(Node *node);
        Node *leftRotate(Node *node); 

        /* Calculates the difference between node->left's height and
           node->right's height (written for you) 
         */
        int heightDiff(Node *node); 
        /* Returns the height of node (written for you) */
        int nodeHeight(Node *node);

        /* used by the destructor to delete nodes recursively */
        void postOrderDelete(Node *node);
};


#endif /* AVLTREE_H_ */
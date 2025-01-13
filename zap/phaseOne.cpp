#include "phaseOne.h"
#include <iostream>
#include <sstream>
#include <vector>

void count_freqs(std::istream &text) {
    char l; //variable to hold the current letter 
    std::vector<Count> vect; //array of Count Structs
    while (text.get(l)) { //until the ends of the istream
        int i = 0; 
        while (i < vect.size()) { //go through the array
            //if already recorded instance of letter
            if (vect.at(i).letter == l) {
                vect.at(i).freq += 1; //increment the freq
                i = vect.size(); //finish the loop 
            }
            i++; //increment the loop variable 
        }
        //if i = exact size of vector than no matching letter in vector
        if (i == vect.size()) {
            Count newCount; //new Count variable
            newCount.letter = l; //set letter
            newCount.freq = 1; //set freq as 1
            vect.push_back(newCount); //add to the vector 
        }
    }
    //print the elements of the vector 
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect.at(i).letter << ": " << vect.at(i).freq << std::endl;
    }
}   

std::string serialize_tree(HuffmanTreeNode *root) {
    std::string str = "";
    //if the node is null, nothing to return
    if (root == nullptr) return "";
    //if the node is a leaf, return the value
    if (root->isLeaf()) {
        std::string letter(1,root->get_val());
        str = "L" + letter;
        return str;
    }
    str = "I" + serialize_tree(root->get_left()) + 
    serialize_tree(root->get_right());
    return str;
}

// HuffmanTreeNode *deserialize_tree(const std::string &s) {
//     std::istringstream iss(s);
//     HuffmanTreeNode *root = deserialize_tree_helper(iss);
//     return root;
// }

HuffmanTreeNode *deserialize_tree_helper(std::istringstream &iss) {
    char letter;
    iss.get(letter);
    if (letter == 'L') {
        char let;
        iss.get(let);
        HuffmanTreeNode *newNode = new HuffmanTreeNode(let, 0);
        return newNode;
    } else if (letter == 'I') {
        HuffmanTreeNode *left = deserialize_tree_helper(iss);
        HuffmanTreeNode *right = deserialize_tree_helper(iss);
        HuffmanTreeNode *newNode = new HuffmanTreeNode('\0', 0,left,right);
        return newNode;
    }
}



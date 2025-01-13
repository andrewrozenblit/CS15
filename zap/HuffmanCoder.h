/*
 *  HuffmanCoder.cpp
 *  Andrew Rozenblit 
 *  03/30/24
 *
 *  CS 15 Project 3 - Zap
 * Purpose:
 *  Interfance of the HuffmanCoder.cpp file. Shows the user all the availble 
 *  functions to call and the public varibales. The code takes in an inputed 
 *  text and either encodes it into a binary string using the Huffman Coding 
 *  method or decodes an input binary string using the Huffman Coding method.
 *
*/

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <vector>
#include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <fstream>
#include <utility>

class HuffmanCoder {
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
    
   public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);
    private:
        void count_freqs(std::istream &text);
        void printTree(HuffmanTreeNode *curr);
        void transfer_to_pq();
        void build_tree();
        void char_codes(HuffmanTreeNode *curr, std::string encode);
        void destructor_recurse_zap(HuffmanTreeNode *curr);
        std::string serialize_tree(HuffmanTreeNode *root);
        char covertFromBit(std::istringstream &iss, HuffmanTreeNode *curr);
        int find_in_vect(char val);
        HuffmanTreeNode *deserialize_tree_helper(std::istringstream &iss);
        struct Count{
            char letter;
            int freq;
            std::string encoding;
        };
        std::vector<Count> vect; //vector of Counts
        //priority queue 
        std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, 
        NodeComparator> my_pq;

};

#endif
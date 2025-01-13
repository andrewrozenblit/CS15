/*
 *  unit_test.h
 *  Andrew Rozenblit 
 *  03/25/24
 *
 *  CS 15 Project 3 - Zap
 *
 *  A unit testing file for the Zap project
 */


#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <sstream>
#include <string>
#include <cassert>
#include "ZapUtil.h"

//Functions testing countFreq

void normalTest() {
    std::string str = "Yeet";
    std::istringstream istr(str);
    count_freqs(istr);
}

void normalTest2() {
    std::string str = "Alexander";
    std::istringstream istr(str);
    count_freqs(istr);
}

//the text has multiple lines
void edgeCase1() {
    std::string str = "hi hi\nhi";
    std::istringstream istr(str);
    count_freqs(istr);
}

//only a singular space
void edgeCase2() {
    std::string str = " ";
    std::istringstream istr(str);
    count_freqs(istr);
}

//all the same letter
void edgeCase3() {
    std::string str = "AAAAA";
    std::istringstream istr(str);
    count_freqs(istr);
}

//serialize_tree tests

//uses example from spec and ZapUtil
void st1() {
    std::string tree = "IIILaLbILeLfILcLd";
    HuffmanTreeNode *root = deserialize_tree(tree);
    std::string tree1 = serialize_tree(root);
    std::cerr << tree;
    assert(tree == tree1);
}
void st2() {
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    std::string str = serialize_tree(root);
    std::cout << str << std::endl;
}


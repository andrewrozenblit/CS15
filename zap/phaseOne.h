#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>

#include "HuffmanTreeNode.h"


struct Count{
    char letter;
    int freq;
};
void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode *deserialize_tree_helper(std::istringstream &iss);


#endif
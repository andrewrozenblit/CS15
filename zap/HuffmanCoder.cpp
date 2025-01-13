/*
 *  HuffmanCoder.cpp
 *  Andrew Rozenblit 
 *  03/30/24
 *
 *  CS 15 Project 3 - Zap
 *
 *  Implementation of HuffmanCoder class. Main functionality is to process
 *  the inputted text and either build a tree and use it to encode the text, or
 *  take the inputted string to decode it and turn it into its original text.
 *   
 *
*/

#include "HuffmanCoder.h"

/*
 * name:      encoder
 * purpose:   codes text in the input file into a binary string and sends it to
 *            the output file 
 * arguments: a string, input_file, stores the name of the input file, a string
 *            the name of the output file, output_file
 * returns:   none
 * effects:   none
*/
void HuffmanCoder::encoder(const std::string &input_file, const std::string 
&output_file) {
    std::ifstream input;
    input.open(input_file); //open the text as an ifstream
    if (not input.is_open()) { //verify that it opened 
        throw std::runtime_error("Unable to open file " + input_file);
    }
    if(input.peek() == -1)  { //check if its empty
        std::cout << input_file + " is empty and cannot be compressed.\n";
        return;
    }
    count_freqs(input); //count the frequency of every letter in the text
    transfer_to_pq(); //convert the vector from count_freqs to a priority queue
    vect.clear(); //empty the vector
    build_tree(); //construct the tree
    input.close(); //close the file
    char_codes(my_pq.top(), ""); //fills vect with the letter and its encoding
    std::string final_encode = ""; //the final bit string
    input.open(input_file); //reopen the file to start from begining
    while (input.peek() != -1) {//goes to each letter and gets its encoding
        int index = find_in_vect(input.get()); //find the letter in vect
        final_encode += vect.at(index).encoding; //add the encoding
    }
    std::string serialize = serialize_tree(my_pq.top()); //serialize the tree
    BinaryIO instance;
    instance.writeFile(output_file,serialize,final_encode);
    std::cout << "Success! Encoded given text using " << final_encode.length()
     << " bits." << std::endl;
    input.close();
    destructor_recurse_zap(my_pq.top()); 
}

/*
 * name:      destructor_recurse_zap
 * purpose:   deletes the tree off the heap
 * arguments: a HuffmanTreeNode pointer of a node in the tree
 * returns:   none
 * effects:   deletes the tree
*/
void HuffmanCoder::destructor_recurse_zap(HuffmanTreeNode *curr) {
    if (curr == nullptr) return; //if nothing to delete return 
    else if (not curr->isLeaf()) { //if its not a leaf
        //delete subtrees first 
        destructor_recurse_zap(curr->get_left());
        destructor_recurse_zap(curr->get_right());
    }
    delete curr; //delete the node
}

/*
 * name:      count_freqs
 * purpose:   counts and stores the frequencies that each letter appears in the
 *            text 
 * arguments: an istream of the provided input
 * returns:   none
 * effects:   creates a vector of counts Structs 
*/
void HuffmanCoder::count_freqs(std::istream &text) {
    char l; //variable to hold the current letter 
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
} 

/*
 * name:      transfer_to_pq
 * purpose:   turns each Count type to a HuffmanTreeNode and pushes onto 
 *            priority queue
 * arguments: none
 * returns:   none
 * effects:   creates the leaf nodes for the tree   
*/
void HuffmanCoder::transfer_to_pq() {
    //go through each Count in vect
    for (int i = 0; i < vect.size(); i++) {
        //turn the Count into a HuffmanTreeNode pointer
        HuffmanTreeNode *node1 = new 
        HuffmanTreeNode(vect.at(i).letter,vect.at(i).freq);
        //push it onto the prority queue 
        my_pq.push(node1);
    }
}

/*
 * name:      build_tree
 * purpose:   builds the tree as specified by the Huffman Coding process
 * arguments: none
 * returns:   none
 * effects:   creates a tree with the more common letters close to the root 
*/
void HuffmanCoder::build_tree() {
    //go until there is one thing remaning on the priority queue (the root)
    while (my_pq.size() != 1) {
        //store least common element into node1
        HuffmanTreeNode *node1 = my_pq.top(); 
        my_pq.pop(); //remove it 
        //store next least common element into node1
        HuffmanTreeNode *node2 = my_pq.top();
        my_pq.pop(); //remove
        int sum = node1->get_freq() + node2->get_freq(); //sum the freqs
        //create new HuffmanTreeNode where node1 and node 2 are its subtrees
        HuffmanTreeNode *new_node = new HuffmanTreeNode('\0',sum,node1,node2);
        my_pq.push(new_node); //push the new node back onto priority queue
    }
}

/*
 * name:      char_codes
 * purpose:   fills vector vect with the letter and its encoding 
 * arguments: HuffmanTreeNode pointer and string of the previous part of the 
 *            encoding 
 * returns:   none
 * effects:   gets each letters encoding  
*/
void HuffmanCoder::char_codes(HuffmanTreeNode *curr, std::string encode) {
    if (curr->isLeaf()) {
        //create new Count
        Count newCount;
        newCount.letter = curr->get_val(); //set the value 
        if (encode == "") encode = "0"; //if tree only one node then encode = 0
        newCount.encoding = encode; //set the structs encoding member to encode
        vect.push_back(newCount); //push newCount onto vect
        return;
    } //else
    encode += "0"; //add 0 to the encoding and go down left
    char_codes(curr->get_left(),encode); 
    //swap that last 0 to a 1 and go down right
    encode[encode.length()-1] = '1';
    char_codes(curr->get_right(),encode);
}

/*
 * name:      find_in_vect
 * purpose:   finds the index of the struct storing the provided variable 
 * arguments: a char, val, telling the function what to find
 * returns:   an int storing the index
 * effects:   none
*/
int HuffmanCoder::find_in_vect(char val) {
    //go through each Count in vect
    for (int i = 0; i < vect.size(); i++) {
        //if that Count stores val
        if (vect.at(i).letter == val) {
            return i; 
        }
    } 
    //if not in vect
    return -1;
}

/*
 * name:      serialize_tree
 * purpose:   serializes the tree into Is and Ls with the letetr value  
 * arguments: HuffmanTreeNode pointer of the current node
 * returns:   a string storing the serialized tree 
 * effects:   none
*/
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *curr) {
    std::string str = "";
    //if the node is null, nothing to return
    if (curr == nullptr) return "";
    //if the node is a leaf, return the value
    if (curr->isLeaf()) {
        std::string letter(1,curr->get_val());
        str = "L" + letter;
        return str;
    }
    //if not a leaf than add I and go down left and right subtrees
    str = "I" + serialize_tree(curr->get_left()) + 
    serialize_tree(curr->get_right());
    return str; //return the string 
}

//DECODER

/*
 * name:      decoder
 * purpose:   decodes text in the input file into normal text and sends it to
 *            the output file 
 * arguments: a string, input_file, stores the name of the input file, a string
 *            the name of the output file, output_file
 * returns:   none 
 * effects:   decodes the input
*/
void HuffmanCoder::decoder(const std::string &input_file, 
const std::string &output_file) {
    BinaryIO instance;
    //get the bit string and serialized tree string
    std::pair<std::string,std::string> read = instance.readFile(input_file);
    std::string serialize = read.first;
    std::string bit = read.second;
    std::istringstream ser(serialize); //turns serialized string to stream
    //deserializes the tree, builds it, and stores root into root
    HuffmanTreeNode *root = deserialize_tree_helper(ser); 
    //turns bit string to stream
    std::istringstream bitstream(bit);
    std::string text = "";
    while (bitstream.peek() != -1) { //until the end of the bit string
        //converts the first couple of numbers into their corresponding letter
        text += covertFromBit(bitstream,root);
    } 
    std::ofstream outstream; //creates an ofstream 
    outstream.open(output_file); //open the file 
    outstream << text; //put the text into the output file
    outstream.close(); 
    destructor_recurse_zap(root); //delete all heap allocated memory 
}

/*
 * name:      deserialize_tree_helper
 * purpose:   constructs a tree based on a serialized string 
 * arguments: an istringstream of the serialized text
 * returns:   the root to the newly constructed tree 
 * effects:   creates a tree
*/
HuffmanTreeNode *HuffmanCoder::deserialize_tree_helper(std::istringstream &iss)
{
    char letter;
    iss.get(letter); //puts the letter currently on into letter
    if (letter == 'L') { //if a lead
        char let;
        iss.get(let); //get the value 
        //create a new HuffmanTreeNode
        HuffmanTreeNode *newNode = new HuffmanTreeNode(let, 0);
        return newNode;
    } else if (letter == 'I') { //if not a leaf
        //create the left side first
        HuffmanTreeNode *left = deserialize_tree_helper(iss); 
        //create the right side 
        HuffmanTreeNode *right = deserialize_tree_helper(iss);
        //initialize a newNode with the left and right subtrees
        HuffmanTreeNode *newNode = new HuffmanTreeNode('\0', 0,left,right);
        return newNode; //return the newly created node
    }
}

/*
 * name:      covertFromBit
 * purpose:   turns the first couple of the numbers into the corresponding 
 *            letter
 * arguments: an istringstream storing the bits, the current node of the tree
 * returns:   a char storing the letter the bits correspond to 
 * effects:   converts the bits to text
*/
char HuffmanCoder::covertFromBit(std::istringstream &iss,HuffmanTreeNode *curr) 
{
    //when the nodes a leaf return the value
    if(curr->isLeaf()) return curr->get_val();
    char bit;
    iss.get(bit); //put the next number into bit
    //if 0 then go right and if 1 then go left
    if (bit == '0') return covertFromBit(iss, curr->get_left());
    else if (bit == '1') return covertFromBit(iss, curr->get_right());
    //if stops mid way then tree can't be constructed
    else throw std::runtime_error("Encoding did not match Huffman tree.");
    return '\0';
}   
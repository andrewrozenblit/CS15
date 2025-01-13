#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>

class HuffmanCoder {
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
   public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);
};

#endif
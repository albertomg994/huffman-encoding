//
//  HuffmanTree.h
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <iostream>
#include <string>

using namespace std;

class HuffmanTree {
private:
    
    HuffmanTree* _iz;
    HuffmanTree* _dr;
    
protected:
    
    int _frec;
    
public:
    
    // Constructors
    HuffmanTree() : _iz(NULL), _frec(0), _dr(NULL) {}
    HuffmanTree(int frec) : _iz(NULL), _frec(frec), _dr(NULL) {}
    HuffmanTree(HuffmanTree* iz, HuffmanTree* dr) : _iz(iz), _dr(dr) {
        _frec = iz->_frec + dr->_frec;
    }
    
    // Destructor
    // ~HuffmanTree() {
    //     ...
    // }
    
    // Getters
    char frec() const { return _frec; }
    HuffmanTree* hijoIz() const { return _iz; }
    HuffmanTree* hijoDr() const { return _dr; }
    
    /**
     * Returns a string representation of tree's inorder traversal
     */
    string to_string() {
        return " HTr[frec: " + std::to_string(_frec) + "] " + _iz->to_string() + _dr->to_string();
    }
};

#endif /* HuffmanTree_h */

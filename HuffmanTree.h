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
protected:

    int _frec;
    bool _hoja;

public:

    // Constructors
    HuffmanTree(int frec = 0) : _frec(frec), _hoja(false) {}
    HuffmanTree(HuffmanTree* iz, HuffmanTree* dr) {
        _frec = iz->_frec + dr->_frec;
    }

    // Destructor - Should never be used. The good ones are ~HuffmanBranch() and ~HuffmanLeaf()
    ~HuffmanTree() {
        // Default is OK
    }

    // Getters
    char frec() const { return _frec; }
    virtual bool esHoja() const { return _hoja; }


    /**
     * Returns a string representation of tree's preorder traversal
     * This method should never be called. The good ones are inside HuffmanLeaf and HuffmanBranch
     */
    virtual string to_string() {
        return " HTr[frec: " + std::to_string(_frec) + "] ";
    }
};

#endif /* HuffmanTree_h */

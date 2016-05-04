//
//  HuffmanLeaf.h
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef HuffmanLeaf_h
#define HuffmanLeaf_h

#include <iostream>
#include <string>
#include "HuffmanTree.h"

using namespace std;

class HuffmanLeaf : public HuffmanTree {
private:
    
    char _c;    // Character in current node
    
public:
    
    // Constructor
    HuffmanLeaf(char c, int frec) : HuffmanTree(frec), _c(c) {}
    
    // Destructor
    ~HuffmanLeaf() {
        // Default is OK
    }
    
    // Getters
    char c() const { return _c; }
    
    /**
     * Returns a string representation of tree's inorder traversal
     * NOTE: since it's a leaf node, there's only need to print current node.
     */
    virtual string to_string() {
        return " HLf[c: " + std::to_string(_c) + ", f: " + std::to_string(_frec) + "] ";
    }
};

#endif /* HuffmanLeaf_h */

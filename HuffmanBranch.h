//
//  HuffmanBranch.h
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef HuffmanBranch_h
#define HuffmanBranch_h

#include <iostream>
#include <string>
#include "HuffmanTree.h"

using namespace std;

class HuffmanBranch : public HuffmanTree {
private:

    HuffmanTree* _iz;
    HuffmanTree* _dr;
    
public:
    
    // Constructor
    HuffmanBranch(HuffmanTree* iz, HuffmanTree* dr) : HuffmanTree(iz, dr), _iz(iz), _dr(dr) {}
    
    // Destructor
    // ~HuffmanBranch() {
    //     ...¿?
    // }
    
    // Getters
    HuffmanTree* hijoIz() const { return _iz; }
    HuffmanTree* hijoDr() const { return _dr; }
    
    /**
     * Returns a string representation of tree's inorder traversal
     */
    string to_string() {
        return " HBr[frec: " + std::to_string(_frec) + "] " + _iz->to_string() + _dr->to_string();
    }
};

#endif /* HuffmanBranch_h */

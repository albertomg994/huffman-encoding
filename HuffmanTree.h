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
    
public:
    
    // Constructors
    HuffmanTree(int frec = 0) : _frec(frec) {}
    HuffmanTree(HuffmanTree* iz, HuffmanTree* dr) {
        _frec = iz->_frec + dr->_frec;
    }
    
    // Destructor - Should never be used. The good ones are ~HuffmanBranch() and ~HuffmanLeaf()
    ~HuffmanTree() {
        // Default is OK
    }
    
    // Getters
    char frec() const { return _frec; }

    
    /**
     * Returns a string representation of tree's inorder traversal
     * This method should never be called. The good ones are inside HuffmanLeaf and HuffmanBranch
     */
    virtual string to_string() {
        return " HTr[frec: " + std::to_string(_frec) + "] ";
    }
    
    /**
     * Sobrecarga de los distintos operadores de comparación
     * Redefinimos los operadores al revés, porque queremos cojer los dos de MENOR FRECUENCIA
     */
    // *********************************************************************** //
    // Como al final usé la clase comparadora de punteros esto no es necesario //
    // *********************************************************************** //
    /*bool operator> (const HuffmanTree &other) {
        return _frec < other._frec;
    }
    
    bool operator>= (const HuffmanTree &other) {
        return _frec <= other._frec;
    }
    
    bool operator< (const HuffmanTree &other) {
        return _frec > other._frec;
    }
    
    bool operator<= (const HuffmanTree &other) {
        return _frec >= other._frec;
    }*/
};

#endif /* HuffmanTree_h */

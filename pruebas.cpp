//
//  pruebas.cpp
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 4/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanLeaf.h"
#include "HuffmanBranch.h"
#include <string>

using namespace std;

// HuffmanTree Constructors
/*
HuffmanTree(int frec = 0) : _frec(frec) {}
HuffmanTree(HuffmanTree* iz, HuffmanTree* dr) {
    _frec = iz->_frec + dr->_frec;
}
*/

// HuffmanLeaf Constructors
/*
HuffmanLeaf(char c, int frec) : HuffmanTree(frec), _c(c) {}

// Destructor
~HuffmanLeaf() {
    // Default is OK
}
 */

// HuffmanBranch Constructor
// HuffmanBranch(HuffmanTree* iz, HuffmanTree* dr) : HuffmanTree(iz, dr), _iz(iz), _dr(dr) {}

void pruebas_herencia() {

    /*HuffmanTree hf5(5);
    HuffmanTree hf6(6);
    
    HuffmanLeaf hl(1, 2);
    HuffmanBranch hb(&hf5, &hf6);
    
    cout << hf5.to_string() << endl;
    cout << hl.to_string() << endl;
    cout << hb.to_string() << endl;*/
    
    // Segunda parte
    
    HuffmanLeaf hl(2, 3);
    HuffmanTree ht = hl;
    cout << hl.to_string() << endl;
    cout << ht.to_string() << endl;
    
}

int main(int argc, const char * argv[]) {
    
    pruebas_herencia();
    return 0;
}

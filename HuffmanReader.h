//
//  HuffmanTree.h
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 6/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef HuffmanReader_h
#define HuffmanReader_h

#include <iostream>
#include <string>
#include "HuffmanTree.h"
#include "HuffmanBranch.h"
#include "HuffmanReader.h"

using namespace std;

class HuffmanReader {
public:

    /**
     * Read tree in ¿preorder?
     */
    static HuffmanTree* read() {
        return read_next();
    }

private:

    /**
     *
     */
    static HuffmanTree* read_next() {

        char type;

        // Read type of next node
        cin >> type;

        if (type == 'L') {
            // Esto realmente es el caso base de la recursión
            return (HuffmanTree*)readLeaf(); // Creo que el cast no es necesario
        }
        else { // type == 'B'
            // Y este es el caso recursivo, un HuffmanBranch nunca es el último nodo
            return (HuffmanTree*)readBranch();
        }
    }

    /**
     *
     */
    static HuffmanBranch* readBranch() {
        int frec;

        // Leemos los datos que nos corresponden
        cin >> frec;

        // Pero antes de invocar a nuestro  constructor debemos leer nuestros nodos hijos
        HuffmanTree* ht_iz = read_next();
        HuffmanTree* ht_dr = read_next();

        // Ahora ya tenemos todos los datos encesarios
        return new HuffmanBranch(ht_iz, ht_dr);
    }

    /**
     *
     */
    static HuffmanLeaf* readLeaf() {
        int frec;
        char c;

        // Leemos los datos de nuestro nodo
        cin >> c;
        cin >> frec;

        // Como HuffmanLeaf no tiene hijos, podemos invocar directamente a nuestro constructor
        return new HuffmanLeaf(c, frec);
    }
};

#endif /* HuffmanReader_h */

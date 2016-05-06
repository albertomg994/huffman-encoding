//
//  main.cpp
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include <iostream>
#include "Huffman.h"
#include "HuffmanReader.h"
#include <string>

using namespace std;

void encode();
void decode();

int main(int argc, const char * argv[]) {

    if (argc != 2) {
        cout << "Incorrect number of params (should be 1)" << endl;
        return -1;
    }

    string operation = argv[1];

    if (operation != "encode" && operation != "decode") {
        cout << "Invalid operation" << endl;
        return -1;
    }

    if (operation == "encode") encode();
    else if (operation == "decode") decode();

    return 0;
}

void encode() {
    int nCasos;
    string plain_text, coded_text;

    cin >> nCasos; cin.ignore();
    cout << " [DEBUG] Hay " << nCasos << " casos en total." << endl << " [DEBUG]" << endl;

    for (int i = 0; i < nCasos; i++) {
        getline(cin, plain_text);
        cout << " [DEBUG] ==================== Caso " << i+1 << " ====================" << endl;
        cout << " [DEBUG] Plain text: " << plain_text << endl;
        coded_text = Huffman::encode(plain_text);
        cout << coded_text << endl;
        cout << " [DEBUG] ================================================" << endl;
    }
}

void decode() {
    int nCasos;
    string encoded_text, plain_text;

    cout << "decoding..." << endl;

    cin >> nCasos; cin.ignore();

    for (int i = 0; i < nCasos; i++) {
        // Leer el texto codificado
        getline(cin, encoded_text);

        // Leer y reconstruir el árbol de huffman, que viene inorden
        // NOTA: tengo que distinguir entre HuffmanBranch y HuffmanLeaf
        HuffmanTree* ht = HuffmanReader::read();
        cout << ht->to_string() << endl;

        // Una vez que tenemos el texto y el árbol, decodificarlo
        plain_text = Huffman::decode(encoded_text, *ht);
        cout << plain_text << endl;

        //delete ht;
    }
}

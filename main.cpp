//
//  main.cpp
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include <iostream>
#include "Huffman.h"
#include <string>

using namespace std;

string leeTexto() {
    string texto;
    getline(cin, texto);
    return texto;
}

int main(int argc, const char * argv[]) {
    
    int nCasos;
    string plain_text, coded_text;
    
    cin >> nCasos;
    
    for (int i = 0; i < nCasos; i++) {
        plain_text = leeTexto();
        coded_text = Huffman::encode(plain_text);
        
        cout << "------------ Caso " << i+1 << " ------------" << endl;
        cout << "Plain text: " << plain_text << endl;
        cout << "Coded text: " << coded_text << endl;
        cout << "--------------------------------" << endl;
    }
    
    return 0;
}

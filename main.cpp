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

string leeCaso() {
    string texto;
    cin.ignore('\n');
    getline(cin, texto);
    return texto;
}

int main(int argc, const char * argv[]) {
    
    int nCasos;
    string plain_text, coded_text;
    
    cin >> nCasos; cin.ignore();
    cout << " [DEBUG] Hay " << nCasos << " casos en total." << endl << " [DEBUG]" << endl;
    
    for (int i = 0; i < nCasos; i++) {
        getline(cin, plain_text);
        //cin.ignore();
        cout << " [DEBUG] ==================== Caso " << i+1 << " ====================" << endl;
        cout << " [DEBUG] Plain text: " << plain_text << endl;
        coded_text = Huffman::encode(plain_text);
        cout << coded_text << endl;
        cout << " [DEBUG] ================================================" << endl;
    }
    
    return 0;
}

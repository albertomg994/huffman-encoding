//
//  Huffman.h
//  T9-10-Codificacion-Huffman
//
//  Created by Alberto Miedes on 29/4/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Huffman_h
#define Huffman_h

#include <iostream>
#include <string>
#include "HuffmanTree.h"
#include "HuffmanBranch.h"
#include "HuffmanLeaf.h"
#include <queue>

#define TABLE_SIZE 128

using namespace std;

/**
 * Because whe use a fixed size array as the frequency table for each character,
 * whe only support the original ASCII talbe characters (128). Thus, characters
 * with (code < 0) || (code >= 128) must be rejected by the algorithm.
 */
class UnsupportedCharacterException {};

/**
 * Class used to compare HuffmanTree nodes in the stl::priority_queue variable
 * used in 'frec_table_to_HuffTree method'.
 */
class CompareHuffmanNodes {
public:
    bool operator() (HuffmanTree ht1, HuffmanTree ht2) {
        return (ht1.frec() >= ht2.frec());
    }
};

/**
 * Main class used to encode/decode text following the Huffman encoding algorithm.
 */
class Huffman {
public:
    
    /**
     * @return encoded text
     */
    static string encode(const string &plain_text) {
        
        int frec_table[TABLE_SIZE];
        int code_table[TABLE_SIZE];
        string coded_text;
        
        init_frec_table(frec_table);
        
        print_frec_table(frec_table, false);
        
        text_to_frec_table(plain_text, frec_table);
        
        print_frec_table(frec_table, false);
        
        HuffmanTree* ht = frec_table_to_HuffTree(frec_table);
        huffTree_to_code_table(*ht, code_table);
        coded_text = code_table_to_coded_text(code_table);
        
        return coded_text;
    }
    
    /**
     * @return decoded text
     */
    static string decode(const string &encoded_text) {
        return "<plain text>";
    }
    
private:
    
    /**
     * A partir de un texto plano, rellena su tabla de frecuencias.
     * @param s String que contiene el texto sin codificar
     * @param frecTable Tabla de frecuencias de caracteres (los arrays son siempre referencias en C++)
     */
    static void text_to_frec_table(const string &s, int frec_table[TABLE_SIZE]) {
        
        char c; int ascii;
        string::const_iterator it = s.cbegin();
        
        while (it != s.cend()) {
            c = *it;
            ascii = (int)c;
            
            if (ascii < 0 || ascii > 128) throw UnsupportedCharacterException();
            /*DEBUG*/ //cout << "ASCII[" << c << "]=" << ascii << endl;
            frec_table[ascii]++;
            
            it++;
        }
    }
    
    /**
     * A partir de una tabla de frecuencias, obtiene el árbol de Huffman
     * @param frecTable
     * @return pointer to HuffmanTree root
     */
    static HuffmanTree* frec_table_to_HuffTree(const int frec_table[TABLE_SIZE]) {
        
        // Utiliza una cola con prioridad (usaremos las operaciones push y pop).
        // Vamos metiendo elementos, y cuando pidamos el máximo nos dará el máximo
        //
        //  1. Recorro la tabla de frecuencias, para cada letra hago un new Hoja() con esa letra y esa frecuencia, y lo guardo en la cola de prioridad (es una cola de prioridad de árboles)
        //  2. Un bucle que (mientras queden elementos en la cola con prioridad), coge 2 y forma un árbol con esos dos, y vuelve a insertarlo.
        
        priority_queue<HuffmanTree*, CompareHuffmanNodes> pq;
        
        // Rellenamos la cola de prioridad con nodos hoja
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (frec_table[i] > 0) pq.push(new HuffmanLeaf(i, frec_table[i]));  // NOTA: aquí construyo las hojas
        }
        
        while(pq.size() > 1) {
            // Get two elements with highest frequency
            HuffmanTree* frst = pq.top(); pq.pop();
            HuffmanTree* scnd = pq.top(); pq.pop();
            
            pq.push(new HuffmanBranch(frst, scnd));
        }
        
        return pq.top();
    }
    
    /**
     *
     */
    static void huffTree_to_code_table(const HuffmanTree &ht, int code_table[TABLE_SIZE]) {
        
    }
    
    /**
     *
     */
    static string code_table_to_coded_text(int code_table[TABLE_SIZE]) {
        return "";
    }
    
    /**
     * Inicializa la tabla de frecuencias de caracteres toda a 0.
     */
    static void init_frec_table(int frec_table[TABLE_SIZE]) {
        for (int i = 0; i < TABLE_SIZE; i++) frec_table[i] = 0;
    }
    
    /**
     * Imprime la tabla de frecuencias
     */
    static void print_frec_table(int frec_table[TABLE_SIZE], bool include_blanks) {
        int i = 0;
        for (; i < TABLE_SIZE-1; i++) {
            if (include_blanks || frec_table[i] != 0) cout << "[" << char(i) << "]=" << frec_table[i] << "  ";
        }
        if (include_blanks || frec_table[i] != 0) cout << "[" << char(i) << "]=" << frec_table[i];
        cout << endl;
    }
    
};

#endif /* Huffman_h */

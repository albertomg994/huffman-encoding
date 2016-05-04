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
#include <vector>

#define TABLE_SIZE 128

using namespace std;

/**
 * Because whe use a fixed size array as the frequency table for each character,
 * whe only support the original ASCII talbe characters (128). Thus, characters
 * with (code < 0) || (code >= 128) must be rejected by the algorithm.
 */
class UnsupportedCharacterException {};
class DebugException {};

/**
 * Class used to compare HuffmanTree nodes in the stl::priority_queue variable
 * used in 'frec_table_to_HuffTree method'.
 */
class CompareHuffmanNodes {
public:
    bool operator() (const HuffmanTree &ht1, const HuffmanTree &ht2) const {
        return (ht1.frec() >= ht2.frec());
    }
};

/**
 * Otro comparador de HuffmanTrees pero orientado a punteros
 */
class CompareHuffmanNodesPointers {
public:
    bool operator() (const HuffmanTree* ht1, const HuffmanTree* ht2) const {
        return (ht1->frec() >= ht2->frec());
    }
};

/**
 * Prints content of a std::priority_queue
 * NOTE: since the only way to iterate through a std::priority_queue is making
 * succesive 'pops', the parameter is passed by copy.
 */
void print_pq(std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>, CompareHuffmanNodesPointers> pq){
    HuffmanTree* ptr;
    cout << "print_pq()..." << endl;
    while(!pq.empty()) {
        ptr = pq.top();
        cout << ptr->to_string() << ' ';
        pq.pop();
    }
    cout << endl;
}

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
        
        // 1st. step
        cout << "Inicio 1er paso. Generando la tabla de frecuencias." << endl;
        text_to_frec_table(plain_text, frec_table);
        //cout << "Imprimiendo la tabla de frecuencias:" << endl;
        print_frec_table(frec_table, false);
        cout << "Final 1er paso. Generada la tabla de frecuencias." << endl << endl;
        
        // 2nd. step
        cout << "Inicio 2o paso. Generando el HuffmanTree." << endl;
        HuffmanTree* ht = frec_table_to_HuffTree(frec_table);
        cout << ht->to_string() << endl;
        cout << "Final 2o paso. Generado el HuffmanTree." << endl << endl;
        
        // 3rd. step
        huffTree_to_code_table(*ht, code_table);
        
        // 4th. step
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
        
        // Opción 4 - Teniendo en cuenta que he redefinido el operador de comparación
        
        /*************************************************************************************/
        /* Que no la instanciemos con punteros, pq el operadro de orden cree que no funciona */
        //bool operator()(const HuffmanTree &h1, const HuffmanTree &h2) {
            
        //}
        //std::priority_queue<HuffmanTree> pq; // Hacerlo así
        /*************************************************************************************/
        
        //std::priority_queue<HuffmanTree*> pq;
        
        // Versión instanciando con punteros y un comparador orientado a punteros
        std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>, CompareHuffmanNodesPointers> pq;
        
        // Rellenamos la cola de prioridad con nodos hoja
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (frec_table[i] > 0) {
                HuffmanLeaf* hl_aux = new HuffmanLeaf(i, frec_table[i]);
                //cout << "new HuffmanLeaf(" << i << ", " << frec_table[i] << ") = " << aux->to_string() << endl;
                pq.push(hl_aux);  // NOTA: aquí construyo las hojas
                //cout << "Se ha hecho un push de: " << (pq.top())->to_string() << endl;, cuidado el top() está ordenado por prioridad
            }
        }
        
        // Imprimimos la cola de prioridad, para depurar:
        cout << "La cola con prioridad tiene un tamaño de: " << pq.size() << endl;
        print_pq(pq);
        if (pq.empty()) throw DebugException();
        
        HuffmanBranch* hb_aux;
        while(pq.size() > 1) {
            // Get two elements with highest frequency
            HuffmanTree* frst = pq.top(); pq.pop();
            HuffmanTree* scnd = pq.top(); pq.pop();
            
            hb_aux = new HuffmanBranch(frst, scnd);
            pq.push(hb_aux);
        }
        
        //cout << "Imprimo el único elemento que debería quedar en la cola con prioridad: " << endl;
        //cout << (pq.top())->to_string() << endl;
        // CUIDADO, ÑAPA!!

        //
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
     * Initializes all frequencies in table to 0.
     */
    static void init_frec_table(int frec_table[TABLE_SIZE]) {
        for (int i = 0; i < TABLE_SIZE; i++) frec_table[i] = 0;
    }
    
    /**
     * Prints frequencies table
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

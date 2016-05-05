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
#include <list>
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
    cout << "print_pq(): ";
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
        list<bool> code_table[TABLE_SIZE];
        string coded_text;
        
        init_frec_table(frec_table);
        
        // 1st. step
        cout << " [DEBUG] Inicio 1er paso. Generando la tabla de frecuencias." << endl;
        cout << " [DEBUG] ------------------------------------------------------------" << endl;
        text_to_frec_table(plain_text, frec_table);
        cout << " [DEBUG] "; print_frec_table(frec_table, false);
        cout << " [DEBUG] << final 1er paso >>" << endl << " [DEBUG]" << endl;
        
        // 2nd. step
        cout << " [DEBUG] Inicio 2o paso. Generando el HuffmanTree." << endl;
        cout << " [DEBUG] ------------------------------------------------------------" << endl;
        HuffmanTree* ht = frec_table_to_HuffTree(frec_table);
        cout << " [DEBUG] Printing HuffmanTree: " << ht->to_string() << endl;
        cout << " [DEBUG] << final 2o paso >>" << endl << " [DEBUG]" << endl;
        
        // 3rd. step
        cout << " [DEBUG] Inicio 3er paso. Generando tabla de códigos." << endl;
        cout << " [DEBUG] ------------------------------------------------------------" << endl;
        huffTree_to_code_table(ht, code_table);
        cout << " [DEBUG] Printing code_table: " << endl; print_code_table(code_table);
        cout << " [DEBUG] << final 3er paso >>" << endl << " [DEBUG]" << endl;
        
        // 4th. step
        cout << " [DEBUG] Inicio 4º paso. Sustituyendo caracteres por sus códigos." << endl;
        cout << " [DEBUG] ------------------------------------------------------------" << endl;
        coded_text = code_table_to_coded_text(code_table, plain_text);
        cout << " [DEBUG] << final 4º paso >>" << endl << " [DEBUG]" << endl;
        
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
            frec_table[ascii]++;
            
            it++;
        }
    }
    
    /**
     * A partir de una tabla de frecuencias, obtiene el árbol de Huffman.
     *  1. Recorro la table de frecuencias, para cada letra hago un new Hoja() con esa letra y esa frecuencia, y lo guardo en la cola de prioridad.
     *  2. Un bucle que (mientras queden elementos en la cola con prioridad), coge 2 y forma un árbol con esos dos, y vuelve a insertarlo.
     *
     * @param frecTable
     * @return pointer to HuffmanTree root
     */
    static HuffmanTree* frec_table_to_HuffTree(const int frec_table[TABLE_SIZE]) {
        
        // Versión instanciando con punteros y un comparador orientado a punteros
        std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>, CompareHuffmanNodesPointers> pq;
        
        // Rellenamos la cola de prioridad con nodos hoja
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (frec_table[i] > 0) {
                HuffmanLeaf* hl_aux = new HuffmanLeaf(i, frec_table[i]);
                pq.push(hl_aux);
            }
        }
        
        cout << " [DEBUG] La cola con prioridad tiene un tamaño de: " << pq.size() << endl;
        cout << " [DEBUG] "; print_pq(pq);
        
        if (pq.empty()) throw DebugException();
        
        HuffmanBranch* hb_aux;
        while(pq.size() > 1) {
            // Get two elements with highest frequency
            HuffmanTree* frst = pq.top(); pq.pop();
            HuffmanTree* scnd = pq.top(); pq.pop();
            
            hb_aux = new HuffmanBranch(frst, scnd);
            pq.push(hb_aux);
        }

        return pq.top();
    }
    
    /**
     * Auxiliary recursive function used by huffTree_to_code_table to assign variable legth codes to each
     * character in the HuffmanTree.
     *
     * @param ht Pointer to the HuffmanTree
     * @param current_code Queue which keeps track of our current position in the tree, which will determine
     *        the code for each leaf node.
     * @param code_table Array containig all variable-lenth codes.
     */
    static void getCodesAux(HuffmanTree* ht, list<bool> &current_code, list<bool> code_table[TABLE_SIZE]){
        
        HuffmanLeaf* hl;
        HuffmanBranch* hb;
        
        //cout << "getCodesAux" << endl;
        
        // Si es una hoja, guardar current_code como su código
        if (ht->esHoja()) {
            hl = (HuffmanLeaf*)ht;
            //cout << "getCodesAux ha llegado a un nodo hoja: " << hl->to_string() << endl;
            if (current_code.empty()) current_code.push_back(0); // Este será el código asignado al primer carácter. Hay que inicializar porque si el plain_text solo tiene un caracter peta...
            char c = hl->c();
            // Copy current_code into corresponding position of code_table
            code_table[(int)c].assign(current_code.begin(), current_code.end());
        }
        // Si es un nodo 'intermedio' (rama)
        else {
            hb = (HuffmanBranch*)ht;
            // Explorar subárbol izquierdo
            current_code.push_back(false);
            getCodesAux(hb->hijoIz(), current_code, code_table);
            current_code.pop_back();
            // Explorar subárbol derecho
            current_code.push_back(true);
            getCodesAux(hb->hijoDr(), current_code, code_table);
            current_code.pop_back();
        }
    }
    
    /**
     * Obtiene el código de longitud variable para cada carácter a partir de un HuffmanTree
     *
     * @param ht Puntero al HuffmanTree a partir del cual hay que obtener los códigos para cada carácter.
     * @param code_table Array de 'queue', donde cada componente es el código para un carácter.
     */
    static void huffTree_to_code_table(HuffmanTree* ht, list<bool> code_table[TABLE_SIZE]) {
        // Recorrer el árbol por completo, guardando en cada momento si vamos a la izq o dcha para guardar el código en la tabla
        list<bool> current_code;
        getCodesAux(ht, current_code, code_table);
    }
    
    /**
     * Generates coded text by making a substitution of each character in the plain_text by
     * its own variable-length code.
     *
     * @param code_table Const referene to code_table
     */
    static string code_table_to_coded_text(list<bool> code_table[TABLE_SIZE], const string &plain_text) {
        
        string ret = "";
        char curr_char;
        
        string::const_iterator it = plain_text.cbegin();
        while (it != plain_text.cend()) {
            curr_char = *it;
            ret.append(char_to_code(curr_char, code_table));
            it++;
        }
        
        return ret;
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
        cout << "print_frec_table(): ";
        int i = 0;
        for (; i < TABLE_SIZE-1; i++) {
            if (include_blanks || frec_table[i] != 0) cout << "[" << char(i) << "]=" << frec_table[i] << "  ";
        }
        if (include_blanks || frec_table[i] != 0) cout << "[" << char(i) << "]=" << frec_table[i];
        cout << endl;
    }
    
    /**
     * Prints code_table
     */
    static void print_code_table(list<bool> code_table[TABLE_SIZE]) {
        
        list<bool>* q_ptr;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            q_ptr = &(code_table[i]);
            if (q_ptr != NULL && q_ptr->size()>0) {
                cout << " [DEBUG] code_table[" << i << "]: "; // Podría poner char(i), pero entonces se lía con los tabuladores, EOF, etc. al imprimir
                list<bool>::const_iterator it = q_ptr->cbegin();
                while (it != q_ptr->cend()) {
                    if (*it) cout << "1";
                    else cout << "0";
                    it++;
                }
                cout << endl;
            }
        }
    }
    
    /**
     * string representation of one variable-length code (i.e. print contents of list<bool>)
     */
    static string char_to_code(char c, list<bool> code_table[TABLE_SIZE]) {
        
        if (int(c) < 0 || int(c) >= 128) throw UnsupportedCharacterException();
        
        string ret = "";
        list<bool>* code = &code_table[c];
        
        list<bool>::const_iterator it = code->cbegin();
        while (it != code->cend()) {
            if (*it) ret.push_back('1');
            else ret.push_back('0');
            it++;
        }
        
        return ret;
    }
    
    
};

#endif /* Huffman_h */

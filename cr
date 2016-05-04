#!/bin/bash
g++ -std=c++11 Huffman.h HuffmanTree.h HuffmanBranch.h HuffmanLeaf.h main.cpp
./a.out < entrada.in > salida.out
cat salida.out

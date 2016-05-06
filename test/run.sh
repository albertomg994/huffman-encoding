#!/bin/bash
# Compliles project and runs all tests
# Author: Alberto Miedes Garcés (c) 5/05/2016

# Setup
# ------------------------------------------------------------------------------

# Test directory setup
mkdir -p tmp

# Compile application
g++ -std=c++11 ../main.cpp -o huffman_test

# Select tests to run
# ------------------------------------------------------------------------------

# Encoding tests
enc_caso_1=true
enc_caso_2=true
enc_caso_3=true
enc_caso_4=false

# Decoding tests
dec_simple_1=false

# Run encoding tests
# ------------------------------------------------------------------------------

# Run test 1
if [ "$enc_caso_1" = true ] ; then
    echo "Running encoding test 1..."
    ./huffman_test < encode/caso-1.in | grep -v "[DEBUG]" > tmp/caso-1.out
    diff encode/caso-1.out.sample tmp/caso-1.out
fi

# Run test 2
if [ "$enc_caso_2" = true ] ; then
    echo "Running encoding test 2..."
    ./huffman_test < encode/caso-2.in | grep -v "[DEBUG]" > tmp/caso-2.out
    diff encode/caso-2.out.sample tmp/caso-2.out
fi

# Run test 3
if [ "$enc_caso_3" = true ] ; then
    echo "Running encoding test 3..."
    ./huffman_test < encode/caso-3.in | grep -v "[DEBUG]" > tmp/caso-3.out
    diff encode/caso-3.out.sample tmp/caso-3.out
fi

# Run test 4
if [ "$enc_caso_4" = true ] ; then
    echo "Running encoding test 4..."
    ./huffman_test < encode/caso-4.in | grep -v "[DEBUG]" > tmp/caso-4.out
    diff encode/caso-4.out.sample tmp/caso-4.out
fi

# Run decoding tests
# ------------------------------------------------------------------------------

# Run test 1
if [ "$dec_simple_1" = true ] ; then
    echo "Running decoding test 1..."
    ./huffman_test < deencode/decode-simple-1.in | grep -v "[DEBUG]" > tmp/decode-simple-1.out
    diff decode/decode-simple-1.out.sample tmp/decode-simple-1.out
fi

# Cleaning
# ------------------------------------------------------------------------------
rm -f huffman_test

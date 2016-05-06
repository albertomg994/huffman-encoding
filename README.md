# Huffman Enconding - Práctica Estructura de Datos y Algoritmos

Clase que implementa en C++ un algoritmo de compresión basado en la codificación de Huffman.

## Compiling and running

To compile:

```
./compile
```

### Encoding

To encode some text, create a file following this pattern:

```
2
Example text one
This is another different example
```

* The first line indicates the number of "cases" (strings to be encoded)
* Each one of the following lines represents a string to be encoded

To process it:

```
./huffman encode < your_input_file | grep -v "[DEBUG]" > output_file
```

### Decoding

* (!!) Not fully working

To decode some text, create a file following this pattern:

```
1
101001011
B 6 B 3 L c 1 L b 2 L a 3
```
* The first line indicates the number of "cases" (strings to be decoded)
* Each case consists of two lines:
  * The first one contains the encoded text
  * The second one the HuffmanTree (B: branch, L: leaf) - B's are followed by their frequency and L's by character + frequency

To process it:

```
./huffman decode < your_input_file | grep -v "[DEBUG]" > output_file
```
## Testing

To run application tests:

```
./rtest
```

## TODOs:

* Decodificación
* Liberar la memoria (hacer los constructores pertinentes) para el HuffmanTree
* Limpiar código
* Batería de pruebas para deocdificación

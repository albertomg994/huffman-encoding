# Huffman Enconding - Práctica Estructura de Datos y Algoritmos

Clase que implementa en C++ un algoritmo de compresión basado en la codificación de Huffman.

## Compiling and running

To compile:

```
./compile
```

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
./huffman < your_input_file | grep -v "[DEBUG]" > output_file
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
* Lectura y escritura directamente en fichero ¿?

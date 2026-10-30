#ifndef LINEA_H
#define LINEA_H

// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// definiciones.hS
// Modulo para definiciones generales del proyecto como constantes, etc.



linea crearLinea();
void reservarCadena(linea l, int length);
void copiarCadena(linea l, Cadena palabra);
char* getPalabra(linea l);
void borrarPalabra(linea l);
int lengthCadena(linea l);
int compararCadena(Cadena palabra, Cadena palabra2);
TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar);

linea Tail(linea l);
void SetTail(linea l, linea sig);
linea Snoc(linea l);
linea Cons(linea l);
bool isEmpty(linea l);
void borrarLinea(linea l);

#endif

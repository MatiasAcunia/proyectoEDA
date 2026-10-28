#ifndef DICCIONARIO_H
#define DICCIONARIO_H

// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// definiciones.hS
// Modulo para definiciones generales del proyecto como constantes, etc.

typedef struct diccionario * Diccionario;
typedef struct nodo_diccionario * nodoD;

Diccionario crearDic();
nodoD getRaiz(Diccionario d);
int getnPalabras(Diccionario d);
void setnPalabras(Diccionario d, int n);
void setRaiz(Diccionario d);
void borrarDic(Diccionario d);
bool isEmptyDic(Diccionario d);

nodoD crearDiccionario();
nodoD subiz(nodoD d);
nodoD subde(nodoD d);
bool isEmptyNodoD(nodoD d);
void borrarNodoD(nodoD d);

void reservarCadena(nodoD d, int length);
Cadena copiarCadena(nodoD d, Cadena palabra);
char* getPalabra(nodoD d);
void borrarPalabra(nodoD d);
int lengthCadena(nodoD d);
int compararCadena(Cadena palabra, Cadena palabra2);

#endif

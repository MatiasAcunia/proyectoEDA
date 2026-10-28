#ifndef TEXTO_H
#define TEXTO_H

#include "linea.h"


// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// definiciones.hS
// Modulo para definiciones generales del proyecto como constantes, etc.

struct nodo_texto;
struct nodo_linea;

typedef struct nodo_texto * texto;

texto crearTexto();

int getNPalabras(texto t);

texto Tail(texto t);

linea getInicio(texto t);

linea getFin(texto t);

void setNPalabras(texto t, int n_palabras);

void setTail(texto t, texto sig);

void setInicio(texto t, linea inicio);

void setFin(texto t, linea fin);

texto cons(texto t);

texto snoc(texto t);

bool isEmpty(texto t);

void borrar(texto t);

#endif

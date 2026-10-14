#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// definiciones.h
// Modulo para definiciones generales del proyecto como constantes, etc.

enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum _retorno TipoRetorno;

typedef struct Editor * Archivo;

typedef struct nodo_editor * editor;

typedef struct nodo_linea * Linea;

typedef struct diccionario * Diccionario;

typedef struct nodo_diccionario * nodoD;

typedef unsigned int Posicion;

typedef char* Cadena;


#define MAX_COMANDO 75
#define MAX_CANT_PALABRAS_X_LINEA 3
#define MAX_CANT_ULTIMAS_PALABRAS 3

#endif


// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// editor.c
// Modulo de implementacion de editor.

#include "editor.h"
// Incluir los modulos realizados.
#include <string.h>
#include <iostream>

using namespace std;

//Estructura para el manejo de la linea individual; nodo de Editor; lista simplemente enlazada
struct nodo_texto{
	int n_palabras;
	texto sig;
	linea inicio, fin;
	
};


// get set atributos, borrado, head, tail, snoc, cons, isEmpty 
texto crearTexto(){
	
	texto t = new(nodo_texto);
	
	t->fin = NULL;
	t->inicio = NULL;
	t->n_palabras = 0;
	t->sig = NULL;
	
	return t;
}


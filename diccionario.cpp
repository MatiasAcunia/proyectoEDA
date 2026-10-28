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

//Estructura para el manejo de diccionario encapsulado; 
struct diccionario {
	nodoD raiz;
	int nPalabras;
	

};

//Estructura de nodos de diccionario; ABB
struct nodo_diccionario{
	Cadena palabra;
	nodoD iz, de;
	int tope;
};


// get set atributos, borrado
Diccionario crearDic() {
	
	Diccionario D = new(diccionario);

	D->nPalabras = 0;
	D->raiz = NULL;

	return D;
}

// get set atributos (subiz y subde), isEmpty, dato, borrar, insertar 
nodoD crearDiccionario(){

	nodoD d = new(nodo_diccionario);
	
	d->de = NULL;
	d->iz = NULL;
	d->tope = -1;

	return d;
}



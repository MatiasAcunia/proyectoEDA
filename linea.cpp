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

//Estructura para el manejo de palabras; nodo de linea; lista simplemente enlazada
struct nodo_linea{
	Cadena palabra;
	linea sig;
};

// get set atributos, borrado, head, tail, snoc, cons, isEmpty, añadir y borrar palabra
linea crearLinea(){
	linea l = new(nodo_linea);
	l->sig = NULL;
	
	return l;
}



TipoRetorno InsertarLinea(editor & e){
// Inserta una nueva línea vacía al final del texto.
// Este requerimiento debe ser resuelto en O(1) peor caso.
// Ver más detalles en la letra del obligatorio.
	
    texto nE = crearNodoEditor();
	if (e->cant_Lineas > 0) {
		e->cola->sig = nE;

	}else{
		e->cabeza = nE;

	} 
	e->cola = nE;
	e->cant_Lineas++;

	return OK;
}

TipoRetorno InsertarLineaEnPosicion(editor & e, Posicion posicionLinea){
// Inserta una nueva línea vacía en la posición indicada.
// Ver más detalles en la letra del obligatorio.
	if(posicionLinea < 0 || posicionLinea > e->cant_Lineas){
		return ERROR;
	}else{
		texto nuevo = crearNodoEditor();

		if(e->cant_Lineas == 0){
			// vacio
			e->cabeza = nuevo;
			e->cola = nuevo;
		}else if(posicionLinea == 0){
			// al inicio
			nuevo->sig = e->cabeza;
			e->cabeza = nuevo;
		}else if(e->cant_Lineas == posicionLinea){
			// al final
			e->cola->sig = nuevo;
			e->cola = nuevo;
		}else{
			// al medio
			texto it = e->cabeza;
			for(int i = 0; i < posicionLinea - 1; i++){
				it = it->sig;
			}
			nuevo->sig = it->sig;
			it->sig = nuevo;
		}
		
		e->cant_Lineas++; 
	}
	return OK;
}

TipoRetorno BorrarLinea(editor & e, Posicion posicionLinea){
// Borra la línea en la posición indicada.
// Ver más detalles en la letra del obligatorio.
	if(posicionLinea < 0 || posicionLinea >= e->cant_Lineas){
		return ERROR;
	}else{
	if(e->cant_Lineas == 0){
			// vacio
			return ERROR;

	}else if(posicionLinea == 0){
		// al inicio
		texto temp = e->cabeza;
		if (e->cant_Lineas > 1) {
			e->cabeza = e->cabeza->sig;
		}else {
			e->cabeza = NULL;
			e->cola = NULL;
		}	
		delete temp;

	}else if(e->cant_Lineas - 1 == posicionLinea){
		// al final
		texto temp = e->cola;

		if (e->cant_Lineas > 1) {
		texto it = e->cabeza;
		for(int i = 0; i < posicionLinea - 1; i++){
			it = it->sig;
		}
		e->cola = it;
		e->cola->sig = NULL;
	    }else{
			e->cabeza = NULL;
			e->cola = NULL;

		}

		delete temp;
		
	}else{
		// al medio
		texto it = e->cabeza;
		for(int i = 0; i < posicionLinea - 1; i++){
			it = it->sig;
		}
		texto temp = it->sig;
		it->sig = temp->sig;
		delete temp;
	}
	
	e->cant_Lineas--;
	}
	return OK;
}

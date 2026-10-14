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

//Estructura que encapsula al archivo entero
struct Editor {
	nodoE cabeza, cola;
	int cant_Lineas;
};


//Estructura para el manejo de la linea individual; nodo de Editor; lista simplemente enlazada
struct nodo_editor{

	int n_palabras;
	nodoE sig;
	Linea inicio, fin;
	
};

//Estructura para el manejo de palabras; nodo de linea; lista simplemente enlazada
struct nodo_linea{
	Cadena palabra;
	Linea sig;
	int tope;
};

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



editor crearEditor(){

	editor E = new(Editor);
	
	E->cabeza = NULL;
	E->cola = NULL;
	E->cant_Lineas = 0;

	return E;
}

nodoE crearNodoEditor(){

	nodoE e = new(nodo_editor);

	e->fin = NULL;
	e->inicio = NULL;
	e->n_palabras = 0;
	e->sig = NULL;
	
	return e;
}


Linea crearLinea(){

	Linea l = new(nodo_linea);

	l->sig = NULL;
	l->tope = -1;

	return l;
}

Diccionario crearDic() {

	Diccionario D = new(diccionario);

	D->nPalabras = 0;
	D->raiz = NULL;

	return D;
}

nodoD crearDiccionario(){

	nodoD d = new(nodo_diccionario);
	
	d->de = NULL;
	d->iz = NULL;
	d->tope = -1;

	return d;
}


TipoRetorno InsertarLinea(editor & e){
// Inserta una nueva línea vacía al final del texto.
// Este requerimiento debe ser resuelto en O(1) peor caso.
// Ver más detalles en la letra del obligatorio.
	
    nodoE nE = crearNodoEditor();
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
	if(posicionLinea < 0 && posicionLinea >= e->cant_Lineas){
		return ERROR;
	}else{
		nodoE nuevo = crearNodoEditor();

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
			nodoE it = e->cabeza;
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
	return NO_IMPLEMENTADA;
}

TipoRetorno BorrarTodo(editor & e){
// Borra todas las líneas del texto.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar){
// Borra todas las ocurrencias de una palabra en el texto.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ImprimirTexto(editor & e){
// Imprime el texto por pantalla.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ComprimirTexto(editor & e){
// Comprime las palabras del texto. Para implementar esta operación no debe generarse un nuevo documento.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar){
// Inserta una palabra en una línea.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra){
// Borra la palabra en la posición indicada.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(editor & e, Posicion posicionLinea, Cadena palabraABorrar){
// Borra todas las ocurrencias de una palabra en la línea indicada.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ImprimirLinea(editor & e, Posicion posicionLinea){
// Imprime la línea por pantalla.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno IngresarPalabraDiccionario(editor & e, Cadena palabraAIngresar){
// Agrega una palabra al diccionario.
// Esta operación debe realizarse en a lo sumo O(log n) promedio.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno BorrarPalabraDiccionario(editor & e, Cadena palabraABorrar){
// Borra una palabra del diccionario.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ImprimirDiccionario(editor & e){
// Muestra las palabras del diccionario alfabéticamente.
// Esta operación debe realizarse en O(n) peor caso.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ImprimirTextoIncorrecto(editor & e){
// Muestra las palabras del texto que no se encuentran en el diccionario.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno ImprimirUltimasPalabras(editor & e){
// Imprime las últimas MAX_CANT_ULTIMAS_PALABRAS palabras ingresadas al texto.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}

TipoRetorno DestruirEditor(editor & e){
// Destruye la estructura editor y libera la memoria asociada.
	return NO_IMPLEMENTADA;
}



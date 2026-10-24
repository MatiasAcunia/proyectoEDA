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
	Diccionario dC;
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
	Linea ant;
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
	E->dC = crearDic();

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
	if(posicionLinea < 0 || posicionLinea > e->cant_Lineas){
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
	if(posicionLinea < 0 || posicionLinea >= e->cant_Lineas){
		return ERROR;
	}else{
	if(e->cant_Lineas == 0){
			// vacio
			return ERROR;

	}else if(posicionLinea == 0){
		// al inicio
		nodoE temp = e->cabeza;
		if (e->cant_Lineas > 1) {
			e->cabeza = e->cabeza->sig;
		}else {
			e->cabeza = NULL;
			e->cola = NULL;
		}	
		delete temp;

	}else if(e->cant_Lineas - 1 == posicionLinea){
		// al final
		nodoE temp = e->cola;

		if (e->cant_Lineas > 1) {
		nodoE it = e->cabeza;
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
		nodoE it = e->cabeza;
		for(int i = 0; i < posicionLinea - 1; i++){
			it = it->sig;
		}
		nodoE temp = it->sig;
		it->sig = temp->sig;
		delete temp;
	}
	
	e->cant_Lineas--;
	}
	return OK;
}

TipoRetorno BorrarTodo(editor & e){
// Borra todas las líneas del texto.
// Ver más detalles en la letra del obligatorio.

	auxBT (e->cabeza);
	e->cant_Lineas = 0;
	e->cabeza = NULL;
	e->cola = NULL;

	return OK;
}

void auxBT (nodoE iter) {
	if (iter != NULL) {

		auxBT(iter->sig);
		auxBPT(iter->inicio);
		delete iter;
	} 

}

void auxBPT (Linea iter){
	if (iter != NULL){

		auxBPT(iter->sig);
		delete[] iter->Cadena;
		delete iter;
	}
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra){
// Borra la palabra en la posición indicada.
// Ver más detalles en la letra del obligatorio.

	if(posicionLinea < 0 || posicionLinea >= e->cant_Lineas){
		return ERROR;
	}else{

    int i = 0;
	nodoE iter = e.cabeza;

	while (i != posicionLinea){

		iter = iter->sig;
		i++;

	}

	if(iter.n_palabras == 0) return ERROR;

	auxBP(iter.inicio);



	return OK;
	}
}

void auxBP(Linea iter, int posicionPalabra) {

	int i = 0;
	while (i != posicionPalabra){
		iter = iter->sig;
		i++;
	}

	if (iter->n_palabras > 1){

		if (iter->ant == NULL){
			nodoE->cabeza = iter->sig;
			nodoE->cabeza->ant = NULL;

		}else if (iter.sig == NULL){
			nodoE->cola = iter.ant;
			nodoE->cola->sig = NULL;

		}else {
		iter->sig->ant = iter->ant;
		iter->ant->sig = iter->sig;

		}
    }else {
		nodoE->inicio = NULL;
		nodoE->fin = NULL;
	}
	delete iter;
	nodoE->n_palabras--;
}


TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar){
// Borra todas las ocurrencias de una palabra en el texto.
// Ver más detalles en la letra del obligatorio.
	if(e != NULL){
		auxBOP(e->cabeza, palabraABorrar);
		return OK;
	}else{
		return ERROR;
	}
}

void auxBOP(nodoE iter, int palabraABorrar, int indiceHorizontal){
	if(iter){
		if(iter->inicio){
			int indiceVertical = 0;
			borrarEnLinea(inicio, palabraABorrar, indiceVertical);
			auxBOP(iter->sig, palabraABorrar);
		}
	}
}

void borrarEnLinea(Linea iter, int palabraABorrar, int indiceVertical){
	if(iter){
		if(iter->palabra == palabraABorrar){
			auxBP(iter, indiceVertical);
		}
		borrarEnLinea(inicio->sig, palabraABorrar, indiceVertical + 1);
	}
}

void borrarEnLinea(nodoE linea, Cadena palabraABorrar){
	// recorre verticalmente una linea y va borrando los nodos = palabraABorrar
	Linea iter = linea->inicio;
	while(iter){
		if(strcmp(iter->palabra, palabraABorrar) == 0){
			// borro
			if(linea->n_palabras == 1){
				// si hay una palabra				
				linea->inicio = NULL;
				linea->fin = NULL;
				linea->n_palabras--;
			}else if(linea->n_palabras > 1 && iter->ant == linea->inicio){
				// si hay mas de una palabra y la palabraAborrar es la del inicio
				linea->inicio = iter->sig;
				iter->sig->ant = iter->ant;
				linea->n_palabras--;
			}else if(linea->n_palabras > 1 && iter->ant == linea->fin){
				// si hay mas de una palabra y la palabraAborrar es la del fin
				linea->fin = iter->ant;
				iter->ant->sig = iter->sig;
				linea->n_palabras--;
			}else{
				// si hay mas de una palabra y es un nodo entre medio
				iter->ant->sig = iter->sig;
				iter->sig->ant = iter->ant;
				linea->n_palabras--;
			}
			// **si no hay palabras simplemente borra iter
			delete iter;
		}
			
	// avanzo
	iter = iter->sig;
	}
}		


TipoRetorno ImprimirTexto(editor & e){
// Imprime el texto por pantalla.
// Ver más detalles en la letra del obligatorio.
	if(e){
		auxIT(e, e->cabeza, 1);
		return OK;
	}else{
		return ERROR;
	}
}

// avanzo horizontalmente
void auxIT(editor &e, nodoE iter, int indice){
	printf("Salida:\n");

	if(e->cabeza != NULL){
		printf("%d: ", indice);
		imprimirLinea(iter->inicio);
		auxIT(e, iter->sig, indice + 1);
		printf("\n");
	}
}
// avanzo verticalmente
void imprimirLinea(Linea linea){
	if(linea != NULL){
		printf("%d", linea->palabra);
		printf(" ");
		imprimirLinea(linea->sig);
	}
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



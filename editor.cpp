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
struct nodo_editor {
	linea inicioMAX;
	texto cabeza, cola;
	int cant_Lineas;
	Diccionario dC;
};


editor crearEditor(){
	editor e = new(nodo_editor);

	e->cabeza = NULL;
	e->cola = NULL;
	e->cant_Lineas = 0;
	e->dC = crearDic();

	return e;
}

texto getCabeza(editor e){
	if(e != NULL) return e->cabeza;
	return NULL;
}
texto getCola(editor e){
	if(e != NULL) return e->cola;
	return NULL;
}
int getCantLineas(editor e){
	if(e != NULL) return e->cant_Lineas;
	return 0;
}
Diccionario getdC(editor e){
	if(e != NULL) return e->dC;
	return NULL;
}


void setCabeza(editor e, texto cabeza){
	if(e != NULL){
		e->cabeza = cabeza;
	}
}
void setCola(editor e, texto cola){
	if(e != NULL){
		e->cola = cola;
	}
}
void setCantLineas(editor e, int cant_Lineas){
	if(e != NULL) e->cant_Lineas = cant_Lineas;
}
void setdC(editor e, Diccionario dC){
	if(e != NULL) e->dC = dC;
}

void borrarEditor(editor e){
	if(e != NULL) delete e;
}


TipoRetorno InsertarLinea(editor & e){
// Inserta una nueva línea vacía al final del texto.
// Este requerimiento debe ser resuelto en O(1) peor caso.
// Ver más detalles en la letra del obligatorio.
	TADInsertarLinea(e);
}

TipoRetorno BorrarTodo(editor & e) {
    if (e == NULL) return ERROR;
    auxBT(getCabeza(e));
    setCantLineas(e, 0);
    setCabeza(e, NULL);
    setCola(e, NULL);

    return OK;
}

void auxBT(texto iter) {
    if (iter != NULL) {
        auxBT(Tail(iter));
        auxBPL(getInicio(iter));
        borrar(iter);
    }
}

void auxBPL(linea iter) {
    if (iter != NULL) {
        auxBPL(Tail(iter));
        borrarPalabra(iter);
        borrarLinea(iter);
    }
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





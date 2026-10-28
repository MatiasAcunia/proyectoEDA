// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// editor.c
// Modulo de implementacion de editor.

#include "linea.h"
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


//			**FUNCIONES DE LINEA**

// get set atributos, borrado, head, tail, snoc, cons, isEmpty, añadir y borrar palabra
linea crearLinea(){
	linea l = new(nodo_linea);
	l->sig = NULL;
	l->palabra = NULL;
	return l;
}


void reservarCadena(linea l, int length){
	if((l != NULL) && (length > 0)){
		l->palabra = new char[length];
	}
	
}
void copiarCadena(linea l, Cadena palabra){
	if((l != NULL) && (l->palabra != NULL) && (palabra != NULL)){
		strcpy(l->palabra, palabra);
	} 
	
}
char* getPalabra(linea l){
	if((l != NULL) && (l->palabra != NULL)){
		Cadena palabra = new char[strlen(l->palabra) + 1];
		strcpy(palabra, l->palabra);
		return palabra;
	}
	return NULL;
}
void borrarPalabra(linea l){
	if((l != NULL) && (l->palabra != NULL)){
		delete[] l->palabra;
		l->palabra = NULL;
	}
}
int lengthCadena(linea l){
	if((l != NULL) && (l->palabra != NULL)){
		return strlen(l->palabra);
	}
	return 0;
}
int compararCadena(Cadena palabra, Cadena palabra2){
	if((palabra != NULL) && (palabra2 != NULL)){
		return strcmp(palabra, palabra2);
	}
	return 0;
}

linea Tail(linea l){
	if(l != NULL) return l->sig;
	return NULL;
}

void SetTail(linea l, linea sig) {
    if (l != NULL) {
        l->sig = sig;
    }
}
linea Snoc(linea l){
	linea temp = crearLinea();
	temp->sig = l;
	return temp;
}
linea Cons(linea l){
	linea temp = crearLinea();
	if(l != NULL) l->sig = temp;
	return temp;
	
	
}
bool isEmpty(linea l){
	return (l == NULL);
}
void borrarLinea(linea l){
	if(l != NULL) delete l;
}


void auxBP(texto txt, Posicion posicionPalabra);
void auxBOP(texto iter, Cadena palabraABorrar);
void borrarEnLinea(texto txt, Cadena palabraABorrar);

TipoRetorno InsertarLineaEnPosicion(editor & e, Posicion posicionLinea) {
    if (e == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e) + 1) {
        return ERROR;
    }

    texto nuevo = crearTexto();

    if (getCantLineas(e) == 0) {
        setCabeza(e, nuevo);
        setCola(e, nuevo);
    } else if (posicionLinea == 1) {
        setTail(nuevo, getCabeza(e));
        setCabeza(e, nuevo);
    } else if (posicionLinea == getCantLineas(e) + 1) {
        setTail(getCola(e), nuevo);
        setCola(e, nuevo);
    } else {
        texto it = getCabeza(e);
        for (Posicion i = 1; i < posicionLinea - 1; i++) {
            it = Tail(it);
        }
        setTail(nuevo, Tail(it));
        setTail(it, nuevo);
    }

    setCantLineas(e, getCantLineas(e) + 1);
    return OK;
}

TipoRetorno BorrarLinea(editor & e, Posicion posicionLinea) {
    if (e == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    }

    texto temp;
    if (posicionLinea == 1) {
        temp = getCabeza(e);
        setCabeza(e, Tail(temp));
        if (getCantLineas(e) == 1) {
            setCola(e, NULL);
        }
    } else {
        texto it = getCabeza(e);
        for (Posicion i = 1; i < posicionLinea - 1; i++) {
            it = Tail(it);
        }
        temp = Tail(it);
        setTail(it, Tail(temp));
        if (posicionLinea == getCantLineas(e)) {
            setCola(e, it);
        }
    }

    auxBPL(getInicio(temp));
    borrar(temp);
    setCantLineas(e, getCantLineas(e) - 1);
    return OK;
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra) {
    if (e == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    }

    texto iter = getCabeza(e);
    for (Posicion i = 1; i < posicionLinea; i++) {
        iter = Tail(iter);
    }

    if (posicionPalabra == 0 || posicionPalabra > getNPalabras(iter)) {
        return ERROR;
    }

    auxBP(iter, posicionPalabra);
    return OK;
}

void auxBP(texto txt, Posicion posicionPalabra) {
    linea iter = getInicio(txt);
    linea prev = NULL;
    for (Posicion i = 1; i < posicionPalabra; i++) {
        prev = iter;
        iter = Tail(iter);
    }

    if (prev == NULL) {
        setInicio(txt, Tail(iter));
    } else {
        SetTail(prev, Tail(iter));
    }
    if (getFin(txt) == iter) {
        setFin(txt, prev);
    }

    setNPalabras(txt, getNPalabras(txt) - 1);
    borrarPalabra(iter);
    borrarLinea(iter);
}

TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar) {
    if (e == NULL || palabraABorrar == NULL) {
        return ERROR;
    }

    auxBOP(getCabeza(e), palabraABorrar);
    return OK;
}

void auxBOP(texto iter, Cadena palabraABorrar) {
    if (iter != NULL) {
        borrarEnLinea(iter, palabraABorrar);
        auxBOP(Tail(iter), palabraABorrar);
    }
}

void borrarEnLinea(texto txt, Cadena palabraABorrar) {
    linea iter = getInicio(txt);
    linea prev = NULL;

    while (iter) {
        linea siguiente = Tail(iter);

        Cadena palabra = getPalabra(iter);
        int res = compararCadena(palabra, palabraABorrar);
        delete[] palabra;

        if (res == 0) {
            if (getNPalabras(txt) == 1) {
                setInicio(txt, NULL);
                setFin(txt, NULL);
                setNPalabras(txt, getNPalabras(txt) - 1);

            } else if (getNPalabras(txt) > 1 && prev == NULL) {
                setInicio(txt, siguiente);
                setNPalabras(txt, getNPalabras(txt) - 1);

            } else if (getNPalabras(txt) > 1 && siguiente == NULL) {
                setFin(txt, prev);
                SetTail(prev, siguiente);
                setNPalabras(txt, getNPalabras(txt) - 1);

            } else {
                SetTail(prev, siguiente);
                setNPalabras(txt, getNPalabras(txt) - 1);
            }

            borrarPalabra(iter);
            borrarLinea(iter);

        } else {
            prev = iter;
        }

        iter = siguiente;
    }
}

TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar) {
    if (e == NULL || palabraAIngresar == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    }

    texto iter = getCabeza(e);
    for (Posicion i = 1; i < posicionLinea; i++) {
        iter = Tail(iter);
    }

    if (posicionPalabra == 0 || posicionPalabra > getNPalabras(iter) + 1 ||
        getNPalabras(iter) >= MAX_CANT_PALABRAS_X_LINEA) {
        return ERROR;
    }

    linea nuevo = crearLinea();
    reservarCadena(nuevo, strlen(palabraAIngresar) + 1);
    copiarCadena(nuevo, palabraAIngresar);

    if (getNPalabras(iter) == 0) {
        setInicio(iter, nuevo);
        setFin(iter, nuevo);
    } else if (posicionPalabra == 1) {
        SetTail(nuevo, getInicio(iter));
        setInicio(iter, nuevo);
    } else if (posicionPalabra == getNPalabras(iter) + 1) {
        SetTail(getFin(iter), nuevo);
        setFin(iter, nuevo);
    } else {
        linea prev = getInicio(iter);
        for (Posicion i = 1; i < posicionPalabra - 1; i++) {
            prev = Tail(prev);
        }
        SetTail(nuevo, Tail(prev));
        SetTail(prev, nuevo);
    }

    setNPalabras(iter, getNPalabras(iter) + 1);
    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(editor & e, Posicion posicionLinea, Cadena palabraABorrar) {
    if (e == NULL || palabraABorrar == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    }

    texto iter = getCabeza(e);
    for (Posicion i = 1; i < posicionLinea; i++) {
        iter = Tail(iter);
    }

    borrarEnLinea(iter, palabraABorrar);
    return OK;
}

TipoRetorno ImprimirLinea(editor & e, Posicion posicionLinea) {
    if (e == NULL || posicionLinea == 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    }

    texto iter = getCabeza(e);
    for (Posicion i = 1; i < posicionLinea; i++) {
        iter = Tail(iter);
    }

    printf("Salida:\n");
    printf("%u: ", posicionLinea);
    imprimirLinea(getInicio(iter));
    printf("\n");
    return OK;
}

void imprimirLinea(linea l) {
    if (l != NULL) {
        Cadena palabra = getPalabra(l);

        printf("%s", palabra);
        printf(" ");

        delete[] palabra;

        imprimirLinea(Tail(l));
    }
}

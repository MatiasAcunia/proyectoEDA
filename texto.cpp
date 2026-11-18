// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// editor.c
// Modulo de implementacion de editor.

#include "editor.h"
#include "linea.h"
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

int getNPalabras(texto t){
	if(t != NULL) return t->n_palabras;
	return 0;
}

bool isEmptyTexto(texto t){
    return (t == NULL);
}


texto TailTexto(texto t){
	if(t != NULL) return t->sig;
	return NULL;
}

linea getInicio(texto t){
	if(t != NULL) return t->inicio;
	return NULL;
}

linea getFin(texto t){
	if(t != NULL) return t->fin;
	return NULL;
}

void setNPalabras(texto t, int n_palabras){
	if(t != NULL) t->n_palabras = n_palabras;
}
void setTail(texto t, texto sig){
	if(t != NULL) t->sig = sig;
}

void setInicio(texto t, linea inicio){
	if(t != NULL) t->inicio = inicio;
}

void setFin(texto t, linea fin){
	if(t != NULL) t->fin = fin;
}

texto cons(texto t){
	texto temp = crearTexto();
	temp->sig = t;
	return temp;
}

texto snoc(texto t){

texto temp = crearTexto();
	if(t != NULL) t->sig = temp;
	return temp;
}

bool isEmpty(texto t){
	return (t == NULL);
}

void borrar(texto t){
	if(t != NULL) delete t;
}


void auxIT(editor & e, texto iter, int indice);

TipoRetorno ImprimirTexto(editor & e) {
    if (e == NULL) return ERROR;
    if (getCabeza(e) == NULL) {
        printf("Texto vacio\n");
        return OK;
    }
    auxIT(e, getCabeza(e), 1);
    return OK;
}

void auxIT(editor & e, texto iter, int indice) {
    while (iter != NULL) {
        printf("%d:", indice++);
        if (getInicio(iter) != NULL) printf(" ");
        imprimirLinea(getInicio(iter));
        printf("\n");
        iter = TailTexto(iter);
    }
}

TipoRetorno ComprimirTexto(editor & e) {
    if (e == NULL) return ERROR;

    texto iter = getCabeza(e);
    while (iter != NULL) {
        int eliminadas = appendPalabras(iter, TailTexto(iter), getFin(iter), getInicio(TailTexto(iter)), 0);
        setCantLineas(e, getCantLineas(e) - eliminadas);

        if (TailTexto(iter) == NULL) {
            setCola(e, iter);
            break;
        }
        iter = TailTexto(iter);
    }

    // La ultima linea tambien debe desaparecer si quedo vacia.
    while (getCantLineas(e) > 0 && getNPalabras(getCola(e)) == 0) {
        BorrarLinea(e, getCantLineas(e));
    }
    return OK;
}

int appendPalabras(texto actLinea, texto sigLinea, linea iterL1, linea iterL2, int lElim) {
    while (sigLinea != NULL) {
        if (getNPalabras(sigLinea) == 0) {
            setTail(actLinea, TailTexto(sigLinea));
            borrar(sigLinea);
            lElim++;
            sigLinea = TailTexto(actLinea);
            continue;
        }

        if (getNPalabras(actLinea) >= MAX_CANT_PALABRAS_X_LINEA) {
            break;
        }

        linea palabra = getInicio(sigLinea);
        setInicio(sigLinea, Tail(palabra));
        if (getInicio(sigLinea) == NULL) {
            setFin(sigLinea, NULL);
        }

        if (getFin(actLinea) == NULL) {
            setInicio(actLinea, palabra);
        } else {
            SetTail(getFin(actLinea), palabra);
        }
        SetTail(palabra, NULL);
        setFin(actLinea, palabra);

        setNPalabras(actLinea, getNPalabras(actLinea) + 1);
        setNPalabras(sigLinea, getNPalabras(sigLinea) - 1);
    }

    return lElim;
}



TipoRetorno ImprimirTextoIncorrecto(editor & e) {
    if (e == NULL) return ERROR;
    texto t = getCabeza(e);
    if (t == NULL) {
        printf("Texto vacio\n");
        return OK;
    }

    Diccionario dic = getDiccionario(e);
    nodoD raiz = dic == NULL ? NULL : getRaiz(dic);
    int numero = 1;
    while (t != NULL) {
        printf("%d:", numero++);
        linea l = getInicio(t);
        while (l != NULL) {
            // Se vuelve a consultar porque el diccionario puede haber cambiado.
            existeEnDic(l, raiz);
            if (!getExiste(l)) {
                Cadena palabra = getPalabra(l);
                if (palabra != NULL) {
                    printf(" %s", palabra);
                    delete[] palabra;
                }
            }
            l = Tail(l);
        }
        printf("\n");
        t = TailTexto(t);
    }
    return OK;
}

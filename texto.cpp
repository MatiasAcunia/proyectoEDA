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

int getNPalabras(texto t){
	if(t != NULL) return t->n_palabras;
	return 0;
}

texto Tail(texto t){
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
void SetTail(texto t, texto sig){
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
    if (e) {
        auxIT(e, getCabeza(e), 1);
        return OK;
    } else {
        return ERROR;
    }
}

void auxIT(editor & e, texto iter, int indice) {
    printf("Salida:\n");

    if (getCabeza(e) != NULL) {
        printf("%d: ", indice);
        imprimirLinea(getInicio(iter));
        auxIT(e, Tail(iter), indice + 1);
        printf("\n");
    }
}

TipoRetorno ComprimirTexto(editor & e) {
    int i = 0;
    texto iter = getCabeza(e);

    while (i < getCantLineas(e) && Tail(iter) != NULL) {
        setCantLineas(
            e,
            getCantLineas(e) - appendPalabras(
                iter,
                Tail(iter),
                getFin(iter),
                getInicio(Tail(iter)),
                0
            )
        );

        i++;
        iter = Tail(iter);
    }

    setCola(e, iter);

    return OK;
}

int appendPalabras(texto actLinea, texto sigLinea, linea iterL1, linea iterL2, int lElim) {
    if (getNPalabras(actLinea) < MAX_CANT_PALABRAS_X_LINEA && iterL1 != NULL && iterL2 != NULL) {
        SetTail(iterL1, iterL2);

        return appendPalabras(
            actLinea,
            sigLinea,
            iterL2,
            Tail(iterL2),
            lElim
        );

    } else if (getNPalabras(actLinea) < MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL) {
        setFin(actLinea, iterL1);
        setNPalabras(
            actLinea,
            getNPalabras(actLinea) + getNPalabras(sigLinea)
        );

        SetTail(actLinea, Tail(sigLinea));

        texto temp = sigLinea;
        borrar(temp);

        lElim++;
        sigLinea = Tail(actLinea);

        return appendPalabras(
            actLinea,
            Tail(sigLinea),
            iterL1,
            getInicio(sigLinea),
            lElim
        );

    } else if (getNPalabras(actLinea) == MAX_CANT_PALABRAS_X_LINEA && iterL2 != NULL) {
        setFin(actLinea, iterL1);

        int palAgg = MAX_CANT_PALABRAS_X_LINEA - getNPalabras(actLinea);

        setNPalabras(actLinea, MAX_CANT_PALABRAS_X_LINEA);
        SetTail(iterL1, NULL);

        setInicio(sigLinea, iterL2);
        setNPalabras(sigLinea, palAgg);

        return lElim;

    } else if (getNPalabras(actLinea) == MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL) {
        setFin(actLinea, iterL1);
        setNPalabras(actLinea, MAX_CANT_PALABRAS_X_LINEA);

        SetTail(actLinea, Tail(sigLinea));
        SetTail(iterL1, NULL);

        texto temp = sigLinea;
        borrar(temp);

        lElim++;

        return lElim;

    } else if (getNPalabras(actLinea) < MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL && getFin(Tail(sigLinea)) == NULL) {
        setFin(actLinea, iterL1);

        setNPalabras(
            actLinea,
            getNPalabras(actLinea) + getNPalabras(sigLinea)
        );

        SetTail(actLinea, NULL);
        SetTail(iterL1, NULL);

        texto temp = sigLinea;
        borrar(temp);

        lElim++;

        return lElim;
    }
}


TipoRetorno ImprimirTextoIncorrecto(editor & e){
// Muestra las palabras del texto que no se encuentran en el diccionario.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}
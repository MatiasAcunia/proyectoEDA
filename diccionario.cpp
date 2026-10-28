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
};


// get set atributos, borrado
Diccionario crearDic() {
	
	Diccionario D = new(diccionario);

	D->nPalabras = 0;
	D->raiz = NULL;

	return D;
}

nodoD getRaiz(Diccionario d){
    if((d != NULL) && (d->raiz != NULL)){
        return d->raiz; 
    } 
}
int getnPalabras(Diccionario d){
    if((d != NULL) && (d->nPalabras != NULL)){
        return d->nPalabras; 
    } 
}
void setnPalabras(Diccionario d, int n){
    if((d != NULL) && (d->nPalabras != NULL)){
        d->nPalabras = n;
    } 
}
void setRaiz(Diccionario d, nodoD raiz){
    if((d != NULL) && (d->raiz != NULL)){
        d->raiz = raiz;
    } 
}
void borrarDic(Diccionario d){
    if(d != NULL){
        delete d; 
    } 
}
bool isEmptyDic(Diccionario d){
    return (d);
}




// get set atributos (subiz y subde), isEmpty, dato, borrar, insertar 
nodoD crearDiccionario(){
	nodoD d = new(nodo_diccionario);
	d->de = NULL;
	d->iz = NULL;
	return d;
}

nodoD subiz(nodoD d){
    if(d != NULL) return d->iz;
}
nodoD subde(nodoD d){
    if(d != NULL) return d->de;
}
bool isEmptyNodoD(nodoD d){
    return (d);
}
void borrarNodoD(nodoD d){
    delete d;
}

void reservarCadena(nodoD d, int length){
	if((d != NULL) && (strlen(d->palabra) != 0)){
		d->palabra = new char[length];
	}
	
}
Cadena copiarCadena(nodoD d, Cadena palabra){
	if((d != NULL) && (d->palabra != NULL) && (palabra != NULL)){
		strcpy(d->palabra, palabra);
	} 
	
}
char* getPalabra(nodoD d){
	if((d != NULL) && (d->palabra != NULL)){
		Cadena palabra = new char[strlen(d->palabra) + 1];
		strcpy(palabra, d->palabra);
		return palabra;
	}
}
void borrarPalabra(nodoD d){
	if((d != NULL) && (d->palabra != NULL)){
		delete[] d->palabra;
	}
}
int lenghtCadena(nodoD d){
	if((d != NULL) && (d->palabra != NULL)){
		return strlen(d->palabra);
	}
}
int compararCadena(Cadena palabra, Cadena palabra2){
	if((palabra != NULL) && (palabra2 != NULL)){
		return strcmp(palabra, palabra2);
	}
}


TipoRetorno IngresarPalabraDiccionario(editor & e, Cadena palabraAIngresar) {
    // Agrega una palabra al diccionario.
    // Esta operación debe realizarse en a lo sumo O(log n) promedio.
    // Ver más detalles en la letra del obligatorio.

    if (e->dC == NULL) {
        Diccionario dic = crearDic();
        e->dC = dic;
    }

    e->dC->raiz = auxIPD(e->dC->raiz, e->dC, palabraAIngresar);
    e->dC->nPalabras++;

    return OK;
}

nodoD auxIPD(nodoD iter, Diccionario dic, Cadena palabraAIngresar) {
    if (dic->raiz != NULL) {
        int res = strcmp(palabraAIngresar, iter->palabra);

        if (res < 0) {
            iter->iz = auxIPD(iter->iz, dic, palabraAIngresar);
            return iter;

        } else if (res > 0) {
            iter->de = auxIPD(iter->de, dic, palabraAIngresar);
            return iter;

        } else if (res == 0) {
            return NULL;

        } else if (iter == NULL) {
            nodoD nuevo = crearDiccionario();
            nuevo->palabra = new char[strlen(palabraAIngresar) + 1];
            strcpy(nuevo->palabra, palabraAIngresar);
            nuevo->tope = strlen(palabraAIngresar) + 1;
            nuevo->iz = NULL;
            nuevo->de = NULL;
            return nuevo;
        }

    } else if (dic->raiz == NULL) {
        nodoD nuevo = crearDiccionario();
        nuevo->palabra = new char[strlen(palabraAIngresar) + 1];
        strcpy(nuevo->palabra, palabraAIngresar);
        nuevo->tope = strlen(palabraAIngresar) + 1;
        nuevo->iz = NULL;
        nuevo->de = NULL;
        return nuevo;
    }
}

TipoRetorno BorrarPalabraDiccionario(editor & e, Cadena palabraABorrar) {
    // Borra una palabra del diccionario.
    // Ver más detalles en la letra del obligatorio.

    if (e->dC == NULL || e->dC->raiz == NULL) {
        return ERROR;
    }

    e->dC->raiz = auxIPD(e->dC->raiz, palabraABorrar);
    e->dC->nPalabras--;

    return OK;
}

nodoD auxBPD(nodoD iter, Cadena palabraABorrar) {
    if (iter->raiz != NULL) {
        int res = strcmp(palabraABorrar, iter->palabra);

        if (res < 0) {
            iter->iz = auxIPD(iter->iz,  palabraABorrar);
            return iter;

        } else if (res > 0) {
            iter->de = auxIPD(iter->de, palabraABorrar);
            return iter;

        } else if (res == 0) {
            if (iter->iz != NULL && iter->de != NULL) {
                nodoD iter2 = iter->de;

                while (iter2->iz != NULL) {
                    iter2 = iter2->iz;
                }

                strcpy(iter->palabra, iter2->palabra);
                iter->de = auxBPD(iter->de, iter2->palabra);

                return iter;

            } else if (iter->iz != NULL && iter->de == NULL) {
                nodoD temp = iter;
                iter = iter->iz;
                delete[] temp->palabra;
                delete temp;
                return iter;

            } else if (iter->de != NULL && iter->iz == NULL) {
                nodoD temp = iter;
                iter = iter->de;
                delete[] temp->palabra;
                delete temp;
                return iter;

            } else {
                delete[] iter->palabra;
                delete iter;
                return NULL;
            }

        } else if (iter == NULL) {
            return NULL;
        }
    }
}


TipoRetorno ImprimirDiccionario(editor & e){
// Muestra las palabras del diccionario alfabéticamente.
// Esta operación debe realizarse en O(n) peor caso.
// Ver más detalles en la letra del obligatorio.
	return NO_IMPLEMENTADA;
}




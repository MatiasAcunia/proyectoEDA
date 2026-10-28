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
    if(d != NULL){
        return d->raiz;
    }
    return NULL; 
}
int getnPalabras(Diccionario d){
    if(d != NULL){
        return d->nPalabras;
    }
    return 0; 
}
void setnPalabras(Diccionario d, int n){
    if(d != NULL){
        d->nPalabras = n;
    } 
}
void setRaiz(Diccionario d, nodoD raiz){
    if(d != NULL){
        d->raiz = raiz;
    } 
}
void borrarDic(Diccionario d){
    if(d != NULL){
        delete d; 
    } 
}
bool isEmptyDic(Diccionario d){
    return (d == NULL);
}




// get set atributos (subiz y subde), isEmpty, dato, borrar, insertar 
nodoD crearDiccionario(){
	nodoD d = new(nodo_diccionario);
	d->de = NULL;
	d->iz = NULL;
	d->palabra = NULL;
	return d;
}

nodoD subiz(nodoD d){
    if(d != NULL) return d->iz;
    return NULL;
}
nodoD subde(nodoD d){
    if(d != NULL) return d->de;
    return NULL;
}
void setSubiz(nodoD d, nodoD iz) {
    if (d != NULL) {
        d->iz = iz;
    }
}

void setSubde(nodoD d, nodoD de) {
    if (d != NULL) {
        d->de = de;
    }
}

bool isEmptyNodoD(nodoD d){
    return (d == NULL);
}
void borrarNodoD(nodoD d){
    delete d;
}

void reservarCadena(nodoD d, int length){
	if((d != NULL) && (length > 0)){
		d->palabra = new char[length];
	}
	
}
void copiarCadena(nodoD d, Cadena palabra){
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
	return NULL;
}
void borrarPalabra(nodoD d){
	if((d != NULL) && (d->palabra != NULL)){
		delete[] d->palabra;
		d->palabra = NULL;
	}
}
int lengthCadena(nodoD d){
	if((d != NULL) && (d->palabra != NULL)){
		return strlen(d->palabra);
	}
	return 0;
}


nodoD auxIPD(nodoD iter, Diccionario dic, Cadena palabraAIngresar);
nodoD auxBPD(nodoD iter, Diccionario dic, Cadena palabraABorrar);

TipoRetorno IngresarPalabraDiccionario(editor & e, Cadena palabraAIngresar) {
    if (getdC(e) == NULL) {
        Diccionario dic = crearDic();
        setdC(e, dic);
    }

    Diccionario dic = getdC(e);

    setRaiz(
        dic,
        auxIPD(getRaiz(dic), dic, palabraAIngresar)
    );

    setnPalabras(dic, getnPalabras(dic) + 1);

    return OK;
}

nodoD auxIPD(nodoD iter, Diccionario dic, Cadena palabraAIngresar) {
    if (getRaiz(dic) != NULL) {
        Cadena palabra = getPalabra(iter);
        int res = compararCadena(palabraAIngresar, palabra);
        delete[] palabra;

        if (res < 0) {
            setSubiz(
                iter,
                auxIPD(subiz(iter), dic, palabraAIngresar)
            );

            return iter;

        } else if (res > 0) {
            setSubde(
                iter,
                auxIPD(subde(iter), dic, palabraAIngresar)
            );

            return iter;

        } else if (res == 0) {
            return NULL;

        } else if (iter == NULL) {
            nodoD nuevo = crearDiccionario();

            reservarCadena(nuevo, strlen(palabraAIngresar) + 1);
            copiarCadena(nuevo, palabraAIngresar);

            setSubiz(nuevo, NULL);
            setSubde(nuevo, NULL);

            return nuevo;
        }

    } else if (getRaiz(dic) == NULL) {
        nodoD nuevo = crearDiccionario();

        reservarCadena(nuevo, strlen(palabraAIngresar) + 1);
        copiarCadena(nuevo, palabraAIngresar);

        setSubiz(nuevo, NULL);
        setSubde(nuevo, NULL);

        return nuevo;
    }
}

TipoRetorno BorrarPalabraDiccionario(editor & e, Cadena palabraABorrar) {
    if (getdC(e) == NULL || getRaiz(getdC(e)) == NULL) {
        return ERROR;
    }

    Diccionario dic = getdC(e);

    setRaiz(
        dic,
        auxIPD(getRaiz(dic), dic, palabraABorrar)
    );

    setnPalabras(dic, getnPalabras(dic) - 1);

    return OK;
}

nodoD auxBPD(nodoD iter, Diccionario dic, Cadena palabraABorrar) {
    if (iter != NULL) {
        Cadena palabra = getPalabra(iter);
        int res = compararCadena(palabraABorrar, palabra);
        delete[] palabra;

        if (res < 0) {
            setSubiz(
                iter,
                auxIPD(subiz(iter), dic, palabraABorrar)
            );

            return iter;

        } else if (res > 0) {
            setSubde(
                iter,
                auxIPD(subde(iter), dic, palabraABorrar)
            );

            return iter;

        } else if (res == 0) {
            if (subiz(iter) != NULL && subde(iter) != NULL) {
                nodoD iter2 = subde(iter);

                while (subiz(iter2) != NULL) {
                    iter2 = subiz(iter2);
                }

                Cadena palabra2 = getPalabra(iter2);

                copiarCadena(iter, palabra2);

                setSubde(
                    iter,
                    auxBPD(subde(iter), dic, palabra2)
                );

                delete[] palabra2;

                return iter;

            } else if (subiz(iter) != NULL && subde(iter) == NULL) {
                nodoD temp = iter;
                iter = subiz(iter);

                borrarPalabra(temp);
                borrarNodoD(temp);

                return iter;

            } else if (subde(iter) != NULL && subiz(iter) == NULL) {
                nodoD temp = iter;
                iter = subde(iter);

                borrarPalabra(temp);
                borrarNodoD(temp);

                return iter;

            } else {
                borrarPalabra(iter);
                borrarNodoD(iter);

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




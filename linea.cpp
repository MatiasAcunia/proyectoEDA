// Estructuras de Datos y Algoritmos - Obligatorio 2026
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Modulo de implementacion de editor.

// Incluir los modulos realizados.
#include "editor.h"
#include "linea.h"
#include "definiciones.h"
#include <string.h>
#include <strings.h>
#include <iostream>
using namespace std;

//Estructura para el manejo de palabras; nodo de linea; lista simplemente enlazada
struct nodo_linea{
    Cadena palabra;
	linea sig;
    bool existe;
};


linea crearLinea(){
	linea l = new(nodo_linea);
	l->sig = NULL;
	l->palabra = NULL;
    l->existe = false;
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

bool getExiste(linea l){
    if(l != NULL){
        return l->existe;
    }
    return false;
}

void setExiste(linea l, bool res){
    if(l != NULL){
        l->existe = res;
    } 
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
		return strcasecmp(palabra, palabra2);
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

void auxBP(texto txt, Posicion posicionPalabra) {
    int iposicionPalabra = static_cast<int>(posicionPalabra);
    
    
    linea iter = getInicio(txt);
    linea prev = NULL;
    for (int i = 1; i < iposicionPalabra; i++) {
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

TipoRetorno BorrarLinea(editor & e, Posicion posicionLinea) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    
    if (e == NULL || posicionLinea == 0 || posicionLinea > static_cast<Posicion>(getCantLineas(e))) {
        return ERROR;
    }
    
    texto temp;
    if (iposicionLinea == 1) {
        temp = getCabeza(e);
        setCabeza(e, TailTexto(temp));
        if (getCantLineas(e) == 1) {
            setCola(e, NULL);
        }
    } else {
        texto it = getCabeza(e);
        for (int i = 1; i < iposicionLinea - 1; i++) {
            it = TailTexto(it);
        }
        temp = TailTexto(it);
        setTail(it, TailTexto(temp));
        if (iposicionLinea == getCantLineas(e)) {
            setCola(e, it);
        }
    }
    
    auxBPL(getInicio(temp));
    borrar(temp);
    setCantLineas(e, getCantLineas(e) - 1);
    return OK;
}

void borrarPalabra(texto txt, Cadena palabraABorrar) {
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

void auxBOP(texto iter, Cadena palabraABorrar) {
    if (iter != NULL) {
        borrarPalabra(iter, palabraABorrar);
        auxBOP(TailTexto(iter), palabraABorrar);
    }
}

TipoRetorno InsertarLineaEnPosicion(editor & e, Posicion posicionLinea) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    
    
    if (e == NULL || posicionLinea == 0 || posicionLinea > static_cast<Posicion>(getCantLineas(e)) + 1) {
        return ERROR;
    }
    
    texto nuevo = crearTexto();
    
    if (getCantLineas(e) == 0) {
        setCabeza(e, nuevo);
        setCola(e, nuevo);
    } else if (iposicionLinea == 1) {
        setTail(nuevo, getCabeza(e));
        setCabeza(e, nuevo);
    } else if (iposicionLinea == getCantLineas(e) + 1) {
        setTail(getCola(e), nuevo);
        setCola(e, nuevo);
    } else {
        texto it = getCabeza(e);
        for (int i = 1; i < iposicionLinea - 1; i++) {
            it = TailTexto(it);
        }
        setTail(nuevo, TailTexto(it));
        setTail(it, nuevo);
    }
    
    setCantLineas(e, getCantLineas(e) + 1);
    return OK;
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    int iposicionPalabra = static_cast<int>(posicionPalabra);
    
    if (e == NULL || posicionLinea == 0 || posicionLinea > static_cast<Posicion>(getCantLineas(e))) {
        return ERROR;
    }
    
    texto iter = getCabeza(e);
    for (int i = 1; i < iposicionLinea; i++) {
        iter = TailTexto(iter);
    }
    
    if (posicionPalabra == 0 || posicionPalabra > static_cast<Posicion>(getNPalabras(iter))) {
        return ERROR;
    }
    
    auxBP(iter, iposicionPalabra);
    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar) {
    if (e == NULL || palabraABorrar == NULL) {
        return ERROR;
    }
    
    auxBOP(getCabeza(e), palabraABorrar);
    return OK;
}




TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    int iposicionPalabra = static_cast<int>(posicionPalabra);

    if (e == NULL || palabraAIngresar == NULL || posicionLinea == 0 ||
        posicionLinea > static_cast<Posicion>(getCantLineas(e))) return ERROR;

    texto iter = getCabeza(e);
    for (int i = 1; i < iposicionLinea; i++) iter = TailTexto(iter);

    if (posicionPalabra == 0 || posicionPalabra > static_cast<Posicion>(getNPalabras(iter)) + 1) return ERROR;

    linea nuevo = crearLinea();
    reservarCadena(nuevo, strlen(palabraAIngresar) + 1);
    copiarCadena(nuevo, palabraAIngresar);
    existeEnDic(nuevo, getRaiz(getDiccionario(e)));

    if (getNPalabras(iter) == 0) {
        setInicio(iter, nuevo);
        setFin(iter, nuevo);
    } else if (iposicionPalabra == 1) {
        SetTail(nuevo, getInicio(iter));
        setInicio(iter, nuevo);
    } else if (iposicionPalabra == getNPalabras(iter) + 1) {
        SetTail(getFin(iter), nuevo);
        setFin(iter, nuevo);
    } else {
        linea prev = getInicio(iter);
        for (int i = 1; i < iposicionPalabra - 1; i++) prev = Tail(prev);
        SetTail(nuevo, Tail(prev));
        SetTail(prev, nuevo);
    }
    setNPalabras(iter, getNPalabras(iter) + 1);

    // Una linea llena desplaza su ultima palabra al principio de la siguiente.
    texto actual = iter;
    while (getNPalabras(actual) > MAX_CANT_PALABRAS_X_LINEA) {
        linea ultima = getFin(actual);
        linea anterior = getInicio(actual);
        while (Tail(anterior) != ultima) anterior = Tail(anterior);

        SetTail(anterior, NULL);
        setFin(actual, anterior);
        setNPalabras(actual, getNPalabras(actual) - 1);

        texto siguiente = TailTexto(actual);
        if (siguiente == NULL) {
            InsertarLinea(e);
            siguiente = TailTexto(actual);
        }

        SetTail(ultima, getInicio(siguiente));
        setInicio(siguiente, ultima);
        if (getFin(siguiente) == NULL) setFin(siguiente, ultima);
        setNPalabras(siguiente, getNPalabras(siguiente) + 1);
        actual = siguiente;
    }

    actualizarUltimasPalabras(e, nuevo);
    return OK;
}


TipoRetorno BorrarOcurrenciasPalabraEnLinea(editor & e, Posicion posicionLinea, Cadena palabraABorrar) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    
    if (e == NULL || palabraABorrar == NULL || posicionLinea == 0 || posicionLinea > static_cast<Posicion>(getCantLineas(e))) {
        return ERROR;
    }
    
    texto iter = getCabeza(e);
    for (int i = 1; i < iposicionLinea; i++) {
        iter = TailTexto(iter);
    }
    
    borrarPalabra(iter, palabraABorrar);
    return OK;
}

TipoRetorno ImprimirLinea(editor & e, Posicion posicionLinea) {
    int iposicionLinea = static_cast<int>(posicionLinea);

    if (e == NULL || posicionLinea == 0 || posicionLinea > static_cast<Posicion>(getCantLineas(e))) {
        return ERROR;
    }

    texto iter = getCabeza(e);
    for (int i = 1; i < iposicionLinea; i++) {
        iter = TailTexto(iter);
    }

    printf("%u:", posicionLinea);
    if (getInicio(iter) != NULL) printf(" ");
    imprimirLinea(getInicio(iter));
    printf("\n");
    return OK;
}

void imprimirLinea(linea l) {
    while (l != NULL) {
        Cadena palabra = getPalabra(l);
        if (palabra != NULL) {
            printf("%s", palabra);
            delete[] palabra;
        }
        l = Tail(l);
        if (l != NULL) printf(" ");
    }
}

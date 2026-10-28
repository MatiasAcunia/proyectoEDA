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


//			**FUNCIONES DE LINEA**

// get set atributos, borrado, head, tail, snoc, cons, isEmpty, añadir y borrar palabra
linea crearLinea(){
	linea l = new(nodo_linea);
	l->sig = NULL;
	return l;
}


void reservarCadena(linea l, int length){
	if((l != NULL) && (strlen(l->palabra) != 0)){
		l->palabra = new char[length];
	}
	
}
Cadena copiarCadena(linea l, Cadena palabra){
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
}
void borrarPalabra(linea l){
	if((l != NULL) && (l->palabra != NULL)){
		delete[] l->palabra;
	}
}
int lenghtCadena(linea l){
	if((l != NULL) && (l->palabra != NULL)){
		return strlen(l->palabra);
	}
}
int compararCadena(Cadena palabra, Cadena palabra2){
	if((palabra != NULL) && (palabra2 != NULL)){
		return strcmp(palabra, palabra2);
	}
}

linea Tail(linea l){
	return l->sig;
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
	return (l);
}
void borrarLinea(linea l){
	if(l != NULL) delete l;
}


TipoRetorno TADInsertarLinea(editor & e){
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

void auxBP(texto txt, Posicion posicionPalabra);
void auxBOP(texto iter, Cadena palabraABorrar);
void borrarEnLinea(texto txt, Cadena palabraABorrar);

TipoRetorno InsertarLineaEnPosicion(editor & e, Posicion posicionLinea) {
    if (posicionLinea < 0 || posicionLinea > getCantLineas(e)) {
        return ERROR;
    } else {
        texto nuevo = crearTexto();

        if (getCantLineas(e) == 0) {
            setCabeza(e, nuevo);
            setCola(e, nuevo);

        } else if (posicionLinea == 0) {
            SetTail(nuevo, getCabeza(e));
            setCabeza(e, nuevo);

        } else if (getCantLineas(e) == posicionLinea) {
            SetTail(getCola(e), nuevo);
            setCola(e, nuevo);

        } else {
            texto it = getCabeza(e);

            for (int i = 0; i < posicionLinea - 1; i++) {
                it = Tail(it);
            }

            SetTail(nuevo, Tail(it));
            SetTail(it, nuevo);
        }

        setCantLineas(e, getCantLineas(e) + 1);
    }

    return OK;
}

TipoRetorno BorrarLinea(editor & e, Posicion posicionLinea) {
    if (posicionLinea < 0 || posicionLinea >= getCantLineas(e)) {
        return ERROR;
    } else {
        if (getCantLineas(e) == 0) {
            return ERROR;

        } else if (posicionLinea == 0) {
            texto temp = getCabeza(e);

            if (getCantLineas(e) > 1) {
                setCabeza(e, Tail(getCabeza(e)));
            } else {
                setCabeza(e, NULL);
                setCola(e, NULL);
            }

            borrar(temp);

        } else if (getCantLineas(e) - 1 == posicionLinea) {
            texto temp = getCola(e);

            if (getCantLineas(e) > 1) {
                texto it = getCabeza(e);

                for (int i = 0; i < posicionLinea - 1; i++) {
                    it = Tail(it);
                }

                setCola(e, it);
                SetTail(getCola(e), NULL);

            } else {
                setCabeza(e, NULL);
                setCola(e, NULL);
            }

            borrar(temp);

        } else {
            texto it = getCabeza(e);

            for (int i = 0; i < posicionLinea - 1; i++) {
                it = Tail(it);
            }

            texto temp = Tail(it);
            SetTail(it, Tail(temp));
            borrar(temp);
        }

        setCantLineas(e, getCantLineas(e) - 1);
    }

    return OK;
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra) {
    if (posicionLinea < 0 || posicionLinea >= getCantLineas(e)) {
        return ERROR;
    } else {
        int i = 0;
        texto iter = getCabeza(e);

        while (i != posicionLinea) {
            iter = Tail(iter);
            i++;
        }

        if (getNPalabras(iter) == 0) {
            return ERROR;
        }

        auxBP(iter, posicionPalabra);

        return OK;
    }
}

void auxBP(texto txt, Posicion posicionPalabra) {
    int i = 0;
    linea iter = getInicio(txt);
    linea prev = NULL;

    while (i != posicionPalabra) {
        prev = iter;
        iter = Tail(iter);
        i++;
    }

    if (getNPalabras(txt) == 1) {
        setInicio(txt, NULL);
        setFin(txt, NULL);
        setNPalabras(txt, getNPalabras(txt) - 1);

    } else if (getNPalabras(txt) > 1 && prev == NULL) {
        setInicio(txt, Tail(iter));
        setNPalabras(txt, getNPalabras(txt) - 1);

    } else if (getNPalabras(txt) > 1 && Tail(iter) == NULL) {
        setFin(txt, prev);
        SetTail(prev, Tail(iter));
        setNPalabras(txt, getNPalabras(txt) - 1);

    } else {
        SetTail(prev, Tail(iter));
        setNPalabras(txt, getNPalabras(txt) - 1);
    }

    borrarLinea(iter);
}

TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar) {
    editor a = e;

    if (a != NULL) {
        auxBOP(getCabeza(e), palabraABorrar);
        return OK;
    } else {
        return ERROR;
    }
}

void auxBOP(texto iter, Cadena palabraABorrar) {
    if (iter) {
        if (getInicio(iter)) {
            borrarEnLinea(iter, palabraABorrar);
            auxBOP(Tail(iter), palabraABorrar);
        }
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

            borrarLinea(iter);

        } else {
            prev = iter;
        }

        iter = siguiente;
    }
}

TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar) {
    int iposicionLinea = static_cast<int>(posicionLinea);
    int iposicionPalabra = static_cast<int>(posicionPalabra);

    if (iposicionLinea < 0 || iposicionLinea >= getCantLineas(e)) {
        return ERROR;
    }

    int i = 0;
    texto iter = getCabeza(e);

    while (i < iposicionLinea) {
        i++;
        iter = Tail(iter);
    }

    if (iposicionPalabra < 0 || iposicionPalabra > getNPalabras(iter)) {
        return ERROR;
    }

    i = 0;
    linea iterP = getInicio(iter);
    linea prev = NULL;

    while (i < iposicionPalabra) {
        i++;
        prev = iterP;
        iterP = Tail(iterP);
    }

    linea nuevo = crearLinea();
    reservarCadena(nuevo, strlen(palabraAIngresar) + 1);
    copiarCadena(nuevo, palabraAIngresar);

    if (iposicionPalabra == getNPalabras(iter)) {
        SetTail(getFin(iter), nuevo);
        SetTail(nuevo, NULL);
        setFin(iter, nuevo);

    } else if (iposicionPalabra == 0) {
        SetTail(nuevo, getInicio(iter));
        setInicio(iter, nuevo);

    } else {
        SetTail(nuevo, getInicio(iter));
        SetTail(prev, nuevo);
    }

    setNPalabras(iter, getNPalabras(iter) + 1);

    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(editor & e, Posicion posicionLinea, Cadena palabraABorrar) {
    int iposicionLinea = static_cast<int>(posicionLinea);

    if (iposicionLinea < 0 || iposicionLinea >= getCantLineas(e)) {
        return ERROR;
    }

    int i = 0;
    texto iter = getCabeza(e);

    while (i < iposicionLinea) {
        i++;
        iter = Tail(iter);
    }

    linea iterP = getInicio(iter);
    linea prev = NULL;
    i = 0;

    while (iterP != NULL) {
        Cadena palabra = getPalabra(iterP);
        int res = compararCadena(palabra, palabraABorrar);
        delete[] palabra;

        if (res == 0) {
            if (i == getNPalabras(iter)) {
                SetTail(prev, NULL);

                linea temp = iterP;
                iterP = Tail(iterP);
                borrarLinea(temp);

                setFin(iter, prev);

            } else if (i == 0) {
                setInicio(iter, Tail(iterP));

                linea temp = iterP;
                iterP = Tail(iterP);
                borrarLinea(temp);

            } else {
                SetTail(prev, Tail(iterP));

                linea temp = iterP;
                iterP = Tail(iterP);
                borrarLinea(temp);
            }

        } else {
            prev = iterP;
            iterP = Tail(iterP);
        }

        i++;
    }

    return OK;
}

TipoRetorno ImprimirLinea(editor & e, Posicion posicionLinea) {
    int iposicionLinea = static_cast<int>(posicionLinea);

    if (iposicionLinea < 0 || iposicionLinea >= getCantLineas(e)) {
        return ERROR;
    }

    int i = 0;
    texto iter = getCabeza(e);

    while (i < iposicionLinea) {
        i++;
        iter = Tail(iter);
    }

    linea iterP = getInicio(iter);

    printf("Salida:\n");
    printf("%d: ", i + 1);
    imprimirLinea(iterP);

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

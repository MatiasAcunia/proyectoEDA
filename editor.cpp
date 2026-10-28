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


// get set atributos y borrado
editor crearEditor(){
	
	editor e = new(nodo_editor);
	
	e->cabeza = NULL;
	e->cola = NULL;
	e->cant_Lineas = 0;
	e->dC = crearDic();
	
	return e;
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

void auxBT (texto iter) {
	if (iter != NULL) {

		auxBT(iter->sig);
		auxBPL(iter->inicio);
		delete iter;
	} 

}

void auxBPL (linea iter){
	if (iter != NULL){

		auxBPL(iter->sig);
		delete[] iter->palabra;
		delete iter;
	}
}

TipoRetorno BorrarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra){
// Borra la palabra en la posición indicada.
// Ver más detalles en la letra del obligatorio.

// recorre horizontalmente hasta llegar a una linea en concreta

	if(posicionLinea < 0 || posicionLinea >= e->cant_Lineas){
		return ERROR;
	}else{

    int i = 0;
	texto iter = e->cabeza;

	while (i != posicionLinea){

		iter = iter->sig;
		i++;

	}

	if(iter->n_palabras == 0) return ERROR;

	auxBP(iter, posicionPalabra);



	return OK;
	}
}

void auxBP(texto txt, Posicion posicionPalabra) {
// borra un nodo en una posición de la linea en concreto
	int i = 0;
	linea iter = txt->inicio;
	while (i != posicionPalabra){
		iter = iter->sig;
		i++;
	}

	// borro
	if(txt->n_palabras == 1){
		// si hay una palabra				
		txt->inicio = NULL;
		txt->fin = NULL;
		txt->n_palabras--;
	}else if(txt->n_palabras > 1 && iter->ant == txt->inicio){
		// si hay mas de una palabra y la palabraAborrar es la del inicio
		txt->inicio = iter->sig;
		iter->sig->ant = iter->ant;
		txt->n_palabras--;
	}else if(txt->n_palabras > 1 && iter->ant == txt->fin){
		// si hay mas de una palabra y la palabraAborrar es la del fin
		txt->fin = iter->ant;
		iter->ant->sig = iter->sig;
		txt->n_palabras--;
	}else{
		// si hay mas de una palabra y es un nodo entre medio
		iter->ant->sig = iter->sig;
		iter->sig->ant = iter->ant;
		txt->n_palabras--;
	}
	// **si no hay palabras simplemente borra iter
	delete iter;
}


TipoRetorno BorrarOcurrenciasPalabraEnTexto(editor & e, Cadena palabraABorrar){
// Borra todas las ocurrencias de una palabra en el texto.
// Ver más detalles en la letra del obligatorio.
	editor a = e;
	
	if(a != NULL){
		auxBOP(e->cabeza, palabraABorrar);
		return OK;
	}else{
		return ERROR;
	}
}

void auxBOP(texto iter, Cadena palabraABorrar){
	// recorre horizontalmente todas las lineas
	if(iter){
		if(iter->inicio){
			borrarEnLinea(iter, palabraABorrar);
			auxBOP(iter->sig, palabraABorrar);
		}
	}
}

void borrarEnLinea(texto linea, Cadena palabraABorrar){
	// recorre verticalmente una linea y va borrando los nodos = palabraABorrar
	linea iter = linea->inicio;
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
void auxIT(editor &e, texto iter, int indice){
	printf("Salida:\n");

	if(e->cabeza != NULL){
		printf("%d: ", indice);
		imprimirLinea(iter->inicio);
		auxIT(e, iter->sig, indice + 1);
		printf("\n");
	}
}
// avanzo verticalmente
void imprimirLinea(linea linea){
	if(linea != NULL){
		printf("%s", linea->palabra);
		printf(" ");
		imprimirLinea(linea->sig);
	}
}


TipoRetorno ComprimirTexto(editor & e) {
    // Comprime las palabras del texto. Para implementar esta operación no debe generarse un nuevo documento.
    // Ver más detalles en la letra del obligatorio.

    int i = 0;
    texto iter = e->cabeza;

    while (i < e->cant_Lineas && iter->sig != NULL) {
        e->cant_Lineas = e->cant_Lineas - appendPalabras(iter, iter->sig, iter->fin, iter->sig->inicio, 0);
        i++;
        iter = iter->sig;
    }

    e->cola = iter;
    return OK;
}

int appendPalabras(texto actLinea, texto sigLinea, linea iterL1, linea iterL2, int lElim) {
    if (actLinea->n_palabras < MAX_CANT_PALABRAS_X_LINEA && iterL1 != NULL && iterL2 != NULL) {
        iterL1->sig = iterL2;
        return appendPalabras(actLinea, sigLinea, iterL2, iterL2->sig, lElim);

    } else if (actLinea->n_palabras < MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL) {
        actLinea->fin = iterL1;
        actLinea->n_palabras = actLinea->n_palabras + sigLinea->n_palabras;
        actLinea->sig = sigLinea->sig;

        texto temp = sigLinea;
        delete temp;

        lElim++;
        sigLinea = actLinea->sig;

        return appendPalabras(actLinea, sigLinea->sig, iterL1, sigLinea->inicio, lElim);

    } else if (actLinea->n_palabras == MAX_CANT_PALABRAS_X_LINEA && iterL2 != NULL) {
        actLinea->fin = iterL1;
        int palAgg = MAX_CANT_PALABRAS_X_LINEA - actLinea->n_palabras;
        actLinea->n_palabras = MAX_CANT_PALABRAS_X_LINEA;
        iterL1->sig = NULL;

        sigLinea->inicio = iterL2;
        sigLinea->n_palabras = palAgg;
        return lElim;

    } else if (actLinea->n_palabras == MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL) {
        actLinea->fin = iterL1;
        actLinea->n_palabras = MAX_CANT_PALABRAS_X_LINEA;
        actLinea->sig = sigLinea->sig;
        iterL1->sig = NULL;

        texto temp = sigLinea;
        delete temp;

        lElim++;
        return lElim;

    } else if (actLinea->n_palabras < MAX_CANT_PALABRAS_X_LINEA && iterL2 == NULL && sigLinea->sig->fin == NULL) {
        actLinea->fin = iterL1;
        actLinea->n_palabras = actLinea->n_palabras + sigLinea->n_palabras;
        actLinea->sig = NULL;
        iterL1->sig = NULL;

        texto temp = sigLinea;
        delete temp;

        lElim++;
        return lElim;
    }
}

TipoRetorno InsertarPalabra(editor & e, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar) {
    // Inserta una palabra en una línea.
    // Ver más detalles en la letra del obligatorio.

    int iposicionLinea = static_cast<int>(posicionLinea);
    int iposicionPalabra = static_cast<int>(posicionPalabra);

    if (iposicionLinea < 0 || iposicionLinea >= e->cant_Lineas) {
        return ERROR;
    }

    int i = 0;
    texto iter = e->cabeza;

    while (i < iposicionLinea) {
        i++;
        iter = iter->sig;
    }

    if (iposicionPalabra < 0 || iposicionPalabra > iter->n_palabras) {
        return ERROR;
    }

    i = 0;
    linea iterP = iter->inicio;
    linea prev = NULL;

    while (i < iposicionPalabra) {
        i++;
        prev = iterP;
        iterP = iterP->sig;
    }

    linea nuevo = crearLinea();
    nuevo->palabra = new char[strlen(palabraAIngresar) + 1];
    strcpy(nuevo->palabra, palabraAIngresar);
    nuevo->tope = strlen(palabraAIngresar) + 1;

    if (iposicionPalabra == iter->n_palabras) {
        iter->fin->sig = nuevo;
        nuevo->sig = NULL;
        nuevo->ant = iter->fin;
        iter->fin = nuevo;

    } else if (iposicionPalabra == 0) {
        nuevo->ant = NULL;
        nuevo->sig = iter->inicio;
        iter->inicio->ant = nuevo;
        iter->inicio = nuevo;

    } else {
        nuevo->sig = iter->inicio;
        nuevo->ant = prev;
        prev->sig = nuevo;
        iterP->ant = nuevo;
    }

    iter->n_palabras++;

    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(editor & e, Posicion posicionLinea, Cadena palabraABorrar) {
    // Borra todas las ocurrencias de una palabra en la línea indicada.
    // Ver más detalles en la letra del obligatorio.

    int iposicionLinea = static_cast<int>(posicionLinea);
    

    if (iposicionLinea < 0 || iposicionLinea >= e->cant_Lineas) {
        return ERROR;
    }

    int i = 0;
    texto iter = e->cabeza;

    while (i < iposicionLinea) {
        i++;
        iter = iter->sig;
    }

   

    linea iterP = iter->inicio;
    linea prev = NULL;
    i = 0;

    while (iterP != NULL) {
        if (strcmp(iterP->palabra, palabraABorrar) == 0) {
            if (i == iter->n_palabras) {
                prev->sig = NULL;
                linea temp = iterP;
                iterP = iterP->sig;
                delete temp;
                iter->fin = prev;

            } else if (i == 0) {
                iterP->sig->ant = NULL;
                iter->inicio = iterP->sig;
                linea temp = iterP;
                iterP = iterP->sig;
                delete temp;

            } else {
                prev->sig = iterP->sig;
                iterP->sig->ant = prev;
                linea temp = iterP;
                iterP = iterP->sig;
                delete temp;
            }

        } else {
            iterP = iterP->sig;
        }

        i++;
    }

    return OK;
}

TipoRetorno ImprimirLinea(editor & e, Posicion posicionLinea) {
    // Imprime la línea por pantalla.
    // Ver más detalles en la letra del obligatorio.

    int iposicionLinea = static_cast<int>(posicionLinea);

    if (iposicionLinea < 0 || iposicionLinea >= e->cant_Lineas) {
        return ERROR;
    }

    int i = 0;
    texto iter = e->cabeza;

    while (i < iposicionLinea) {
        i++;
        iter = iter->sig;
    }


    linea iterP = iter->inicio;

    printf("Salida:\n");
    printf("%d: ", i + 1);
    imprimirLinea(iterP);

    return OK;
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



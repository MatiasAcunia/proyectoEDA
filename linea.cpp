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

TipoRetorno InsertarLineaEnPosicion(editor & e, Posicion posicionLinea){
// Inserta una nueva línea vacía en la posición indicada.
// Ver más detalles en la letra del obligatorio.
	if(posicionLinea < 0 || posicionLinea > e->cant_Lineas){
		return ERROR;
	}else{
		texto nuevo = crearNodoEditor();

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
			texto it = e->cabeza;
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
		texto temp = e->cabeza;
		if (e->cant_Lineas > 1) {
			e->cabeza = e->cabeza->sig;
		}else {
			e->cabeza = NULL;
			e->cola = NULL;
		}	
		delete temp;

	}else if(e->cant_Lineas - 1 == posicionLinea){
		// al final
		texto temp = e->cola;

		if (e->cant_Lineas > 1) {
		texto it = e->cabeza;
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
		texto it = e->cabeza;
		for(int i = 0; i < posicionLinea - 1; i++){
			it = it->sig;
		}
		texto temp = it->sig;
		it->sig = temp->sig;
		delete temp;
	}
	
	e->cant_Lineas--;
	}
	return OK;
}



//			**FUNCIONES DE PALABRA**

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

// avanzo verticalmente
void imprimirLinea(linea linea){
	if(linea != NULL){
		printf("%s", linea->palabra);
		printf(" ");
		imprimirLinea(linea->sig);
	}
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





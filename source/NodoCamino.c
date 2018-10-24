#include "NodoCamino.h"

#include <string.h>

void nodoCaminoContruir(NodoCamino_T * nodo, char * nombre) {
	strncpy(nodo->nombre, nombre, LONG_MAX_NODO);
	nodo->siguiente = NULL;
}

void nodoCaminoDestruir(NodoCamino_T * nodo) {
}

char * nodoCaminoGetNombre(NodoCamino_T * nodo) {
	return nodo->nombre;
}

NodoCamino_T * nodoCaminoGetSiguiente(NodoCamino_T * nodo) {
	return nodo->siguiente;
}

void nodoCaminoSetSiguiente(NodoCamino_T * nodo, NodoCamino_T * siguiente) {
	nodo->siguiente = siguiente;
}

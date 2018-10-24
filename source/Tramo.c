#include "Tramo.h"

#include <string.h>

void tramoConstruir(Tramo_T * tramo, char * inicio, char * fin, int distancia) {
	strncpy(tramo->inicio, inicio, LONG_MAX_TRAMO);
	strncpy(tramo->fin, fin, LONG_MAX_TRAMO);
	tramo->distancia = distancia;
	tramo->siguiente = NULL;
}

void tramoDestruir(Tramo_T * tramo) {
}

void tramoSetSiguiente(Tramo_T * tramo, Tramo_T * siguiente) {
	tramo->siguiente = siguiente;
}

Tramo_T * tramoGetSiguiente(Tramo_T * tramo) {
	return tramo->siguiente;
}

char * tramoGetInicio(Tramo_T * tramo) {
	return tramo->inicio;
}

char * tramoGetFin(Tramo_T * tramo) {
	return tramo->fin;
}

int tramoGetDistancia(Tramo_T * tramo) {
	return tramo->distancia;
}

char tramoSonIguales(Tramo_T * tramo, char * inicio, char * fin) {
	if (!(strncmp(tramo->inicio, inicio, LONG_MAX_TRAMO))
			&& !(strncmp(tramo->fin, fin, LONG_MAX_TRAMO)))
		return IGUALES;
	else
		return DISTINTOS;
}

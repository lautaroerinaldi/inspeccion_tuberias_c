#include "MapaTuberias.h"

#include <stdio.h>
#include <stdlib.h>

void mapaTuberiasConstruir(MapaTuberias_T * mapa) {
	mapa->primero = NULL;
	mapa->ultimo = NULL;
}

void mapaTuberiasDestruir(MapaTuberias_T * mapa) {
	if (mapa->primero) {
		Tramo_T * tramo_a_borrar = mapa->primero;
		Tramo_T * tramo_siguiente = tramoGetSiguiente(tramo_a_borrar);

		while (tramo_a_borrar) {
			tramoDestruir(tramo_a_borrar);
			free(tramo_a_borrar);
			tramo_a_borrar = tramo_siguiente;
			if (tramo_a_borrar)
				tramo_siguiente = tramoGetSiguiente(tramo_a_borrar);
		}
	}
}

void mapaTuberiasAgregarTramo(MapaTuberias_T * mapa, char * inicio, char * fin,
		int distancia) {
	Tramo_T * tramo_aux = malloc(sizeof(Tramo_T));
	tramoConstruir(tramo_aux, inicio, fin, distancia);
	if (mapa->primero == NULL)
		mapa->primero = tramo_aux;
	else
		tramoSetSiguiente(mapa->ultimo, tramo_aux);

	mapa->ultimo = tramo_aux;
}

int mapaTuberiasGetDistancia(MapaTuberias_T * mapa, char * inicio, char * fin) {
	Tramo_T * tramo_aux = mapa->primero;
	while (!tramoSonIguales(tramo_aux, inicio, fin))
		tramo_aux = tramoGetSiguiente(tramo_aux);

	return tramoGetDistancia(tramo_aux);
}

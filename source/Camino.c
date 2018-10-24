#include "Camino.h"

#include <stdio.h>
#include <stdlib.h>

void caminoContruir(Camino_T * camino) {
	camino->distancia_total = 0;
	camino->tamanio = 0;
	camino->primero = NULL;
	camino->ultimo = NULL;
}

void caminoDestruir(Camino_T * camino) {
	if (camino->primero) {
		NodoCamino_T * nodo_a_borrar = camino->primero;
		NodoCamino_T * nodo_siguiente = nodoCaminoGetSiguiente(nodo_a_borrar);

		while (nodo_a_borrar) {
			nodoCaminoDestruir(nodo_a_borrar);
			free(nodo_a_borrar);
			nodo_a_borrar = nodo_siguiente;
			if (nodo_a_borrar)
				nodo_siguiente = nodoCaminoGetSiguiente(nodo_a_borrar);
		}
	}
}

void caminoAgregarNodo(Camino_T * camino, char * nombre_nodo,
		MapaTuberias_T * mapa) {
	NodoCamino_T * nodo_aux = malloc(sizeof(NodoCamino_T));
	nodoCaminoContruir(nodo_aux, nombre_nodo);

	if (camino->primero == NULL) {
		camino->primero = nodo_aux;
	} else {
		nodoCaminoSetSiguiente(camino->ultimo, nodo_aux);
		camino->distancia_total += mapaTuberiasGetDistancia(mapa,
				nodoCaminoGetNombre(camino->ultimo),
				nodoCaminoGetNombre(nodo_aux));
	}
	camino->ultimo = nodo_aux;
	++camino->tamanio;
}

int caminoGetDistanciaTotal(Camino_T * camino) {
	return camino->distancia_total;
}

Falla_T * caminoGetTramoFalla(Camino_T * camino, MapaTuberias_T * mapa,
		float distancia_a_origen) {
	return caminoLocalizarFalla(camino->primero,
			nodoCaminoGetSiguiente(camino->primero), distancia_a_origen, mapa);
}

Falla_T * caminoLocalizarFalla(NodoCamino_T * nodo_actual,
		NodoCamino_T * siguiente, float distancia_a_nodo_actual,
		MapaTuberias_T * mapa) {
	// OJO, esta es una funcion RECURSIVA!!!
	float medida = mapaTuberiasGetDistancia(mapa,
			nodoCaminoGetNombre(nodo_actual), nodoCaminoGetNombre(siguiente));

	if (medida > distancia_a_nodo_actual) {
		// la falla se encuentra entre nodo_accutal y siguiente
		Falla_T * falla_aux;
		falla_aux = malloc(sizeof(Falla_T));
		fallaConstruir(falla_aux, nodoCaminoGetNombre(nodo_actual),
				nodoCaminoGetNombre(siguiente), distancia_a_nodo_actual);
		return falla_aux;
	} else {
		// avanzo a siguiente tramo y resto la distancia del tramo anterior
		return caminoLocalizarFalla(siguiente,
				nodoCaminoGetSiguiente(siguiente),
				distancia_a_nodo_actual - medida, mapa);
	}
}

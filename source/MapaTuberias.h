/* MapaTuberias.h*/
#ifndef MAPATUBERIAS_H_
#define MAPATUBERIAS_H_

#include "Tramo.h"

/*
 * Mantiene la estructura tipo lista que conforman el diagrama de las tuberias
 * a traves de los distintos tramos que lo componen
 */
typedef struct {
	Tramo_T * primero;
	Tramo_T * ultimo;
} MapaTuberias_T;

/*
 * Inicializa la estructura MapaTuberias
 */
void mapaTuberiasConstruir(MapaTuberias_T * mapa);

/*
 * Libera los recursos utilizados por MapaTuberias
 */
void mapaTuberiasDestruir(MapaTuberias_T * mapa);

/*
 * Dado dos nodos inicial y final de un tramo y la distancia entre los mismos,
 * construye un nuevo tramo y lo agrega a la lista.
 */
void mapaTuberiasAgregarTramo(MapaTuberias_T * mapa, char * inicio, char * fin,
		int distancia);

/*
 * Dado el nombre de dos nodos "QUE SE CORRESPONDEN CON UN TRAMO VALIDO" nos
 * devuelve la distancia en metros entre sus extremos.
 */
int mapaTuberiasGetDistancia(MapaTuberias_T * mapa, char * inicio, char * fin);

#endif /* MAPATUBERIAS_H_ */

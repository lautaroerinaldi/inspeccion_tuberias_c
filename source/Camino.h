#ifndef CAMINO_H_
#define CAMINO_H_

#include "Falla.h"
#include "MapaTuberias.h"
#include "NodoCamino.h"

/*
 * Mantiene la estructura de lista enlazada simple de los nodos que constituyen
 * el recorrido del PIG.
 */
typedef struct {
	NodoCamino_T * primero;
	NodoCamino_T * ultimo;
	int distancia_total;
	int tamanio;
} Camino_T;

/*
 * Inicializa la estructura del camino como una lista vacia (sin nodos) y por
 * ende con distancia total del camino igual a CERO.
 */
void caminoContruir(Camino_T * camino);

/*
 * Libera los recursos utilizados por el Camino.
 */
void caminoDestruir(Camino_T * camino);

/*
 * Agrega nodos a la lista y dado el mapa de tuberias que contienen las
 * distancias entre un nodo y otro va calculando automaticamente el largo que
 * camino tienen "luego" de agregar el nodo.
 */
void caminoAgregarNodo(Camino_T * camino, char * nombre_nodo,
		MapaTuberias_T * mapa);

/*
 * Retorna el largo del camino entre el primer y el ultimo nodo de la lista.
 */
int caminoGetDistanciaTotal(Camino_T * camino);

/*
 * Si se sabe que hay una falla y se pudo calcular la distancia de esta al
 * origen del camino, esta funcion se encarga de localizar el tramo en donde
 * se encuentra la misma y retorna un objeto Falla que tienen los nodos inicial
 * y final del tramo mencionado y la posicion relativa de la falla al comienzo
 * del tramo.
 * OJO: Esta función devuelve un puntero a un objeto en memoria dinámica, y el
 * usuario que la invoque deberá recordar LIBERAR DICHA MEMORIA.
 */
Falla_T * caminoGetTramoFalla(Camino_T * camino, MapaTuberias_T * mapa,
		float distancia_a_origen);

/*
 * Función que dado los dos primeros nodos del camino, se encarga de localizar
 * recursivamente el tramo en donde se encuentra la misma y retorna un objeto
 * con los datos de dicho tramo en memoria dinámica. Dicha memoria debera
 * liberarse por la funcion llamadora.
 */
Falla_T * caminoLocalizarFalla(NodoCamino_T * nodo_actual,
		NodoCamino_T * siguiente, float distancia_a_nodo_actual,
		MapaTuberias_T * mapa);

#endif /* CAMINO_H_ */

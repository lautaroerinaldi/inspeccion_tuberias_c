/* Tramo.h */
#ifndef TRAMO_H_
#define TRAMO_H_

#define IGUALES 1
#define DISTINTOS 0
#define LONG_MAX_TRAMO 21 // 20 caracteres para el nombre y un \0 para terminar

/*
 * Cada Tramo en un elemento de una lista simplemente enlazada, donde cada uno
 * es un tramo del mapa de tuberias. Cada tramo esta compuesto por uno nodo de
 * inicio, un nodo de culminacion, la distancia entre dichos nodos.
 */
typedef struct Tramo {
	char inicio[LONG_MAX_TRAMO];
	char fin[LONG_MAX_TRAMO];
	int distancia;
	struct Tramo * siguiente;
} Tramo_T;

/*
 * Incicializa un tramo cuyos extremos son inicio y fin, y distancia es la
 * distancia entre los extremos del mismo
 */
void tramoConstruir(Tramo_T * tramo, char * inicio, char * fin, int distancia);

/*
 * Libera los recursos utilizados por Tramo
 */
void tramoDestruir(Tramo_T * tramo);

/*
 * Establece el siguiente elemento en la lista de tramos
 */
void tramoSetSiguiente(Tramo_T * tramo, Tramo_T * siguiente);

/*
 * Retorna un puntero al siguiente nodo de la lista, que resulta ser otro
 * tramo que no necesariamente comparte alguno de los extremos.
 */
Tramo_T * tramoGetSiguiente(Tramo_T * tramo);

/*
 * Retorna el nombre del nodo en donde inicia el tramo.
 */
char * tramoGetInicio(Tramo_T * tramo);

/*
 *  Retorna el nombre del nodo en donde culmina el tramo.
 */
char * tramoGetFin(Tramo_T * tramo);

/*
 *  Retorna la distancia entre los nodos inicial y final del tramo.
 */
int tramoGetDistancia(Tramo_T * tramo);

/*
 * Compara el tramo actual, con los extremos inicio y fin de otro tramo.
 * Retorna IGUALES si tramo empieza en en inicio y culmina en fin, y retorna
 * DISTINTOS en otro caso.
 */
char tramoSonIguales(Tramo_T * tramo, char * inicio, char * fin);

#endif /* TRAMO_H_ */

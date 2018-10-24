/* NodoCamino.h*/
#ifndef NODOCAMINO_H_
#define NODOCAMINO_H_

#define LONG_MAX_NODO 21 // 20 caracteres para el nombre y un \0 para terminar

/*
 * Son los nodos que construyen una lista simplemente enlazada
 * que indica cada una de las paradas del recorrido del PIG.
 */
typedef struct NodoCamino {
	char nombre[LONG_MAX_NODO];
	struct NodoCamino * siguiente;
} NodoCamino_T;

/*
 * Inicializa un nodo dado su nombre
 * El enlazado entre un nodo y otro debe hacerlo el usuario desde fuera de
 * la clase utilizando la funcion nodoCaminorGetSiguiente.
 */
void nodoCaminoContruir(NodoCamino_T * nodo, char * nombre);

/*
 * Libera los recursos utilizados por el nodo
 */
void nodoCaminoDestruir(NodoCamino_T * nodo);

/*
 * Retorna el nombre del nodo actual
 */
char * nodoCaminoGetNombre(NodoCamino_T * nodo);

/*
 * Retorna un puntero al siguiente nodo de la lista.
 */
NodoCamino_T * nodoCaminoGetSiguiente(NodoCamino_T * nodo);

/*
 * Setea el siguiente nodo de la lista enlazada, es decir, el usuario
 * del TDA es el encargado de asignar la secuencia de la lista.
 */
void nodoCaminoSetSiguiente(NodoCamino_T * nodo, NodoCamino_T * siguiente);

#endif /* NODOCAMINO_H_ */

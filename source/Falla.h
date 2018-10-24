/* Falla.h */
#ifndef FALLA_H_
#define FALLA_H_

#define LONG_NOM_NODO 21 // 20 caracteres para el nombre y un \0 para terminar

/*
 * Este TDA encapsula todos los atributos de la posicion de una falla ya
 * detectada. Estos son en los puntos inicial y final del tramo en que se
 * encuentra y la posicion relativa al inicio del tramo.
 */
typedef struct {
	char nodo_inicial[LONG_NOM_NODO];
	char nodo_final[LONG_NOM_NODO];
	float posicion_falla;
} Falla_T;

/*
 * Inicializa el TDA con los puntos inicial y final del tramo que contiene una
 * falla y la distancia relativa al inicio de dicho tramo en donde se encuentra
 * la falla.
 */
void fallaConstruir(Falla_T * falla, char * nodo_inicial, char * nodo_final,
		float posicion);

/*
 * Libera los recursos reservados por la clase Falla
 */
void fallaDestruir(Falla_T * falla);

/*
 * Retorna el nombre del nodo inicial del tramo en donde se encuentra la falla.
 */
char * fallaGetNodoInicial(Falla_T * falla);

/*
 * Retorna el nombre del nodo final del tramo en donde se encuentra la falla.
 */
char * fallaGetNodoFinal(Falla_T * falla);

/*
 * Retorna la posicion relativa al nodo inicial del tramo en donde se
 * encuentra la falla.
 */
float fallaGetPosicion(Falla_T * falla);

#endif /* FALLA_H_ */

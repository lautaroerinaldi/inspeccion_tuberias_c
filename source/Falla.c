#include "Falla.h"

#include <string.h>

void fallaConstruir(Falla_T * falla, char * nodo_inicial, char * nodo_final,
		float posicion) {
	strncpy(falla->nodo_inicial, nodo_inicial, LONG_NOM_NODO);
	strncpy(falla->nodo_final, nodo_final, LONG_NOM_NODO);
	falla->posicion_falla = posicion;
}

void fallaDestruir(Falla_T * falla) {
}

char * fallaGetNodoInicial(Falla_T * falla) {
	return falla->nodo_inicial;
}

char * fallaGetNodoFinal(Falla_T * falla) {
	return falla->nodo_final;
}

float fallaGetPosicion(Falla_T * falla) {
	return falla->posicion_falla;
}

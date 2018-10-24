#include "Sensor.h"

#include <stdio.h>
#include <stdlib.h>

#include "Falla.h"

#define RUPTURA 0xFF
#define CORROSION 0XA0

void sensorConstruir(Sensor_T * sensor, float metros_por_muestra,
		unsigned int cantidad_muestras_umbral_corrosion, Camino_T * camino,
		MapaTuberias_T * mapa) {
	sensor->metros_por_muestra = metros_por_muestra;
	sensor->cantidad_muestras_umbral_corrosion =
			cantidad_muestras_umbral_corrosion;
	sensor->muestras_corrosion_acumuladas = 0;
	sensor->numero_de_muestra = 0;
	sensor->muestra_inicio_corrosion = 0;
	sensor->camino = camino;
	sensor->mapa = mapa;
	sensor->siguiente = NULL;
}

void sensorDestruir(Sensor_T * sensor) {
}

void sensorProcesarCorrosion(Sensor_T * sensor) {
	// indico que la muestra es la posicion desde donde empezar a contabilizar
	// corrosion para futuras muestras consecutivas
	if (sensor->muestra_inicio_corrosion == 0)
		sensor->muestra_inicio_corrosion = sensor->numero_de_muestra;

	++sensor->muestras_corrosion_acumuladas;

	// supere umbral de corrosion?
	if (sensor->muestras_corrosion_acumuladas
			>= sensor->cantidad_muestras_umbral_corrosion) {
		Falla_T * falla_aux;
		// localizo la posicion relativa al tramo en donde se encuentra la falla.
		falla_aux = caminoGetTramoFalla(sensor->camino, sensor->mapa,
				sensor->muestra_inicio_corrosion * sensor->metros_por_muestra);
		printf("CORROSION %s->%s (%.2fm)\n", fallaGetNodoInicial(falla_aux),
				fallaGetNodoFinal(falla_aux), fallaGetPosicion(falla_aux));
		fallaDestruir(falla_aux);
		free(falla_aux);
		// reinicio punto de partida para contabilizar corrosion
		sensor->muestras_corrosion_acumuladas = 0;
		sensor->muestra_inicio_corrosion = 0;
	}
}

void sensorProcesarRuptura(Sensor_T * sensor) {
	Falla_T * falla_aux;
	// localizo la posicion relativa al tramo en donde se encuentra la falla.
	falla_aux = caminoGetTramoFalla(sensor->camino, sensor->mapa,
			sensor->numero_de_muestra * sensor->metros_por_muestra);
	printf("RUPTURA %s->%s (%.2fm)\n", fallaGetNodoInicial(falla_aux),
			fallaGetNodoFinal(falla_aux), fallaGetPosicion(falla_aux));
	fallaDestruir(falla_aux);
	free(falla_aux);
}

void sensorProcesarMuestra(Sensor_T * sensor, u_int16_t muestra_leida) {
	++sensor->numero_de_muestra;

	if (muestra_leida > RUPTURA) {		// hay fuga?
		sensorProcesarRuptura(sensor);
		// fuga implica corrosion
		sensorProcesarCorrosion(sensor);
	} else {
		if (muestra_leida >= CORROSION) {	// hay corrosion?
			sensorProcesarCorrosion(sensor);
		} else {	// si no hay corrosion, tengo una discontinuidad y reinicio
					// el punto de partida desde donde contar corrosion y la
					// cantidad de muestras consecutivas que tenian corrosion
			sensor->muestras_corrosion_acumuladas = 0;
			sensor->muestra_inicio_corrosion = 0;
		}
	}
}

Sensor_T * sensorGetSiguiente(Sensor_T * sensor) {
	return sensor->siguiente;
}

void sensorSetSiguiente(Sensor_T * sensor, Sensor_T * siguiente) {
	sensor->siguiente = siguiente;
}

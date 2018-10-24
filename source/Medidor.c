#include "Medidor.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define METROS_UMBRAL_CORROSION 0.5
#define MINUTOS_EN_UNA_HORA 60

void medidorCalcularParametrosRestantes(Medidor_T * medidor) {
	medidor->metros_por_muestra = (double) (medidor->velocidad_flujo)
			/ (medidor->velocidad_sensado * MINUTOS_EN_UNA_HORA);

	medidor->cantidad_muestras_umbral_corrosion = ceil(
			(METROS_UMBRAL_CORROSION * MINUTOS_EN_UNA_HORA
					* medidor->velocidad_sensado) / medidor->velocidad_flujo);

	medidor->muestras_esperadas = truncf(
			medidor->cantidad_sensores
					* caminoGetDistanciaTotal(&medidor->camino)
					/ medidor->metros_por_muestra);

	medidor->cantidad_muestras_leidas = 0;
}

void medidorCrearListaSensores(Medidor_T * medidor) {
	Sensor_T * ultimo_sensor_agregado;
	ultimo_sensor_agregado = NULL;
	for (int x = 0; x < medidor->cantidad_sensores; ++x) {
		Sensor_T * sensor_aux;
		sensor_aux = malloc(sizeof(Sensor_T));
		sensorConstruir(sensor_aux, medidor->metros_por_muestra,
				medidor->cantidad_muestras_umbral_corrosion, &medidor->camino,
				&medidor->mapa);

		if (x == 0)
			medidor->primer_sensor = sensor_aux;
		else
			sensorSetSiguiente(ultimo_sensor_agregado, sensor_aux);

		ultimo_sensor_agregado = sensor_aux;
	}
	//lo convierto en buffer circular, haciendo que el primer sensor sea el
	// siguiente del ultimo.
	sensorSetSiguiente(ultimo_sensor_agregado, medidor->primer_sensor);
	medidor->sensor_actual = medidor->primer_sensor;
}

void medidorDestruirListaSensores(Medidor_T * medidor) {
	if (medidor->primer_sensor) {
		Sensor_T * sensor_a_borrar = medidor->primer_sensor;
		Sensor_T * sensor_siguiente = sensorGetSiguiente(sensor_a_borrar);

		for (int x = 0; x < medidor->cantidad_sensores; ++x) {
			sensorDestruir(sensor_a_borrar);
			free(sensor_a_borrar);
			sensor_a_borrar = sensor_siguiente;
			// como es buffer circular, al ultimo no le puedo pedir el
			// siguiente, ya estan todos liberados
			if (x < medidor->cantidad_sensores - 1)
				sensor_siguiente = sensorGetSiguiente(sensor_a_borrar);
		}
	}
}

void medidorConstruir(Medidor_T * medidor, Parser_T * parser) {
	medidor->parser = parser;
	mapaTuberiasConstruir(&medidor->mapa);
	parserLeerTuberias(medidor->parser, &medidor->mapa);
	caminoContruir(&medidor->camino);
	parserLeerRecorrido(medidor->parser, &medidor->camino, &medidor->mapa);

	parserLeerParametrosMediciones(medidor->parser, &medidor->velocidad_flujo,
			&medidor->velocidad_sensado, &medidor->cantidad_sensores);
	medidorCalcularParametrosRestantes(medidor);
	medidorCrearListaSensores(medidor);
}

void medidorDestruir(Medidor_T * medidor) {
	caminoDestruir(&medidor->camino);
	mapaTuberiasDestruir(&medidor->mapa);
	medidorDestruirListaSensores(medidor);
}

char medidorProcesarMediciones(Medidor_T * medidor) {
	u_int16_t muestra_leida = 0;

	while (parserLeerMuestra(medidor->parser, &muestra_leida) == LECTURA_OK) {
		++medidor->cantidad_muestras_leidas;
		sensorProcesarMuestra(medidor->sensor_actual, muestra_leida);
		//digo que la proxima muestra la va a procesar el siguiente sensor
		medidor->sensor_actual = sensorGetSiguiente(medidor->sensor_actual);
	}

	if (medidor->cantidad_muestras_leidas != medidor->muestras_esperadas) {
		fprintf(stderr, "Cantidad de muestras incorrectas\n");
		return CANT_MUESTRAS_ERROR;
	} else {
		return CANT_MUESTRAS_CORRECTAS;
	}
}

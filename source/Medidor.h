#ifndef MEDIDOR_H_
#define MEDIDOR_H_

#include <sys/types.h>

#include "Camino.h"
#include "MapaTuberias.h"
#include "Parser.h"
#include "Sensor.h"

#define CANT_MUESTRAS_CORRECTAS 0
#define CANT_MUESTRAS_ERROR 1

/*
 * El Medidor se encarga de realizar el trabajo de analizar las muestras
 * tomadas por el PIG y leidas desde el archivo de mediciones y de utilizar al
 * parser para crear las estructuras necesarias para poder detectar CORROSION y
 * RUPTURA.
 */
typedef struct {
	u_int32_t velocidad_flujo;
	u_int32_t velocidad_sensado;
	u_int32_t cantidad_sensores;
	double metros_por_muestra;
	unsigned int cantidad_muestras_umbral_corrosion;
	float muestras_esperadas;
	unsigned int cantidad_muestras_leidas;

	Parser_T * parser;
	Sensor_T * primer_sensor;
	Sensor_T * sensor_actual; // es el que va a procesar la muestra leida

	Camino_T camino;
	MapaTuberias_T mapa;
} Medidor_T;

/*
 * Una vez leidos los parametros de entrada del archivo de mediciones calcula
 * los parametros metros_por_muestra, cantidad_muestras_umbral_corrosion, y
 * la cantidad de muestras_esperadas.
 */
void medidorCalcularParametrosRestantes(Medidor_T * medidor);

/*
 * Supone que parser ya ha sido debidamente inicializado y los archivos de
 * entrada los pudo abrir exitosamente.
 * Inicializa todas las estructuras en memoria necesarias a partir de los
 * archivos de entrada para quedar en condiciones de empezar a procesar las
 * muestras.
 */
void medidorConstruir(Medidor_T * medidor, Parser_T * parser);

/*
 * Libera los recursos utilizados por el Medidor
 */
void medidorDestruir(Medidor_T * medidor);

/*
 * Recorre todas las muestras tomadas por el PIG y va reportando por pantalla
 * si hay una RUPTURA o una CORROSION (en el caso de que se haya superado la
 * cantidad de muestras que indica el umbral).
 * Retorna CANT_MUESTRAS_CORRECTAS en caso de que que la cantidad de muestras
 * leidas y procesadas coincida con la cantidad de muestras esperadas (que
 * fueron calculadas a partir de los parametros de entrada) y retorna en caso
 * de que no coincidan, CANT_MUESTRAS_ERROR.
 */
char medidorProcesarMediciones(Medidor_T * medidor);

/*
 * A partir del parametro cantidad de sensores leidos del archivo de mediciones
 * crea e inicializa una lista de sensores de igual numero de elementos con los
 * parametros necesarios para que cada uno pueda detectar por si mismo si se
 * encontro CORROSION o una RUPTURA.
 */
void medidorCrearListaSensores(Medidor_T * medidor);

/*
 * Destruye la lista de sensores que se genero con la invocacion a la funcion
 * medidorCrearListaSensores, y libera los recursos reservador por la misma.
 */
void medidorDestruirListaSensores(Medidor_T * medidor);

#endif /* MEDIDOR_H_ */


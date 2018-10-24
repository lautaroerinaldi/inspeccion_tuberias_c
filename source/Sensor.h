/* Sensor.h */
#ifndef SENSOR_H_
#define SENSOR_H_

#include <sys/types.h>

#include "Camino.h"
#include "MapaTuberias.h"

/*
 * Cada sensor es un nodo de una lista simplemente enlazada. Tienen control de
 * las ultimas muestras con corrosion y dada una muestra determina si se
 * trata de una RUPTURA o si esta ultima muestra hace que se supere la
 * cantidad de muestras que determinan que hay corrosion en la tuberia.
 * El enlazado entre un nodo y otro debe hacerlo el usuario desde fuera de
 * la clase utilizando la funcion sensorGetSiguiente.
 */
typedef struct Sensor {
	float metros_por_muestra;
	unsigned int cantidad_muestras_umbral_corrosion;
	unsigned int muestras_corrosion_acumuladas;
	unsigned int numero_de_muestra;	//cada sensor sabe cuantas muestras proceso
	unsigned int muestra_inicio_corrosion;
	Camino_T * camino;
	MapaTuberias_T * mapa;
	struct Sensor * siguiente;
} Sensor_T;

/*
 * Inicializa un sensor para que tambien pueda actuar como analizador de las
 * muestras.
 */
void sensorConstruir(Sensor_T * sensor, float metros_por_muestra,
		unsigned int cantidad_muestras_umbral_corrosion, Camino_T * camino,
		MapaTuberias_T * mapa);

/*
 * Libera los recursos utilizados por el sensor.
 */
void sensorDestruir(Sensor_T * sensor);

/*
 * Dada una muestra determina si se esta supera el umbral de RUPTURA o en caso
 * de superar el umbral de CORROSION, determina si ya se han alcanzado la
 * cantidad de muestras necesarias para asegurar que el tramo de tuberia esta
 * corroido.
 */
void sensorProcesarMuestra(Sensor_T * sensor, u_int16_t muestra_leida);

/*
 * Retorna un puntero al siguiente sensor/nodo de la lista.
 */
Sensor_T * sensorGetSiguiente(Sensor_T * sensor);

/*
 * Setea el siguiente nodo/sensor de la lista enlazada, es decir, el usuario
 * del TDA es el encargado de asignar la secuencia de la lista.
 */
void sensorSetSiguiente(Sensor_T * sensor, Sensor_T * siguiente);

/*
 * Solo debe invocarse si la muestra leida supera el umbral de corrosion.
 * Verifica si la muestra actual hace que se supere la cantidad de muestras
 * consecutivas necesarias para indicar que hay corrosion en  un tramo de
 * cañeria y en ese caso localiza la posicion relativa de la falla en
 * el tramo y muestra por pantalla.
 * Si no se supero el umbral, incrementa en uno la cantidad de muestras
 * consecutivas acumuladas de corrosion y actualiza la posicion de inicio de
 * corrosion
 */
void sensorProcesarCorrosion(Sensor_T * sensor);

/*
 * Solo debe invocarse si la muestra leida supera el umbral de ruptura.
 * Localiza la posicion relativa de la falla en el tramo y muestra por pantalla
 */
void sensorProcesarRuptura(Sensor_T * sensor);

#endif /* SENSOR_H_ */

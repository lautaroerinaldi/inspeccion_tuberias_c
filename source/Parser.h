#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <sys/types.h>

#include "Camino.h"
#include "MapaTuberias.h"

#define LECTURA_OK 1
#define LECTURA_FALLO 0

#define APERTURA_OK 0
#define APERTURA_FALLO 1

/* El PARSER se encarga de lo que respecta a la apertura y cierre de archivos,
 * como asi tambien de ir construyendo las estructuras Camino y Mapa a medida
 * que va leyendo los archivos de entrada. Lee los parametros de entrada
 * (velocidades y cantidad de sensores) y tambien las muestras que leyo el PIG.
 */
typedef struct {
	FILE * arch_mediciones;
	FILE * arch_tuberias;
	FILE * arch_recorrido;
} Parser_T;

/*
 * Analiza los argumentos de entrada del programa y retorna APERTURA_FALLO en
 * caso de que la cantidad de argumentos sea incorrecta o los archivos de
 * entrada sean inaccesibles o retorna APERTURA_OK en caso de que los
 * argumentos de entrada sean 4: nombre del programa, archivo de mediciones,
 * archivo de tuberias y archivo de recorrido. Abre dichos archivos.
 */
char parserConstruir(Parser_T * parser, int cant_args_recibidos,
		char *argumentos[]);

/*
 * Cierra los archivos que se lograron abrir en parserConstruir y libera todos
 * los recursos utilizador por Parser.
 */
void parserDestruir(Parser_T * parser);

/*
 * Parsea el archivo de recorrido pasado como argumento en parserContruir y
 * almacena en camino una lista simple con el recorrido que hace el PIG.
 * Supone que el mapa ha sido previamente inicializado al llamar a
 * parserLeerTuberias.
 */
void parserLeerRecorrido(Parser_T * parser, Camino_T * camino,
		MapaTuberias_T * mapa);

/*
 * Parsea el archivo de tuberias pasado como argumento en parserContruir y
 * almacena en mapa la estructura de los distintos tramos que poseen las
 * tuberias.
 */
void parserLeerTuberias(Parser_T * parser, MapaTuberias_T * mapa);

/*
 * Parsea del archivo de mediciones pasado como argumento en parserContruir
 * los parametros velocidad de flujo (en metros/hora), velocidad de sensado
 * (en muestras por minuto) y cantidad de sensores y los almacena en las
 * variables pasadas por parametro.
 * Lee en formato BigEndian y retorna en el formato que corresponda a la PC en
 * donde se este corriendo.
 */
void parserLeerParametrosMediciones(Parser_T * parser,
		u_int32_t * velocidad_flujo, u_int32_t * velocidad_sensado,
		u_int32_t * cantidad_sensores);

/*
 * Intenta leer una muestra del archivo de mediciones pasado como argumento en
 * parserConstruir y la almacena en muestra_leida. Lee en formato BigEndian y
 * retorna en el formato que corresponda a la PC en donde se este corriendo.
 * Retorna LECTURA_OK si pudo leerse una muestra, en caso contrario retorna
 * LECTURA_FALLO y esto indica que ya no quedan muestras por leer.
 */
char parserLeerMuestra(Parser_T * parser, u_int16_t * muestra_leida);

/*
 * Dado un FILE *, lo cierra si el mismo es valido; En otro caso, no hace
 * nada.
 */
void parserCerrarArchivo(FILE * archivo_a_cerrar);

#endif /* PARSER_H_ */

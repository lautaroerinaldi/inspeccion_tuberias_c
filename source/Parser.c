#include "Parser.h"

#include <netinet/in.h>

#define POS_ARCH_MEDICIONES 1
#define POS_ARCH_TUBERIAS 2
#define POS_ARCH_RECORRIDO 3
#define CANT_ARGS_ESPERADOS 4

char parserConstruir(Parser_T * parser, int cant_args_recibidos,
		char * argumentos[]) {
	parser->arch_mediciones = NULL;
	parser->arch_tuberias = NULL;
	parser->arch_recorrido = NULL;
	char resultado_apertura;

	// verifico que el programa se haya llamado con todos sus argumentos
	if (cant_args_recibidos == CANT_ARGS_ESPERADOS) {
		parser->arch_mediciones = fopen(argumentos[POS_ARCH_MEDICIONES], "rb");
		parser->arch_tuberias = fopen(argumentos[POS_ARCH_TUBERIAS], "r");
		parser->arch_recorrido = fopen(argumentos[POS_ARCH_RECORRIDO], "r");

		//si alguno de los archivos no pudo ser abierto
		if ((parser->arch_mediciones == NULL) || (parser->arch_tuberias == NULL)
				|| (parser->arch_recorrido == NULL)) {
			//ERROR, al menos un archivo de entrada no pudo ser abierto
			fprintf(stderr, "Archivo inválido\n");
			resultado_apertura = APERTURA_FALLO;
		} else {
			//OK, los 3 archivos de entrada pudieron ser abiertos
			resultado_apertura = APERTURA_OK;
		}
	} else {
		//ERROR, falla en la cantidad de argumentos
		fprintf(stderr, "Archivo inválido\n");
		resultado_apertura = APERTURA_FALLO;
	}
	return resultado_apertura;
}

void parserDestruir(Parser_T * parser) {
	parserCerrarArchivo(parser->arch_mediciones);
	parserCerrarArchivo(parser->arch_tuberias);
	parserCerrarArchivo(parser->arch_recorrido);
}

void parserCerrarArchivo(FILE * archivo_a_cerrar) {
	if (archivo_a_cerrar)
		fclose(archivo_a_cerrar);
}

void parserLeerTuberias(Parser_T * parser, MapaTuberias_T * mapa) {
	while (!feof(parser->arch_tuberias)) {
		// se asume que el archivo de entrada esta bien formado, y que el nombre
		// de cada nodo tiene como maximo 20 caracteres
		char nodo_inicial[LONG_MAX_NODO] = "";
		char nodo_final[LONG_MAX_NODO] = "";
		int distancia = 0;
		int leidos = fscanf(parser->arch_tuberias, "%[^,],%d,%[^\n]\n",
				nodo_inicial, &distancia, nodo_final);

		if (leidos == 3) // OK, fscanf logro leer los 3 argumenos
			mapaTuberiasAgregarTramo(mapa, nodo_inicial, nodo_final, distancia);
	}
}

void parserLeerRecorrido(Parser_T * parser, Camino_T * camino,
		MapaTuberias_T * mapa) {
	// se asume que el archivo de entrada esta bien formado, y que el nombre
	// de cada nodo tiene como maximo 20 caracteres
	while (!feof(parser->arch_recorrido)) {
		char tramo[LONG_MAX_NODO] = "";
		int leidos = fscanf(parser->arch_recorrido, "%s\n", tramo);
		if (leidos == 1) // OK, fscanf logro leer un nodo del archivo
			caminoAgregarNodo(camino, tramo, mapa);
	}
}

void parserLeerParametrosMediciones(Parser_T * parser,
		u_int32_t * velocidad_flujo, u_int32_t * velocidad_sensado,
		u_int32_t * cantidad_sensores) {
	int leidos = 0;

	// se leen 4 bytes que corresponden a la velocidad de flujo
	leidos += fread(velocidad_flujo, sizeof(u_int32_t), 1,
			parser->arch_mediciones);
	// se leen 4 bytes que corresponden a la velocidad de sensado
	leidos += fread(velocidad_sensado, sizeof(u_int32_t), 1,
			parser->arch_mediciones);
	// se leen 4 bytes que corresponden a la cantidad de sensores
	leidos += fread(cantidad_sensores, sizeof(u_int32_t), 1,
			parser->arch_mediciones);
	if (leidos == 3) {	//OK, fread pudo leer todos los parametros de entrada
		*velocidad_flujo = ntohl(*velocidad_flujo);
		*velocidad_sensado = ntohl(*velocidad_sensado);
		*cantidad_sensores = ntohl(*cantidad_sensores);
	}
}

char parserLeerMuestra(Parser_T * parser, u_int16_t * muestra_leida) {
	if (fread(muestra_leida, sizeof(u_int16_t), 1, parser->arch_mediciones)) {
		*muestra_leida = ntohs(*muestra_leida);
		return LECTURA_OK;
	} else {
		return LECTURA_FALLO;
	}
}

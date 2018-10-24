#include "Medidor.h"
#include "Parser.h"

#define EJECUCION_EXITOSA 0
#define EJECUCION_FALLIDA 1

int main(int argc, char *argv[]) {
	char resultado_ejecucion = EJECUCION_FALLIDA;

	Parser_T parser;
	if (parserConstruir(&parser, argc, argv) == APERTURA_OK) {
		Medidor_T medidor;
		medidorConstruir(&medidor, &parser);
		if (medidorProcesarMediciones(&medidor) == CANT_MUESTRAS_CORRECTAS)
			resultado_ejecucion = EJECUCION_EXITOSA;

		medidorDestruir(&medidor);
	}
	parserDestruir(&parser);
	return resultado_ejecucion;
}

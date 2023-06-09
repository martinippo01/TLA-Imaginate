#include "backend/code-generation/generator.h"
#include "backend/errors/error-list.h"
#include "backend/support/garbage-collector.h"
#include "backend/symbols-table/definitions/hashmap_defs.h"
#include "backend/symbols-table/values/hashmap_val.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>

// Estado de la aplicación.
CompilerState state;

const int main(const int argumentCount, const char ** arguments) {

	state.program = NULL;
	state.result = 0;
	state.succeed = false;
	initHashMap(state.symbols_table);
	initDefsTable(state.defs_table);
	initErrorsList(state.errors);
	

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				Generator(state.program);
			}
			else {
				LogError("Se produjo un error en la aplicacion.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	
	TraverseErrorList(&state.errors);
	LogInfo("Fin.");

	//decirle al garbage-collector que libere toda la memoria
	free_all();
	destroy(state.symbols_table);
	destroyDefsTable(state.defs_table);
	
	return result;
}

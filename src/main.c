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
	state.succeed = UNDEFINED;
	state.next_object_id = 0;
	initHashMap(state.symbols_table);
	initDefsTable(state.defs_table);
	initErrorsList(state.errors);
	

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argument %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compiling...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed == SUCCESS) {
				LogInfo("Compilation successful");
				Generator(state.program);
			}
			break;
		case 1:
			LogError("There is a syntax error in the program");
			break;
		case 2:
			LogError("There was not enough memory to carry out parser");
			break;
		default:
			LogError("Errors found in compilation");
	}
	
	printHashMap(state.symbols_table);
	TraverseErrorList(&state.errors);

	//decirle al garbage-collector que libere toda la memoria
	free_all();
	destroy(state.symbols_table);
	destroyDefsTable(state.defs_table);
	
	return result == 0 ? state.succeed : result;
}

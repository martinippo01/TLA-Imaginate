#include "backend/code-generation/generator.h"
#include "backend/errors/error-list.h"
#include "backend/support/garbage-collector.h"
#include "backend/symbols-table/definitions/hashmap_defs.h"
#include "backend/symbols-table/values/hashmap_val.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>
#include <getopt.h>

// Estado de la aplicación.
CompilerState state;


typedef struct Args {
	// -x Run after compile
	int x;
	// -o set output file name
	int o;
	char * fileName;
} Args;

void parseArgs(const int argc, const char **argv, Args *args){

        int option_index = 0;
        static struct option long_options[] = {
            { "doh-ip",    no_argument, 0, 0xD001 },
            { "doh-port",  no_argument, 0, 0xD002 },
            { "doh-host",  no_argument, 0, 0xD003 },
            { "doh-path",  no_argument, 0, 0xD004 },
            { "doh-query", no_argument, 0, 0xD005 },
            { 0,           0,                 0, 0 }
        };
	
	char c;
	
	args->x = 0;
	args->o = 0;
	args->fileName = "generator.py";

	while((c = getopt_long(argc, argv, "xo:", long_options, &option_index)) != -1){
		switch (c)
		{
		case 'x':
			args->x = 1;
			break;
		
		case 'o':
			args->o = 1;
			args->fileName = optarg;
			break;

		default:
			break;
		}
	}

}


const int main(const int argumentCount, const char ** arguments) {

	state.program = NULL;
	state.result = 0;
	state.succeed = false;
	initHashMap(state.symbols_table);
	initDefsTable(state.defs_table);
	initErrorsList(state.errors);
	
	Args args;
	
	parseArgs(argumentCount, arguments, &args);

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				Generator(state.program, args.x, args.fileName);
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
	if(state.succeed) {
		LogInfo("Compilation successfull!");
	} else {
		LogError("Errors found in compilation");
	}

	//decirle al garbage-collector que libere toda la memoria
	free_all();
	destroy(state.symbols_table);
	destroyDefsTable(state.defs_table);
	
	return result;
}

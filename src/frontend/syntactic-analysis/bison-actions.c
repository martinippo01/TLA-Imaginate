#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

int AssignmentsGrammarAction(const int assignment, const int assignments) {
    
    return 0;
}

int AssignmentGrammarAction(const int assignment, const int assignments) {
	return 0;
}
int EmptyAssignmentsGrammarAction() {
    
    return 0;
}

int VariableIdentifierGrammarAction(const int variable) {
	return 0;
}

int ValueStringGrammarAction(const int sval) {
    
    return 0;
}

int ValueIntegerGrammarAction(const int ival) {
    
    return 0;
}

int DefinitionsGrammarAction(const int definition, const int definitions) {
    
    return 0;
}

int EmptyDefinitionsGrammarAction() {
    
    return 0;
}

int DefinitionGrammarAction(const int variableIdentifier, const int methodChain) {
    
    return 0;
}

int EmptyParamsGrammarAction() {
    
    return 0;
}

int ImaginateGrammarAction(const int focus, const int methodChain, const int render) {
    
    return 0;
}

int FocusAddGrammarAction(const int paramsBlock) {
    
    return 0;
}

int FocusForEachGrammarAction(const int paramsBlock) {
    
    return 0;
}

int MethodChainGrammarAction(const int method, const int methodChain) {
    
    return 0;
}

int EmptyMethodChainGrammarAction() {
    
    return 0;
}

int MethodGrammarAction(const int optional, const int methodIdentifier, const int paramsBlock) {
    
    return 0;
}

int ParamsBlockGrammarAction(const int params) {
    
    return 0;
}

int OptionalQuestionSignGrammarAction() {
    
    return 0;
}

int EmptyOptionalGrammarAction() {
    
    return 0;
}

int ParamsGrammarAction(const int param, const int params) {
    
    return 0;
}

int ParamStringGrammarAction(const int sval) {
    
    return 0;
}

int ParamIntegerGrammarAction(const int ival) {
    
    return 0;
}

int RenderGrammarAction() {
    
    return 0;
}

int RenderAllGrammarAction() {
    
    return 0;
}

int MethodIdentifierGrammarAction(const int sval) {
    
    return 0;
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
	int ProgramGrammarAction(const int assignments, const int definitions, const int imaginate) {

	LogDebug("\tProgramGrammarAction(%d, %d, %d)", assignments, definitions, imaginate);
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = imaginate;
	return imaginate;
}


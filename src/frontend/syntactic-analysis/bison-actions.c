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

int ParamInlineObjectGrammarAction(const int inlineObject) {
    LogDebug("ParamInlineObjectGrammarAction: valueObject = %d", inlineObject);
    return 0;
}
int InlineObjectGrammarAction(const int objectIdentifier) {
    LogDebug("InlineObject: valueObject = %d", objectIdentifier);
    return 0;
}
 
int ValueObjectGrammarAction(const int valueObject) {
    LogDebug("ValueObjectGrammarAction: valueObject = %d", valueObject);
    return 0;
}

int ParamObjectGrammarAction(const int paramObject) {
    LogDebug("ParamObjectGrammarAction: paramObject = %d", paramObject);
    return 0;
}

int ObjectIdentifierGrammarAction(const int objectIdentifier) {
    LogDebug("ObjectIdentifierGrammarAction: objectIdentifier = %d", objectIdentifier);
    return 0;
}

int ObjectContentGrammarAction(const int objectAssignment, const int objectContent) {
    LogDebug("ObjectContentGrammarAction: objectAssignment = %d, objectContent = %d", objectAssignment, objectContent);
    return 0;
}

int EmptyObjectContentGrammarAction() {
    LogDebug("EmptyObjectContentGrammarAction");
    return 0;
}

int ParamObjectElementGrammarAction(const int objectElement) {
    LogDebug("ParamObjectElementGrammarAction: objectElement = %d", objectElement);
    return 0;
}

int ObjectElementGrammarAction(const int variableIdentifier, const int objectElement) {
    LogDebug("ObjectElementGrammarAction: variableIdentifier = %d, objectElement = %d", variableIdentifier, objectElement);
    return 0;
}

int ObjectAssignmentGrammarAction(const int variableIdentifier, const int value) {
    LogDebug("ObjectAssignmentGrammarAction: variableIdentifier = %d, value = %d", variableIdentifier, value);
    return 0;
}

int ParamVariableGrammarAction(const int variableIdentifier) {
    LogDebug("ParamVariableGrammarAction: variableIdentifier = %d", variableIdentifier);
 		return 0;
}

int AssignmentGrammarAction(const int assignment, const int assignments) {
    LogDebug("AssignmentGrammarAction: assignment = %d, assignments = %d", assignment, assignments);
    return 0;
}

int EmptyAssignmentsGrammarAction() {
    LogDebug("EmptyAssignmentsGrammarAction");
    return 0;
}

int VariableIdentifierGrammarAction(const int variable) {
    LogDebug("VariableIdentifierGrammarAction: variable = %d", variable);
    return 0;
}

int ValueStringGrammarAction(const int sval) {
    LogDebug("ValueStringGrammarAction: sval = %d", sval);
    return 0;
}

int ValueIntegerGrammarAction(const int ival) {
    LogDebug("ValueIntegerGrammarAction: ival = %d", ival);
    return 0;
}

int EmptyDefinitionsGrammarAction() {
    LogDebug("EmptyDefinitionsGrammarAction");
    return 0;
}

int DefinitionGrammarAction(const int variableIdentifier, const int methodChain) {
    LogDebug("DefinitionGrammarAction: variableIdentifier = %d, methodChain = %d", variableIdentifier, methodChain);
    return 0;
}

int EmptyParamsGrammarAction() {
    LogDebug("EmptyParamsGrammarAction");
    return 0;
}

int FocusAddGrammarAction(const int paramsBlock) {
    LogDebug("FocusAddGrammarAction: paramsBlock = %d", paramsBlock);
    return 0;
}

int FocusForEachGrammarAction(const int paramsBlock) {
    LogDebug("FocusForEachGrammarAction: paramsBlock = %d", paramsBlock);
    return 0;
}

int MethodChainGrammarAction(const int method, const int methodChain) {
    LogDebug("MethodChainGrammarAction: method = %d, methodChain = %d", method, methodChain);
    return 0;
}

int EmptyMethodChainGrammarAction() {
    LogDebug("EmptyMethodChainGrammarAction");
    return 0;
}

int MethodGrammarAction(const int optional, const int methodIdentifier, const int paramsBlock) {
    LogDebug("MethodGrammarAction: optional = %d, methodIdentifier = %d, paramsBlock = %d", optional, methodIdentifier, paramsBlock);
    return 0;
}

int ParamsBlockGrammarAction(const int params) {
    LogDebug("ParamsBlockGrammarAction: params = %d", params);
    return 0;
}

int OptionalQuestionSignGrammarAction() {
    LogDebug("OptionalQuestionSignGrammarAction");
    return 0;
}


int EmptyOptionalGrammarAction() {
    LogDebug("EmptyOptionalGrammarAction");
    return 0;
}

int ParamsGrammarAction(const int param, const int params) {
    LogDebug("ParamsGrammarAction: param = %d, params = %d", param, params);
    return 0;
}

int ParamGrammarAction(const int param) {
    LogDebug("ParamsGrammarAction: param = %d", param);
    return 0;
}

int ParamStringGrammarAction(const int sval) {
    LogDebug("ParamStringGrammarAction: sval = %d", sval);
    return 0;
}

int ParamIntegerGrammarAction(const int ival) {
    LogDebug("ParamIntegerGrammarAction: ival = %d", ival);
    return 0;
}

int RenderGrammarAction() {
    LogDebug("RenderGrammarAction");
    return 0;
}

int RenderAllGrammarAction() {
    LogDebug("RenderAllGrammarAction");
    return 0;
}

int MethodIdentifierGrammarAction(const int sval) {
    LogDebug("MethodIdentifierGrammarAction: sval = %d", sval);
    return 0;
}


AssignmentsNode* AssignmentsGrammarAction(AssignmentNode* assignment, AssignmentsNode* next) {
    LogDebug("AssignmentsGrammarAction: assignment = %d, assignments = %d", assignment, next);
    AssignmentsNode* assignments = malloc(sizeof(AssignmentsNode));
    assignments->assignment = assignment;
    assignments->next = next;
    return assignments;
}

DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next) {
    LogDebug("DefinitionsGrammarAction: definition = %d, definitions = %d", definition, next);
    DefinitionsNode* definitions = malloc(sizeof(DefinitionsNode));
    definitions->definition = definition;
    definitions->next = next;
    return definitions;
}

ImaginateNode* ImaginateGrammarAction(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render) {
    LogDebug("ImaginateGrammarAction: focus = %d, methodChain = %d, render = %d", focus, methodChain, render);
    ImaginateNode* imaginate = malloc(sizeof(ImaginateNode));
    imaginate->focus = focus;
    imaginate->methodChain = methodChain;
    imaginate->render = render;
    return imaginate;
}

// Other grammar actions go here...

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
 ProgramNode* ProgramGrammarAction(AssignmentsNode* assignments, DefinitionsNode* definitions, ImaginateNode* imaginate) {

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

    ProgramNode* program = malloc(sizeof(ProgramNode));
    program->assignments = assignments;
    program->definitions = definitions;
    program->imaginate = imaginate;
    return program;
}

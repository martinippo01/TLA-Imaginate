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

ParamNode * ParamInlineObjectGrammarAction(InlineObjectNode * inlineObject) {
    LogDebug("ParamInlineObjectGrammarAction: valueObject = %d", inlineObject);
    return 0;
}
 
ValueNode * ValueObjectGrammarAction(ObjectIdentifierNode * objectIdentifier) {
    LogDebug("ValueObjectGrammarAction: valueObject = %d");
    return 0;
}


ObjectContentNode* EmptyObjectContentGrammarAction() {
    LogDebug("EmptyObjectContentGrammarAction");
    return 0;
}

ParamNode * ParamObjectElementGrammarAction(ObjectElementNode * objectElement) {
  LogDebug("ParamObjectElementGrammarAction: objectElement = %d", objectElement);

    return 0;
}


ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier) {
    LogDebug("ParamVariableGrammarAction: variableIdentifier = %d", variableIdentifier);
 		return 0;
}


AssignmentNode * EmptyAssignmentsGrammarAction() {
    LogDebug("EmptyAssignmentsGrammarAction");
    return 0;
}


DefinitionNode * EmptyDefinitionsGrammarAction() {
    LogDebug("EmptyDefinitionsGrammarAction");
    return 0;
}

ForEachFocusNode * FocusForEachGrammarAction(ParamsNode * paramsBlock) {
    LogDebug("FocusForEachGrammarAction: paramsBlock = %d", paramsBlock);
    return 0;
}

MethodChainNode * EmptyMethodChainGrammarAction() {
    LogDebug("EmptyMethodChainGrammarAction");
    return 0;
}

ParamsBlockNode * ParamsBlockGrammarAction(ParamsNode * params) {
    LogDebug("ParamsBlockGrammarAction: params = %d", params);
    return 0;
}

ValueNode * ParamStringGrammarAction(const char * sval) {
    LogDebug("ParamStringGrammarAction: sval = %d", sval);

    ValueNode * node = (ValueNode*) malloc(sizeof(ValueNode));
    node->type = STRING_VALUE;
    node->value.stringValue = sval;

    return 0;
}

 ValueNode * ParamIntegerGrammarAction(const int ival) {
    LogDebug("ParamIntegerGrammarAction: ival = %d", ival);
    ValueNode * node = (ValueNode*) malloc(sizeof(ValueNode));
    node->type = INT_VALUE;
    node->value.intValue = ival;
    return 0;
}

RenderNode * RenderAllGrammarAction() {

    LogDebug("RenderAllGrammarAction");
    RenderNode * node = (RenderNode*) malloc(sizeof(RenderNode));
    node->type = RENDERALL__;

    return node;
}

EmptyParamsNode* EmptyParamsGrammarAction() {
    LogDebug("EmptyParamsGrammarAction");
    EmptyParamsNode* node = (EmptyParamsNode*) malloc(sizeof(EmptyParamsNode));
    node->isEmpty = 1;
    return node;
}

MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsNode* params) {
    LogDebug("MethodGrammarAction: optional = %d, methodIdentifier = %d, paramsBlock = %d");
    MethodNode* node = (MethodNode*) malloc(sizeof(MethodNode));
    node->identifier = identifier;
    node->params = params;
    return node;
}

CustomMethodIdentifierNode* CustomMethodIdentifierGrammarAction(char* name) {
    CustomMethodIdentifierNode* node = (CustomMethodIdentifierNode*) malloc(sizeof(CustomMethodIdentifierNode));
    // node->name = strdup(name); 
    return node;
}

ObjectIdentifierNode* ObjectIdentifierGrammarAction(char* name) {
    LogDebug("ObjectIdentifierGrammarAction: objectIdentifier = %d");
    ObjectIdentifierNode* node = (ObjectIdentifierNode*) malloc(sizeof(ObjectIdentifierNode));
    // node->name = strdup(name); 
    return node;
}

ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next) {
    LogDebug("ObjectContentGrammarAction: objectAssignment = %d, objectContent = %d");
    ObjectContentNode* node = (ObjectContentNode*) malloc(sizeof(ObjectContentNode));
    node->assignment = assignment;
    node->next = next;
    return node;
}

ObjectAssignmentNode* ObjectAssignmentGrammarAction(IdentifierNode* variable, ValueNode* value) {
    LogDebug("ObjectAssignmentGrammarAction: variableIdentifier = %d, value = %d");
    ObjectAssignmentNode* node = (ObjectAssignmentNode*) malloc(sizeof(ObjectAssignmentNode));
    node->variable = variable;
    node->value = value;
    return node;
}

ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, ValueNode* value) {
    LogDebug("ObjectElementGrammarAction: variableIdentifier = %d, objectElement = %d");
    ObjectElementNode* node = (ObjectElementNode*) malloc(sizeof(ObjectElementNode));
    node->identifier = identifier;
    node->value = value;
    return node;
}

InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content) {
    LogDebug("InlineObject: valueObject = %d");
    InlineObjectNode* node = (InlineObjectNode*) malloc(sizeof(InlineObjectNode));
    node->content = content;
    return node;
}

AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ExpressionNode* expression) {
    LogDebug("AssignmentGrammarAction: assignment = %d, assignments = %d", identifier, expression);
    AssignmentNode* assignment = malloc(sizeof(AssignmentNode));
    assignment->identifier = identifier;
    assignment->expression = expression;
    return assignment;
}

DefinitionNode* DefinitionGrammarAction(IdentifierNode * identifier, ParamsNode * params, MethodChainNode * methodChain) {
    LogDebug("DefinitionGrammarAction: variableIdentifier = %d, methodChain = %d", identifier, methodChain);
    DefinitionNode* definition = malloc(sizeof(DefinitionNode));
    definition->identifier = identifier;
    definition->params = params;
    definition->methodChain = methodChain;
    return definition;
}

FocusNode* FocusAddGrammarAction(ValueNode * val) {
    LogDebug("FocusAddGrammarAction: paramsBlock = %d", val);
    FocusNode* focus = malloc(sizeof(FocusNode));
    focus->var = val;
    return focus;
}

MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next) {
    LogDebug("MethodChainGrammarAction: method = %d, methodChain = %d", method, next);
    MethodChainNode* methodChain = malloc(sizeof(MethodChainNode));
    methodChain->method = method;
    methodChain->next = next;
    return methodChain;
}

RenderNode* RenderGrammarAction() {
    LogDebug("RenderGrammarAction");
    RenderNode* render = malloc(sizeof(RenderNode));
    return render;
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

IdentifierNode* VariableIdentifierGrammarAction(const char* name) {
    LogDebug("VariableIdentifierGrammarAction: variable = %d", name);
    IdentifierNode* node = (IdentifierNode*) malloc(sizeof(IdentifierNode));
    //node->name = strdup(name); 
    return node;
}

ValueNode* ValueIntegerGrammarAction(const int value) {
    LogDebug("ValueIntegerGrammarAction: ival = %d", value);
    ValueNode* node = (ValueNode*) malloc(sizeof(ValueNode));
    node->type = INT_VALUE;
    node->value.intValue = value;
    return node;
}

ValueNode* ValueStringGrammarAction(const char* value) {
    LogDebug("ValueStringGrammarAction: sval = %d", value);
    ValueNode* node = (ValueNode*) malloc(sizeof(ValueNode));
    node->type = STRING_VALUE;
    //node->value.stringValue = strdup(value); 
    return node;
}

MethodIdentifierNode* MethodIdentifierGrammarAction(const char* name) {
    LogDebug("MethodIdentifierGrammarAction: sval = %d", name);
    MethodIdentifierNode* node = (MethodIdentifierNode*) malloc(sizeof(MethodIdentifierNode));
    //node->name = strdup(name); 
    return node;
}

ParamNode* ParamGrammarAction(ValueNode* value) {
    LogDebug("ParamGrammarAction: param = %d", value);
    ParamNode* node = (ParamNode*) malloc(sizeof(ParamNode));
    node->value = value;
    return node;
}

ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params) {
    LogDebug("ParamsGrammarAction: param = %d, params = %d", param, params);
    ParamsNode* node = (ParamsNode*) malloc(sizeof(ParamsNode));
    node->param = param;
    node->next = params;
    return node;
}

OptionalNode* OptionalQuestionSignGrammarAction() {
    LogDebug("OptionalQuestionSignGrammarAction");
    OptionalNode* node = (OptionalNode*) malloc(sizeof(OptionalNode));
    node->isQuestionMarkPresent = 1;
    return node;
}

OptionalNode* EmptyOptionalGrammarAction() {
    LogDebug("EmptyOptionalGrammarAction");
    OptionalNode* node = (OptionalNode*) malloc(sizeof(OptionalNode));
    node->isQuestionMarkPresent = 0;
    return node;
}

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

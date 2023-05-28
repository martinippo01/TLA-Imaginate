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
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    // node->value->value.objectValue = inlineObject;
    return node;
}
 
ValueNode * ValueObjectGrammarAction(ObjectNode * object) {
    LogDebug("ValueObjectGrammarAction: valueObject = %d", object);
    ValueNode * node = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->type = OBJECT_VALUE;
    // node->value.objectValue = object;
    return node;
}

ObjectContentNode* EmptyObjectContentGrammarAction() {
    LogDebug("EmptyObjectContentGrammarAction");
    ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
    node->next = NULL;
    node->assignment = NULL;
    return node;
}

ParamNode * ParamObjectElementGrammarAction(ObjectElementNode * objectElement) {
  LogDebug("ParamObjectElementGrammarAction: objectElement = %d", objectElement);
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    // node->value->value.objectValue = objectElement->identifier;
    return node;
}

ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier) {
    LogDebug("ParamVariableGrammarAction: variableIdentifier = %d", variableIdentifier);
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    // node->value->value.objectValue = variableIdentifier;
    return node;
}

AssignmentsNode * EmptyAssignmentsGrammarAction() {
    LogDebug("EmptyAssignmentsGrammarAction");
    AssignmentsNode * node = (AssignmentsNode*) calloc_(1, sizeof(AssignmentsNode));
    node->assignment= NULL;
    node->next = NULL;
    return node;
}

DefinitionsNode * EmptyDefinitionsGrammarAction() {
    LogDebug("EmptyDefinitionsGrammarAction");
    DefinitionsNode * node = (DefinitionsNode*) calloc_(1, sizeof(DefinitionsNode));
    node->definition = NULL;
    node->next = NULL;
    return node;
}

ForEachFocusNode * FocusForEachGrammarAction(ParamsBlockNode * paramsBlock) {
    LogDebug("FocusForEachGrammarAction: paramsBlock = %d", paramsBlock);
    ForEachFocusNode * node = (ForEachFocusNode*) calloc_(1, sizeof(ForEachFocusNode));
    // node->var = &(paramsBlock->param->value);
    return node;
}

MethodChainNode * EmptyMethodChainGrammarAction() {
    LogDebug("EmptyMethodChainGrammarAction");
    MethodChainNode * node = (MethodChainNode*) calloc_(1, sizeof(MethodChainNode));
    node->method = NULL;
    node->next = NULL;
    return node;
}

ParamsBlockNode * ParamsBlockGrammarAction(ParamsNode * params) {
    LogDebug("ParamsBlockGrammarAction: params = %d", params);
    ParamsBlockNode * node = (ParamsBlockNode*) calloc_(1, sizeof(ParamsBlockNode));
    node->params = params;
    return node;
}


ParamNode * ParamStringGrammarAction(int sval) {
    LogDebug("ParamStringGrammarAction: sval = %d", sval);
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    value->type = STRING_VALUE;
    // value->value.stringValue = sval;
    node->value = value;
    // node->value.stringValue = sval;
    return 0;
}

 ParamNode * ParamIntegerGrammarAction(const int ival) {
    LogDebug("ParamIntegerGrammarAction: ival = %d", ival);
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    value->type = INT_VALUE;
    value->value.intValue = ival;
    node->value = value;
    // node->value.intValue = ival;
    return 0;
}

RenderNode * RenderAllGrammarAction() {

    LogDebug("RenderAllGrammarAction");
    RenderNode * node = (RenderNode*) calloc_(1, sizeof(RenderNode));
    node->type = RENDERALL__;

    return node;
}

ParamsNode * EmptyParamsGrammarAction() {
    LogDebug("ParamsGrammarAction");
    ParamsNode* node = (ParamsNode*) calloc(sizeof(ParamsNode), 1);
    return node;
}


MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsBlockNode * params) {
    LogDebug("MethodGrammarAction: optional = %d, methodIdentifier = %d, paramsBlock = %d");
    MethodNode* node = (MethodNode*) calloc_(1, sizeof(MethodNode));
    node->identifier = identifier;
    node->params = params;
    return node;
}


MethodIdentifierNode * CustomMethodIdentifierGrammarAction(int name) {
    MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
    // node->name = strdup(name); 
    return node;
}

ObjectNode* ObjectNodeGrammarAction(ObjectContentNode * content) {
    LogDebug(" ObjectNodeGrammarAction: objectIdentifier = %d");
    ObjectNode* node = (ObjectNode*) calloc_(1, sizeof(ObjectNode));
    // node->name = strdup(name); 
    return node;
}

ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next) {
    LogDebug("ObjectContentGrammarAction: objectAssignment = %d, objectContent = %d");
    ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
    node->assignment = assignment;
    node->next = next;
    return node;
}


ObjectAssignmentNode* ObjectAssignmentIdentifierGrammarAction(IdentifierNode* variable, IdentifierNode * identifier) {
    LogDebug("ObjectAssignmentIdentifierGrammarAction: variableIdentifier = %d, value = %d");
    ObjectAssignmentNode* node = (ObjectAssignmentNode*) calloc_(1, sizeof(ObjectAssignmentNode));
    node->variable = variable;
    node->rightHandIdentifier = identifier;
    node->rightHandValue = NULL;
    return node;
}


ObjectAssignmentNode* ObjectAssignmentValueGrammarAction(IdentifierNode* variable, ValueNode * value) {
    LogDebug("ObjectAssignmentValueGrammarAction: variableIdentifier = %d, value = %d");
    ObjectAssignmentNode* node = (ObjectAssignmentNode*) calloc_(1, sizeof(ObjectAssignmentNode));
    node->variable = variable;
    node->rightHandValue = value;
    node->rightHandIdentifier = NULL;
    return node;
}

ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, IdentifierNode * value) {
    LogDebug("ObjectElementGrammarAction: variableIdentifier = %d, objectElement = %d");
    ObjectElementNode* node = (ObjectElementNode*) calloc_(1, sizeof(ObjectElementNode));
    node->identifier = identifier;
    node->value = value;
    return node;
}

InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content) {
    LogDebug("InlineObject: valueObject = %d");
    InlineObjectNode* node = (InlineObjectNode*) calloc_(1, sizeof(InlineObjectNode));
    node->content = content;
    return node;
}

AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ValueNode * expression) {
    LogDebug("AssignmentGrammarAction: assignment = %d, assignments = %d", identifier, expression);
    AssignmentNode* assignment = calloc_(1, sizeof(AssignmentNode));
    assignment->identifier = identifier;
    assignment->expression = expression;
    return assignment;
}

DefinitionNode* DefinitionGrammarAction(int identifier, ParamsBlockNode * params, MethodChainNode * methodChain) {
    LogDebug("DefinitionGrammarAction: variableIdentifier = %d, methodChain = %d", identifier, methodChain);
    DefinitionNode* definition = calloc_(1, sizeof(DefinitionNode));
    // definition->identifier = identifier;
    definition->params = params;
    definition->methodChain = methodChain;
    return definition;
}

FocusNode* FocusAddGrammarAction(ParamsBlockNode * val) {
    LogDebug("FocusAddGrammarAction: paramsBlock = %d", val);
    FocusNode* focus = calloc_(1, sizeof(FocusNode));
    // focus->var = val;
    return focus;
}

MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next) {
    LogDebug("MethodChainGrammarAction: method = %d, methodChain = %d", method, next);
    MethodChainNode* methodChain = calloc_(1, sizeof(MethodChainNode));
    methodChain->method = method;
    methodChain->next = next;
    return methodChain;
}

RenderNode* RenderGrammarAction() {
    LogDebug("RenderGrammarAction");
    RenderNode* render = calloc_(1, sizeof(RenderNode));
    return render;
}

AssignmentsNode* AssignmentsGrammarAction(AssignmentNode* assignment, AssignmentsNode* next) {
    LogDebug("AssignmentsGrammarAction: assignment = %d, assignments = %d", assignment, next);
    AssignmentsNode* assignments = calloc_(1, sizeof(AssignmentsNode));
    assignments->assignment = assignment;
    assignments->next = next;
    return assignments;
}

DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next) {
    LogDebug("DefinitionsGrammarAction: definition = %d, definitions = %d", definition, next);
    DefinitionsNode* definitions = calloc_(1, sizeof(DefinitionsNode));
    definitions->definition = definition;
    definitions->next = next;
    return definitions;
}


ImaginateNode* ImaginateGrammarActionForEachFocus(ForEachFocusNode* focuses, MethodChainNode* methodChain, RenderNode* render) {
    LogDebug("ImaginateGrammarAction: focus = %d, methodChain = %d, render = %d");
    ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
    // imaginate->focus = focuses;
    imaginate->methodChain = methodChain;
    imaginate->render = render;
    return imaginate;
}

ImaginateNode* ImaginateGrammarActionFocus(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render) {
    LogDebug("ImaginateGrammarAction: focus = %d, methodChain = %d, render = %d", focus, methodChain, render);
    ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
    imaginate->focus = focus;
    imaginate->methodChain = methodChain;
    imaginate->render = render;
    return imaginate;
}

IdentifierNode* VariableIdentifierGrammarAction(int name) {
    LogDebug("VariableIdentifierGrammarAction: variable = %d", name);
    IdentifierNode* node = (IdentifierNode*) calloc_(1, sizeof(IdentifierNode));
    //node->name = strdup(name); 
    return node;
}

ValueNode* ValueIntegerGrammarAction(const int value) {
    LogDebug("ValueIntegerGrammarAction: ival = %d", value);
    ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->type = INT_VALUE;
    node->value.intValue = value;
    return node;
}

ValueNode* ValueStringGrammarAction(const int value) {
    LogDebug("ValueStringGrammarAction: sval = %d", value);
    ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->type = STRING_VALUE;
    //node->value.stringValue = strdup(value); 
    return node;
}

MethodIdentifierNode* MethodIdentifierGrammarAction(const int name) {
    LogDebug("MethodIdentifierGrammarAction: sval = %d", name);
    MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
    //node->name = strdup(name); 
    return node;
}

ParamsNode* ParamGrammarAction(ParamNode * param) {
    LogDebug("ParamGrammarAction: param = %d");
    ParamsNode* node = (ParamsNode*) calloc_(1, sizeof(ParamsNode));
    node->param = param;
    node->next = NULL;
    return node;
}

ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params) {
    LogDebug("ParamsGrammarAction: param = %d, params = %d", param, params);
    ParamsNode* node = (ParamsNode*) calloc_(1, sizeof(ParamsNode));
    node->param = param;
    node->next = params;
    return node;
}

OptionalNode* OptionalQuestionSignGrammarAction() {
    LogDebug("OptionalQuestionSignGrammarAction");
    OptionalNode* node = (OptionalNode*) calloc_(1, sizeof(OptionalNode));
    node->isQuestionMarkPresent = 1;
    return node;
}

OptionalNode* EmptyOptionalGrammarAction() {
    LogDebug("EmptyOptionalGrammarAction");
    OptionalNode* node = (OptionalNode*) calloc_(1, sizeof(OptionalNode));
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

    ProgramNode* program = calloc_(1, sizeof(ProgramNode));
    program->assignments = assignments;
    program->definitions = definitions;
    program->imaginate = imaginate;
    return program;
}

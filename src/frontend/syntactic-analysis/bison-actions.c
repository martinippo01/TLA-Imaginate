#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "../../backend/semantic-analysis/adapters.h"
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
    LogDebug("ParamInlineObjectGrammarAction: valueObject = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    //hay que agregarlo a la tabla de simbolos y ahi darle un IdentifierNode
    // node->value->value.objectValue = inlineObject;
    return node;
}
 
ValueNode * ValueObjectGrammarAction(ObjectNode * object) {
    LogDebug("ValueObjectGrammarAction: valueObject = %d");
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
  LogDebug("ParamObjectElementGrammarAction: objectElement = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    // node->value->value.objectValue = objectElement->identifier;
    return node;
}

ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier) {
    LogDebug("ParamVariableGrammarAction: variableIdentifier = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;
    node->value->value.objectValue = variableIdentifier;
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
    LogDebug("FocusForEachGrammarAction: paramsBlock = %d");
    ForEachFocusNode * node = (ForEachFocusNode*) calloc_(1, sizeof(ForEachFocusNode));
    node->var = paramsBlockToValuesBlock(paramsBlock);
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
    LogDebug("ParamsBlockGrammarAction: params = %d");
    ParamsBlockNode * node = (ParamsBlockNode*) calloc_(1, sizeof(ParamsBlockNode));
    node->params = params;
    return node;
}


ParamNode * ParamStringGrammarAction(const char * sval) {
    LogDebug("ParamStringGrammarAction: sval = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    value->type = STRING_VALUE;
    value->value.stringValue = calloc_(strlen(sval) + 1, sizeof(char));
    strcpy(value->value.stringValue, sval);
    node->value = value;
    return 0;
}

 ParamNode * ParamIntegerGrammarAction(const int ival) {
    LogDebug("ParamIntegerGrammarAction: ival = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    value->type = INT_VALUE;
    value->value.intValue = ival;
    node->value = value;
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


MethodIdentifierNode * CustomMethodIdentifierGrammarAction(const char * name) {
    MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
    node->name = calloc_(strlen(name) + 1, sizeof(char));
    strcpy(node->name, name);
    return node;
}

ObjectNode* ObjectNodeGrammarAction(ObjectContentNode * content) {
    LogDebug(" ObjectNodeGrammarAction: objectIdentifier = %d");
    ObjectNode* node = (ObjectNode*) calloc_(1, sizeof(ObjectNode));
    // aca tambien falta lo de tabla de simbolos
    // node->node = content; 
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
    LogDebug("AssignmentGrammarAction: assignment = %d, assignments = %d");
    AssignmentNode* assignment = calloc_(1, sizeof(AssignmentNode));
    assignment->identifier = identifier;
    assignment->expression = expression;
    return assignment;
}

DefinitionNode* DefinitionGrammarAction(const char * identifierStr, ParamsBlockNode * params, MethodChainNode * methodChain) {
    LogDebug("DefinitionGrammarAction: variableIdentifier = %d, methodChain = %d");

    IdentifierNode * identifier = calloc_(1, sizeof(IdentifierNode));
    identifier->name = strdup_(identifierStr);
    
    DefinitionNode* definition = calloc_(1, sizeof(DefinitionNode));
    definition->identifier = identifier;
    definition->params = params;
    definition->methodChain = methodChain;
    return definition;
}

FocusNode* FocusAddGrammarAction(ParamsBlockNode * val) {
    LogDebug("FocusAddGrammarAction: paramsBlock = %d");
    FocusNode* focus = calloc_(1, sizeof(FocusNode));
    // focus->var = val->params[0].param->value;
    return focus;
}

MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next) {
    LogDebug("MethodChainGrammarAction: method = %d, methodChain = %d");
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
    LogDebug("AssignmentsGrammarAction: assignment = %d, assignments = %d");
    AssignmentsNode* assignments = calloc_(1, sizeof(AssignmentsNode));
    assignments->assignment = assignment;
    assignments->next = next;
    return assignments;
}

DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next) {
    LogDebug("DefinitionsGrammarAction: definition = %d, definitions = %d");
    DefinitionsNode* definitions = calloc_(1, sizeof(DefinitionsNode));
    definitions->definition = definition;
    definitions->next = next;
    return definitions;
}


ImaginateNode* ImaginateGrammarActionForEachFocus(ForEachFocusNode* focuses, MethodChainNode* methodChain, RenderNode* render) {
    LogDebug("ImaginateGrammarAction: focus = %d, methodChain = %d, render = %d");
    ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
    imaginate->focuses = focuses;
    imaginate->methodChain = methodChain;
    imaginate->render = render;
    return imaginate;
}

ImaginateNode* ImaginateGrammarActionFocus(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render) {
    LogDebug("ImaginateGrammarAction: focus = %d, methodChain = %d, render = %d");
    ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
    imaginate->focus = focus;
    imaginate->focuses = NULL;
    imaginate->methodChain = methodChain;
    imaginate->render = render;
    return imaginate;
}

IdentifierNode* VariableIdentifierGrammarAction(const char *  name) {
    LogDebug("VariableIdentifierGrammarAction: variable = %d");
    IdentifierNode* node = (IdentifierNode*) calloc_(1, sizeof(IdentifierNode));
    node->name = strdup_(name); 
    return node;
}

ValueNode* ValueIntegerGrammarAction(const int value) {
    LogDebug("ValueIntegerGrammarAction: ival = %d");
    ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->type = INT_VALUE;
    node->value.intValue = value;
    return node;
}

ValueNode* ValueStringGrammarAction(const char * value) {
    LogDebug("ValueStringGrammarAction: sval = %d");
    ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->type = STRING_VALUE;
    node->value.stringValue = strdup_(value);
    return node;
}

MethodIdentifierNode* MethodIdentifierGrammarAction(const int id) {
    LogDebug("MethodIdentifierGrammarAction: sval = %d");
    MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
    // node->name =  id;
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
    LogDebug("ParamsGrammarAction: param = %d, params = %d");
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

ProgramNode* ProgramGrammarAction(AssignmentsNode* assignments, DefinitionsNode* definitions, ImaginateNode* imaginate) {

	LogDebug("\tProgramGrammarAction(%d, %d, %d)");
	state.succeed = true;
  ProgramNode* program = calloc_(1, sizeof(ProgramNode));
  program->assignments = assignments;
  program->definitions = definitions;
  program->imaginate = imaginate;
  return program;
}

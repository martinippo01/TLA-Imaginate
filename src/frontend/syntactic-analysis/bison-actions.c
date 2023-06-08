#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "../../backend/symbols-table/values/hashmap_val.h"
#include "../../backend/semantic-analysis/adapters.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char* concatIntToStr(const char* str, int num) {
    char* newStr = malloc(strlen(str) + 50); 
    sprintf(newStr, "%s%d", str, num); 
    return newStr;
}


ArgumentsBlockNode * ArgumentsBlockGrammarAction(ArgumentsNode * arguments) {
    ArgumentsBlockNode *node = (ArgumentsBlockNode *)calloc_(1, sizeof(ArgumentsBlockNode));
    node->params = arguments;
    return node;
}

ArgumentsNode * ArgumentGrammarAction(ArgumentNode * argument) {
    ArgumentsNode *node = (ArgumentsNode *)calloc_(1, sizeof(ArgumentsNode));
    node->arg = argument;
    return node;
}

ArgumentsNode * ArgumentsGrammarAction(ArgumentNode * argument, ArgumentsNode * nextArgs) {
    ArgumentsNode *node = ArgumentGrammarAction(argument);
    node->next = nextArgs;
    return node;
}

ArgumentNode * ArgumentIdentifierGrammarAction(const char * name) {
    ArgumentNode *node = (ArgumentNode *)calloc_(1, sizeof(ArgumentNode));
    node->value = (ValueNode *)calloc_(1, sizeof(ValueNode));
    node->value->value.stringValue = strdup_(name);
    return node;
}

ArgumentsNode * EmptyArgumentsGrammarAction() {
    return (ArgumentsNode *)calloc_(1, sizeof(ArgumentsNode));
}
ParamNode * ParamInlineObjectGrammarAction(InlineObjectNode * inlineObject) {
    LogDebug("ParamInlineObjectGrammarAction: valueObject = %d");

    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    node->value->type = OBJECT_VALUE;

    // int id = state.next_inline_object_id++;
    // Value * value = calloc_(1, sizeof(Value));
    //
    // char * concatenated_str = concatIntToStr("inlineObject", id);
    // put(state.symbols_table, concatenated_str, *value); 

    //probably need to create a new symbols_table for inline objects!

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

    if(!exists(state.symbols_table, variableIdentifier->name)) {
        printf("Error: Identifier %s is not defined.\n", variableIdentifier->name);
        exit(1);
    }

    // If exists, retrieve the value
    Value defaultVal;
    Value* val = getOrDefault(state.symbols_table, variableIdentifier->name, &defaultVal);
    ValueNode* valueNode = calloc_(1, sizeof(ValueNode));

    // Depending on the type of the value, set the correct type and value in the ValueNode
    if(strcmp(val->type, "int") == 0) {
        valueNode->type = INT_VALUE;
        valueNode->value.intValue = atoi(val->initialization);
    } else if(strcmp(val->type, "string") == 0) {
        valueNode->type = STRING_VALUE;
        valueNode->value.stringValue = strdup(val->initialization);
    }

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
    node->var = paramsBlock;
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
    value->value.stringValue = strdup_(sval);
    node->value = value;
    return node;
}

 ParamNode * ParamIntegerGrammarAction(const int ival) {
    LogDebug("ParamIntegerGrammarAction: ival = %d");
    ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
    ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
    value->type = INT_VALUE;
    value->value.intValue = ival;
    node->value = value;
    return node;
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

		if (identifier->type == CUSTOM) {
			boolean isDefined = exists(state.symbols_table, identifier->value.name);
			//probably need to define another table for methods (so in the value we can
			//put the paramsBlock and check directly!)
		}

    MethodNode* node = (MethodNode*) calloc_(1, sizeof(MethodNode));
    node->optional = optional;
    node->identifier = identifier;
    node->params = params;
    return node;
}


MethodIdentifierNode * CustomMethodIdentifierGrammarAction(const char * name) {
    MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
    node->type = CUSTOM;
    node->value.name =  strdup_(name);
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

    Value* value = malloc(sizeof(Value));
    if(expression->type == INT_VALUE) {
        strcpy(value->type, "int");
        sprintf(value->initialization, "%d", expression->value.intValue);
    } else if(expression->type == STRING_VALUE) {
        strcpy(value->type, "string");
        strcpy(value->initialization, expression->value.stringValue);
    }

    int put_status = put(state.symbols_table, identifier->name, *value);

    if(put_status == 0) {
        printf("Error: Couldn't store the value in the symbol table.\n");
    }

    // Create AssignmentNode after storing the value to symbol table
    AssignmentNode* assignmentNode = malloc(sizeof(AssignmentNode));
    assignmentNode->identifier = identifier;
    assignmentNode->expression = expression;
    return assignmentNode;
}

DefinitionNode* DefinitionGrammarAction(const char * identifierStr, ArgumentsBlockNode * args, MethodChainNode * methodChain) {
    LogDebug("DefinitionGrammarAction: variableIdentifier = %d, methodChain = %d");

    IdentifierNode * identifier = calloc_(1, sizeof(IdentifierNode));
    identifier->name = strdup_(identifierStr);
    
    DefinitionNode* definition = calloc_(1, sizeof(DefinitionNode));
    definition->identifier = identifier;
    definition->args = args;
    definition->methodChain = methodChain;
    return definition;
}

FocusNode* FocusAddGrammarAction(ParamsBlockNode * val) {
    LogDebug("FocusAddGrammarAction: paramsBlock = %d");
    FocusNode * focus = calloc_(1, sizeof(FocusNode));
    focus->var = val;
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
    node->type = OWN;
    node->value.id = id;
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
    state.program = program;
    program->assignments = assignments;
    program->definitions = definitions;
    program->imaginate = imaginate;
    return program;
}

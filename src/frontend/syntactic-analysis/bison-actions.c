#include "../../backend/domain-specific/def-execution.h"
#include "../../backend/support/logger.h"
#include "../../backend/symbols-table/values/hashmap_val.h"
#include "../../backend/semantic-analysis/adapters.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


char* strcatint_(const char* str, int num) {
    int str_len = strlen(str);
    int num_len = snprintf(NULL, 0, "%d", num);

    // allocate memory for the new string
    char* result = calloc_(str_len + num_len + 1, sizeof(char)); 

    // copy str into result
    strcpy(result, str);

    // append num to result
    sprintf(result + str_len, "%d", num);

    return result;
}

char * strcat_(const char* str1, const char* str2) {
 // calculate lengths of both strings
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);

    // allocate memory for the new string
    // +2 for the null-terminator and the period
    char* result = calloc(str1_len + str2_len + 2, sizeof(char)); 

    // check if memory allocation was successful
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // copy str1 into result
    strcpy(result, str1);

    // add a period after str1
    result[str1_len] = '.';

    // append str2 to result
    strcpy(result + str1_len + 1, str2);
    return result;
}
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

ObjectContentNode *  ObjectAssignmentGrammarAction(ObjectAssignmentNode * assignment) {
  ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
  node->assignment = assignment;
  node->next = NULL;
  return node;
}

ObjectContentNode *  ObjectAssignmentsGrammarAction(ObjectAssignmentNode * assignment, ObjectContentNode * next) {
  ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
  node->assignment = assignment;
  node->next = next;
  return node;
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

  ValueNode * value = (ValueNode *) calloc_(1, sizeof(ValueNode));
  value->value.stringValue = strdup_(name);
  value->type = STRING_VALUE;

  ArgumentNode *node = (ArgumentNode *)calloc_(1, sizeof(ArgumentNode));
  node->value = value;

  Value * valueEntry = (Value *) calloc_(1, sizeof(Value));

  if(exists(state.symbols_table, value->value.stringValue)) {
		AppendError(&state.errors, "Not allowed method definition as defined parameters collide with global variables");
	}

  put(state.symbols_table, value->value.stringValue, *valueEntry);
  return node;
}

ArgumentsNode * EmptyArgumentsGrammarAction() {
  return (ArgumentsNode *)calloc_(1, sizeof(ArgumentsNode));
}

ParamNode * ParamInlineObjectGrammarAction(InlineObjectNode * inlineObject) {
  LogDebug("ParamInlineObjectGrammarAction: valueObject = ");

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


Value * initialiseValueSymbolsTable(ValueNode * assignment) {
		Value * val = calloc_(1, sizeof(Value));
		//should check whether string or int as value
		if(assignment->type == INT_VALUE) {
	   val->initialization = strdup_(assignment->value.stringValue);
	   val->type_enum = INT_VALUE;
	   strcpy(val->type, "int");
		} else if (assignment->type == STRING_VALUE) {
	   val->initialization = strdup_(assignment->value.stringValue);
	   val->type_enum = STRING_VALUE;
	   strcpy(val->type, "string");
	  }
	  return val;
}

AssignmentNode * ValueObjectGrammarAction(IdentifierNode * identifier, ObjectNode * object) {
  LogDebug("ValueObjectGrammarAction: valueObject = ");

  ValueNode * node = (ValueNode*) calloc_(1, sizeof(ValueNode));
  node->type = OBJECT_VALUE;
  node->value.objectValue = object->identifier;


	//insert the object in itself
  char * key = identifier->name;
  Value * val = calloc_(1, sizeof(Value));
  put(state.symbols_table, key, *val);

	//insert the body of the object
  ObjectContentNode * assignments = object->content;
  while(assignments != NULL && assignments->assignment != NULL) {
  	char * key = strcat_(identifier->name, assignments->assignment->variable->name); 
	put(state.symbols_table, key, *initialiseValueSymbolsTable(assignments->assignment->rightHandValue));
	printHashMap(state.symbols_table);
	assignments = assignments->next;
  }


  AssignmentNode* assignmentNode = malloc(sizeof(AssignmentNode));
  assignmentNode->identifier = identifier;
  assignmentNode->expression = node;
  return assignmentNode;
}

ObjectContentNode* EmptyObjectContentGrammarAction() {
  LogDebug("EmptyObjectContentGrammarAction");
  ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
  node->next = NULL;
  node->assignment = NULL;
  return node;
}

ParamNode * ParamObjectElementGrammarAction(ObjectElementNode * objectElement) {
  LogDebug("ParamObjectElementGrammarAction: objectElement = ");
  ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
  node->value = (ValueNode*) calloc_(1, sizeof(ValueNode));
  node->value->type = OBJECT_VALUE;
  node->value->value.objectValue = objectElement->identifier;
  return node;
}
ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier) {

  LogDebug("ParamVariableGrammarAction: variableIdentifier = ");

  if(!exists(state.symbols_table, variableIdentifier->name))
    AppendError(&state.errors, "Identifier %s is not defined.\n", variableIdentifier->name);

  // If exists, retrieve the value and update it's values.
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
  LogDebug("FocusForEachGrammarAction: paramsBlock = ");
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
  LogDebug("ParamsBlockGrammarAction: params = ");
  ParamsBlockNode * node = (ParamsBlockNode*) calloc_(1, sizeof(ParamsBlockNode));
  node->params = params;
  return node;
}


ParamNode * ParamStringGrammarAction(const char * sval) {
  LogDebug("ParamStringGrammarAction: sval = ");
  ParamNode * node = (ParamNode*) calloc_(1, sizeof(ParamNode));
  ValueNode * value = (ValueNode*) calloc_(1, sizeof(ValueNode));
  value->type = STRING_VALUE;
  value->value.stringValue = strdup_(sval);
  node->value = value;
  return node;
}

ParamNode * ParamIntegerGrammarAction(const int ival) {
  LogDebug("ParamIntegerGrammarAction: ival = ");
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

// METHODS

MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsBlockNode * params) {
  LogDebug("MethodGrammarAction: optional = , methodIdentifier = , paramsBlock = ");

	if (identifier->type == CUSTOM_METHOD && !existsDefsTable(state.defs_table, identifier->value.name))
		AppendError(&state.errors, "Method def %s already defined in the table", identifier->value.name);

	if(identifier-> type == CUSTOM_METHOD && !validateDefinitionSignature(state.defs_table, identifier->value.name, params))
		 AppendError(&state.errors, "Method def %s does not match the arguments passed", identifier->value.name);

  MethodNode* node = (MethodNode*) calloc_(1, sizeof(MethodNode));
  node->optional = optional;
  node->identifier = identifier;
  node->params = params;

  if(identifier->type == CUSTOM_METHOD) {
    node->definition = getOrDefaultDefsTable(state.defs_table, identifier->value.name, &DEFAULT_VALUE_NODE)->definition;
  } else {
    node->definition = NULL;
  }

  return node;
}


MethodIdentifierNode * CustomMethodIdentifierGrammarAction(const char * name) {
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = CUSTOM_METHOD;
  node->value.name =  strdup_(name);
  return node;
}

// ___________________________________________

ObjectNode* ObjectNodeGrammarAction(ObjectContentNode * content) {
  LogDebug(" ObjectNodeGrammarAction: objectIdentifier = ");
  ObjectNode* node = (ObjectNode*) calloc_(1, sizeof(ObjectNode));
  node->content = content; 
  return node;
}

ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next) {
  LogDebug("ObjectContentGrammarAction: objectAssignment = , objectContent = ");
  ObjectContentNode* node = (ObjectContentNode*) calloc_(1, sizeof(ObjectContentNode));
  node->assignment = assignment;
  node->next = next;
  return node;
}


ObjectAssignmentNode* ObjectAssignmentIdentifierGrammarAction(IdentifierNode* variable, IdentifierNode * identifier) {
  LogDebug("ObjectAssignmentIdentifierGrammarAction: variableIdentifier = , value = ");
  ObjectAssignmentNode* node = (ObjectAssignmentNode*) calloc_(1, sizeof(ObjectAssignmentNode));
  node->variable = variable;
  node->rightHandIdentifier = identifier;
  node->rightHandValue = NULL;
  return node;
}


ObjectAssignmentNode* ObjectAssignmentValueGrammarAction(IdentifierNode* variable, ValueNode * value) {
  LogDebug("ObjectAssignmentValueGrammarAction: variableIdentifier = %s", variable->name);
  ObjectAssignmentNode* node = (ObjectAssignmentNode*) calloc_(1, sizeof(ObjectAssignmentNode));
  node->variable = variable;
  node->rightHandValue = value;
  node->rightHandIdentifier = NULL;
  return node;
}

ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, IdentifierNode * value) {
  LogDebug("ObjectElementGrammarAction: variableIdentifier = , objectElement = ");
  ObjectElementNode* node = (ObjectElementNode*) calloc_(1, sizeof(ObjectElementNode));
  node->identifier = identifier;
  node->value = value;
  return node;
}

InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content) {
  LogDebug("InlineObject: valueObject = ");
  InlineObjectNode* node = (InlineObjectNode*) calloc_(1, sizeof(InlineObjectNode));
  node->content = content;
  return node;
}

AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ValueNode * expression) {

  LogDebug("AssignmentGrammarAction: assignment = , assignments = ");

  Value* value = malloc(sizeof(Value));
  if(expression->type == INT_VALUE) {
    strcpy(value->type, "int");
    value->initialization = strcatint_("", expression->value.intValue);
  } else if(expression->type == STRING_VALUE) {
    strcpy(value->type, "string");
    value->initialization = strdup_(expression->value.stringValue);
  }

  int put_status = put(state.symbols_table, identifier->name, *value);

  if(put_status == 0)
    AppendError(&state.errors, "Couldn't store the value in the symbol table %s", identifier->name);


  // Create AssignmentNode after storing the value to symbol table
  AssignmentNode* assignmentNode = malloc(sizeof(AssignmentNode));
  assignmentNode->identifier = identifier;
  assignmentNode->expression = expression;
  return assignmentNode;
}

DefinitionNode* DefinitionGrammarAction(const char * identifierStr, ArgumentsBlockNode * args, MethodChainNode * methodChain) {
  LogDebug("DefinitionGrammarAction: variableIdentifier = , methodChain = ");

	if(existsDefsTable(state.defs_table, identifierStr))
		 AppendError(&state.errors, "Already defined the token %s", identifierStr);


  IdentifierNode * identifier = calloc_(1, sizeof(IdentifierNode));
  identifier->name = strdup_(identifierStr);


  DefinitionNode* definition = calloc_(1, sizeof(DefinitionNode));
  definition->identifier = identifier;
  definition->args = args;
  definition->methodChain = methodChain;


  ValueDef * defsEntry = calloc_(1, sizeof(ValueDef));
  defsEntry->name = strdup_(identifierStr);
  defsEntry->definition = definition;

	putDefsTable(state.defs_table, strdup_(identifier->name), *defsEntry);
  return definition;
}

FocusNode* FocusAddGrammarAction(ParamsBlockNode * val) {
  LogDebug("FocusAddGrammarAction: paramsBlock = %d");
  FocusNode * focus = calloc_(1, sizeof(FocusNode));
  focus->var = val;
  return focus;
}

MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next) {
  LogDebug("MethodChainGrammarAction: method = , methodChain = ");
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
  LogDebug("AssignmentsGrammarAction: assignment = , assignments = ");
  AssignmentsNode* assignments = calloc_(1, sizeof(AssignmentsNode));
  assignments->assignment = assignment;
  assignments->next = next;
  return assignments;
}

DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next) {
  LogDebug("DefinitionsGrammarAction: definition = , definitions = ");
  DefinitionsNode* definitions = calloc_(1, sizeof(DefinitionsNode));
  definitions->definition = definition;
  definitions->next = next;
  return definitions;
}


ImaginateNode* ImaginateGrammarActionForEachFocus(ForEachFocusNode* focuses, MethodChainNode* methodChain, RenderNode* render) {
  LogDebug("ImaginateGrammarAction: focus = , methodChain = , render = ");
  ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
  imaginate->focuses = focuses;
  imaginate->methodChain = methodChain;
  imaginate->render = render;
  return imaginate;
}

ImaginateNode* ImaginateGrammarActionFocus(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render) {
  LogDebug("ImaginateGrammarAction: focus = , methodChain = , render = ");
  ImaginateNode* imaginate = calloc_(1, sizeof(ImaginateNode));
  imaginate->focus = focus;
  imaginate->focuses = NULL;
  imaginate->methodChain = methodChain;
  imaginate->render = render;
  return imaginate;
}

IdentifierNode* VariableIdentifierGrammarAction(const char *  name) {
  LogDebug("VariableIdentifierGrammarAction: variable = ");

  IdentifierNode* node = (IdentifierNode*) calloc_(1, sizeof(IdentifierNode));
  node->name = strdup_(name); 

  return node;
}

ValueNode* ValueIntegerGrammarAction(const int value) {
  LogDebug("ValueIntegerGrammarAction: ival = ");
  ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
  node->type = INT_VALUE;
  node->value.intValue = value;
  return node;
}

ValueNode* ValueStringGrammarAction(const char * value) {
  LogDebug("ValueStringGrammarAction: sval = ");
  ValueNode* node = (ValueNode*) calloc_(1, sizeof(ValueNode));
  node->type = STRING_VALUE;
  node->value.stringValue = strdup_(value);
  return node;
}

// BUILT IN METHODS


MethodIdentifierNode* AddBlackAndWhiteIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = ADDBLACKANDWHITE_METHOD;
  node->value.id = id;
  return node;
}

MethodIdentifierNode* AddContrastMethodIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = ADDCONTRAST_METHOD;
  node->value.id = id;
  return node;
}

MethodIdentifierNode* AddGrayScaleMethodIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = ADDGRAYSCALE_METHOD;
  node->value.id = id;
  return node;
}

MethodIdentifierNode* AddBackgroundMethodIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = ADDBACKGROUND_METHOD;
  node->value.id = id;
  return node;
}

MethodIdentifierNode* AddFlavourMethodIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = ADDFLAVOUR_METHOD;
  node->value.id = id;
  return node;
}

MethodIdentifierNode* PickFlavourMethodIdentifierGrammarAction(const int id) {
  LogDebug("MethodIdentifierGrammarAction: sval = ");
  MethodIdentifierNode* node = (MethodIdentifierNode*) calloc_(1, sizeof(MethodIdentifierNode));
  node->type = PICKFLAVOUR_METHOD;
  node->value.id = id;
  return node;
}

//__________________________________________

ParamsNode* ParamGrammarAction(ParamNode * param) {
  LogDebug("ParamGrammarAction: param = ");
  ParamsNode* node = (ParamsNode*) calloc_(1, sizeof(ParamsNode));
  node->param = param;
  node->next = NULL;
  return node;
}

ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params) {
  LogDebug("ParamsGrammarAction: param = , params = ");
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

	LogDebug("\tProgramGrammarAction(, , )");
	state.succeed = isEmpty(&state.errors);
  ProgramNode* program = calloc_(1, sizeof(ProgramNode));
  state.program = program;
  program->assignments = assignments;
  program->definitions = definitions;
  program->imaginate = imaginate;
  return program;
}

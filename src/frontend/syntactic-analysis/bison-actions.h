#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

ProgramNode* ProgramGrammarAction(AssignmentsNode* assignments, DefinitionsNode* definitions, ImaginateNode* imaginate);
AssignmentsNode* AssignmentsGrammarAction(AssignmentNode* assignment, AssignmentsNode* next);
DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next);
ImaginateNode* ImaginateGrammarAction(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render);

AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ExpressionNode* expression);

DefinitionNode* DefinitionGrammarAction(IdentifierNode * identifier, ParamsBlockNode * params, MethodChainNode * methodChain);
FocusNode* FocusAddGrammarAction(ValueNode* var);
MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next);
RenderNode* RenderGrammarAction();

IdentifierNode* VariableIdentifierGrammarAction(const char* name);
ValueNode* ValueIntegerGrammarAction(const int value);
ValueNode* ValueStringGrammarAction(const char* value);
MethodIdentifierNode* MethodIdentifierGrammarAction(const char* name);
ParamNode* ParamGrammarAction(ValueNode* value);
ParamsBlockNode* ParamsGrammarAction(ParamNode* param, ParamsBlockNode* params);
OptionalNode* OptionalQuestionSignGrammarAction();
OptionalNode* EmptyOptionalGrammarAction();

EmptyParamsNode* EmptyParamsGrammarAction();
MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsBlockNode* params);
CustomMethodIdentifierNode* CustomMethodIdentifierGrammarAction(char* name);
ObjectIdentifierNode* ObjectIdentifierGrammarAction(char* name);
ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next);
ObjectAssignmentNode* ObjectAssignmentGrammarAction(IdentifierNode* variable, ValueNode* value);
ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, ValueNode* value);
InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content);
RenderNode * RenderAllGrammarAction();
ParamNode * ParamStringGrammarAction(const int sval);
ParamNode * ParamIntegerGrammarAction(const char * ival);

// TODO convert them to nodes in AST.
int ValueObjectGrammarAction(const int valueObject);
int ParamObjectGrammarAction(const int paramObject);
int EmptyObjectContentGrammarAction();
int ParamVariableGrammarAction(const int variableIdentifier);
int ParamObjectElementGrammarAction(const int objectElement);
int ParamInlineObjectGrammarAction(const int inlineObject);
int EmptyAssignmentsGrammarAction();
int EmptyDefinitionsGrammarAction();
int FocusForEachGrammarAction(const int paramsBlock);
int EmptyMethodChainGrammarAction();
int ParamsBlockGrammarAction(const int params);

int VariableAssignmentGrammarAction(const int variable_name, const int variable_value);


#endif

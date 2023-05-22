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

DefinitionNode* DefinitionGrammarAction(IdentifierNode * identifier, ParamsNode* params, MethodChainNode * methodChain);
FocusNode* FocusAddGrammarAction(ValueNode* var);
MethodChainNode* MethodChainGrammarAction(MethodNode* method, MethodChainNode* next);
RenderNode* RenderGrammarAction();

// TODO convert them to nodes in AST.
int ValueObjectGrammarAction(const int valueObject);
int ParamObjectGrammarAction(const int paramObject);
int ObjectIdentifierGrammarAction(const int objectIdentifier);
int ObjectContentGrammarAction(const int objectAssignment, const int objectContent);
int EmptyObjectContentGrammarAction();
int ObjectAssignmentGrammarAction(const int  variableIdentifier, const int value);
int ParamVariableGrammarAction(const int variableIdentifier);
int ParamObjectElementGrammarAction(const int objectElement);
int ObjectElementGrammarAction(const int variableIdentifier, const int objectElement);
int ObjectAssignmentGrammarAction(const int variableIdentifier, const int value);
int InlineObjectGrammarAction(const int objectIdentifier);
int ParamInlineObjectGrammarAction(const int inlineObject);
int EmptyAssignmentsGrammarAction();
int ValueIntegerGrammarAction(const int ival);
int ValueStringGrammarAction(const int sval);
int EmptyDefinitionsGrammarAction();
int EmptyParamsGrammarAction();
int FocusForEachGrammarAction(const int paramsBlock);
int EmptyMethodChainGrammarAction();
int MethodGrammarAction(const int optional, const int methodIdentifier, const int paramsBlock);
int ParamsBlockGrammarAction(const int params);
int OptionalQuestionSignGrammarAction();
int EmptyOptionalGrammarAction();
int ParamsGrammarAction(const int param, const int params);
int ParamGrammarAction(const int param);
int EmptyParamsGrammarAction();
int ParamStringGrammarAction(const int sval);
int ParamIntegerGrammarAction(const int ival);
int RenderAllGrammarAction();
int VariableIdentifierGrammarAction(const int sval);
int MethodIdentifierGrammarAction(const int sval);
int VariableAssignmentGrammarAction(const int variable_name, const int variable_value);


#endif

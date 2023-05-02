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

// Programa.
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

int ProgramGrammarAction(const int assignments, const int definitions, const int imaginate);
int AssignmentsGrammarAction(const int assignment, const int assignments);
int EmptyAssignmentsGrammarAction();
int AssignmentGrammarAction(const int variableIdentifier, const int value);
int ValueIntegerGrammarAction(const int ival);
int ValueStringGrammarAction(const int sval);
int DefinitionsGrammarAction(const int definition, const int definitions);
int EmptyDefinitionsGrammarAction();
int DefinitionGrammarAction(const int variableIdentifier, const int methodChain);
int EmptyParamsGrammarAction();
int ImaginateGrammarAction(const int focus, const int methodChain, const int render);
int FocusAddGrammarAction(const int paramsBlock);
int FocusForEachGrammarAction(const int paramsBlock);
int MethodChainGrammarAction(const int method, const int methodChain);
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
int RenderGrammarAction();
int RenderAllGrammarAction();
int VariableIdentifierGrammarAction(const int sval);
int MethodIdentifierGrammarAction(const int sval);

#endif

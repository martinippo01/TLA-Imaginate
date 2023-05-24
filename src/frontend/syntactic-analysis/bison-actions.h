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


/*
 * Aca se divide el compilador en las tres partes principales: 
 *   asignaciones (val abc : xyz)
 *   definiciones (def abc(xyz):)
 *   imaginate(Imaginate.focus().abc.render())
 * */
AssignmentsNode* AssignmentsGrammarAction(AssignmentNode* assignment, AssignmentsNode* next);
DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next);
ImaginateNode* ImaginateGrammarAction(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render);

/* Asignaciones */
AssignmentNode * EmptyAssignmentsGrammarAction();
AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ExpressionNode* expression);
IdentifierNode* VariableIdentifierGrammarAction(const char* name);
ValueNode* ValueIntegerGrammarAction(const int value);
ValueNode* ValueStringGrammarAction(const char* value);
ValueNode * ValueObjectGrammarAction(ObjectIdentifierNode * objectIdentifier);

/* Definciones */
DefinitionNode * EmptyDefinitionsGrammarAction();
DefinitionNode * DefinitionGrammarAction(IdentifierNode * identifier, ParamsNode * params, MethodChainNode * methodChain);

MethodChainNode * MethodChainGrammarAction(MethodNode* method, MethodChainNode* next);
MethodChainNode * EmptyMethodChainGrammarAction();
MethodIdentifierNode* MethodIdentifierGrammarAction(const char* name);
MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsNode* params);
CustomMethodIdentifierNode* CustomMethodIdentifierGrammarAction(char* name);

ParamNode* ParamGrammarAction(ValueNode* value);
ParamNode * ParamVariableGrammarAction(const int variableIdentifier);
ParamNode * ParamObjectElementGrammarAction(const int objectElement);
ParamNode * ParamInlineObjectGrammarAction(const int inlineObject);
ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params);
ParamsBlockNode * ParamsBlockGrammarAction(const int params);
EmptyParamsNode* EmptyParamsGrammarAction();


/* Imaginate */
FocusNode* FocusAddGrammarAction(ValueNode* var);
ForEachFocusNode * FocusForEachGrammarAction(ParamsNode * paramsBlock);
RenderNode* RenderGrammarAction();

OptionalNode* OptionalQuestionSignGrammarAction();
OptionalNode* EmptyOptionalGrammarAction();


/* Objetos */
ObjectIdentifierNode* ObjectIdentifierGrammarAction(char* name);
ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next);
ObjectAssignmentNode* ObjectAssignmentGrammarAction(IdentifierNode* variable, ValueNode* value);
ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, ValueNode* value);
ObjectContentNode* EmptyObjectContentGrammarAction();
InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content);

RenderNode * RenderAllGrammarAction();
ValueNode * ParamStringGrammarAction(const char * sval);
ValueNode * ParamIntegerGrammarAction(const int ival) ;



#endif

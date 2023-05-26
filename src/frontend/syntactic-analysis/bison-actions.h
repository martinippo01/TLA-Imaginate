#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 *
 * A grandes rasgos el AST formado es:
  
  ProgramNode
  ├── AssignmentsNode
  │   ├── AssignmentNode
  │   │   ├── IdentifierNode (for variableIdentifier)
  │   │   └── ValueNode (for value, which could be a ValueStringGrammarAction, ValueIntegerGrammarAction or ValueObjectGrammarAction)
  │   └── AssignmentsNode (recursively for multiple assignments)
  ├── DefinitionsNode
  │   ├── DefinitionNode
  │   │   ├── IdentifierNode (for customMethodIdentifier)
  │   │   ├── ParamsNode (for paramsBlock)
  │   │   └── MethodChainNode (for methodChain)
  │   └── DefinitionsNode (recursively for multiple definitions)
  └── ImaginateNode
      ├── FocusNode (for focus)
      ├── MethodChainNode (for methodChain)
      └── RenderNode (for render)

 */

ProgramNode* ProgramGrammarAction(AssignmentsNode* assignments, DefinitionsNode* definitions, ImaginateNode* imaginate);


/*
 * Aca se divide el compilador en las tres partes principales: 
 *   asignaciones (val abc : xyz)
 *   definiciones (def abc(xyz):)
 *   imaginate(Imaginate.focus().abc.render())
 *
 * */
AssignmentsNode* AssignmentsGrammarAction(AssignmentNode* assignment, AssignmentsNode* next);
DefinitionsNode* DefinitionsGrammarAction(DefinitionNode* definition, DefinitionsNode* next);
ImaginateNode* ImaginateGrammarAction(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render);

/* 
 * Asignaciones
 * */
AssignmentsNode * EmptyAssignmentsGrammarAction();
AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ExpressionNode* expression);
IdentifierNode* VariableIdentifierGrammarAction(const char* name);
ValueNode* ValueIntegerGrammarAction(const int value);
ValueNode* ValueStringGrammarAction(const char* value);
ValueNode * ValueObjectGrammarAction(ObjectNode * objectIdentifier);

/* 
 * Definciones
 * */
DefinitionNode * EmptyDefinitionsGrammarAction();
DefinitionNode * DefinitionGrammarAction(IdentifierNode * identifier, ParamsNode * params, MethodChainNode * methodChain);

MethodChainNode * MethodChainGrammarAction(MethodNode* method, MethodChainNode* next);
MethodChainNode * EmptyMethodChainGrammarAction();
MethodIdentifierNode* MethodIdentifierGrammarAction(const char* name);
MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsNode* params);
MethodIdentifierNode * CustomMethodIdentifierGrammarAction(char* name);

/* Parametros */
ValueNode * ParamStringGrammarAction(const char * sval);
ValueNode * ParamIntegerGrammarAction(const int ival) ;
ParamNode* ParamGrammarAction(ValueNode* value);
ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier);
ParamNode * ParamObjectElementGrammarAction(ObjectElementNode * objectElement);
ParamNode * ParamInlineObjectGrammarAction(InlineObjectNode * inlineObject);
ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params);
ParamsBlockNode * ParamsBlockGrammarAction(ParamsNode * params);
EmptyParamsNode* EmptyParamsGrammarAction();


/* 
 * Imaginate
 * */
FocusNode* FocusAddGrammarAction(ValueNode* var);
ForEachFocusNode * FocusForEachGrammarAction(ParamsNode * paramsBlock);

RenderNode* RenderGrammarAction();
RenderNode * RenderAllGrammarAction();

OptionalNode* OptionalQuestionSignGrammarAction();
OptionalNode* EmptyOptionalGrammarAction();


/* 
 * Objetos
 * */
ObjectNode* ObjectNodeGrammarAction(ObjectContentNode * content);
ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next);
ObjectAssignmentNode* ObjectAssignmentValueGrammarAction(IdentifierNode* variable, ValueNode * value);
ObjectAssignmentNode* ObjectAssignmentIdentifierGrammarAction(IdentifierNode* variable, IdentifierNode * value);
ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, IdentifierNode * value);
ObjectContentNode* EmptyObjectContentGrammarAction();
InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content);



#endif

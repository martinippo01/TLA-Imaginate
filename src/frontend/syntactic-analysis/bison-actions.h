#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/support/garbage-collector.h"
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
ImaginateNode* ImaginateGrammarActionFocus(FocusNode* focus, MethodChainNode* methodChain, RenderNode* render);
ImaginateNode* ImaginateGrammarActionForEachFocus(ForEachFocusNode* focuses, MethodChainNode* methodChain, RenderNode* render);

/* 
 * Asignaciones
 * */
AssignmentsNode * EmptyAssignmentsGrammarAction();
AssignmentNode* AssignmentGrammarAction(IdentifierNode * identifier, ValueNode * expression);
IdentifierNode* VariableIdentifierGrammarAction(const char * name);
ValueNode* ValueIntegerGrammarAction(int value);
ValueNode* ValueStringGrammarAction(const char * value);
AssignmentNode * ValueObjectGrammarAction(IdentifierNode * identifier, ObjectNode * objectIdentifier);

/* 
 * Definciones
 * */
DefinitionsNode * EmptyDefinitionsGrammarAction();
DefinitionNode * DefinitionGrammarAction(const char * identifier, ArgumentsBlockNode * params, MethodChainNode * methodChain);

MethodChainNode * MethodChainGrammarAction(MethodNode* method, MethodChainNode* next);
MethodChainNode * EmptyMethodChainGrammarAction();

//MethodIdentifierNode* MethodIdentifierGrammarAction(const int name);

MethodNode* MethodGrammarAction(OptionalNode * optional, MethodIdentifierNode* identifier, ParamsBlockNode * params);

MethodIdentifierNode * CustomMethodIdentifierGrammarAction(const char * name);
MethodIdentifierNode * AddBackgroundMethodIdentifierGrammarAction(const int id);
MethodIdentifierNode * AddFlavourMethodIdentifierGrammarAction(const int id);
MethodIdentifierNode * PickFlavourMethodIdentifierGrammarAction(const int id);
MethodIdentifierNode * AddGrayScaleMethodIdentifierGrammarAction(const int id);
MethodIdentifierNode * AddBlackAndWhiteIdentifierGrammarAction(const int id);
MethodIdentifierNode * AddContrastMethodIdentifierGrammarAction(const int id);

/* Argumentos */
ArgumentsBlockNode * ArgumentsBlockGrammarAction(ArgumentsNode * arguments);
ArgumentsNode * ArgumentGrammarAction(ArgumentNode * argument);
ArgumentsNode * ArgumentsGrammarAction(ArgumentNode * argument, ArgumentsNode * nextArgs);
ArgumentNode * ArgumentIdentifierGrammarAction(const char * name);
ArgumentsNode * EmptyArgumentsGrammarAction();

/* Parametros */
ParamNode * ParamStringGrammarAction(const char * sval);
ParamNode * ParamIntegerGrammarAction(int ival) ;
ParamsNode* ParamGrammarAction(ParamNode * paramNode);
ParamNode * ParamVariableGrammarAction(IdentifierNode * variableIdentifier);
ParamNode * ParamObjectElementGrammarAction(ObjectElementNode * objectElement);
ParamNode * ParamInlineObjectGrammarAction(InlineObjectNode * inlineObject);
ParamsNode* ParamsGrammarAction(ParamNode* param, ParamsNode* params);
ParamsBlockNode * ParamsBlockGrammarAction(ParamsNode * params);
ParamsNode * EmptyParamsGrammarAction();


/* 
 * Imaginate
 * */
FocusNode* FocusAddGrammarAction(ParamsBlockNode * var);
ForEachFocusNode * FocusForEachGrammarAction(ParamsBlockNode * paramsBlock);

RenderNode* RenderGrammarAction();
RenderNode * RenderAllGrammarAction();

OptionalNode* OptionalQuestionSignGrammarAction();
OptionalNode* EmptyOptionalGrammarAction();


/* 
 * Objetos
 * */
ObjectContentNode *  ObjectAssignmentGrammarAction(ObjectAssignmentNode * assignment);
ObjectContentNode *  ObjectAssignmentsGrammarAction(ObjectAssignmentNode * assignment, ObjectContentNode * next);
ObjectNode* ObjectNodeGrammarAction(ObjectContentNode * content);
ObjectContentNode* ObjectContentGrammarAction(ObjectAssignmentNode* assignment, ObjectContentNode* next);
ObjectAssignmentNode* ObjectAssignmentValueGrammarAction(IdentifierNode* variable, ValueNode * value);
ObjectAssignmentNode* ObjectAssignmentIdentifierGrammarAction(IdentifierNode* variable, IdentifierNode * value);
ObjectElementNode* ObjectElementGrammarAction(IdentifierNode* identifier, IdentifierNode * value);
ObjectContentNode* EmptyObjectContentGrammarAction();
InlineObjectNode* InlineObjectGrammarAction(ObjectContentNode* content);



#endif

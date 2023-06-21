#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER
#include "../semantic-analysis/abstract-syntax-tree.h"

void Generator(ProgramNode * program, int executePython);

void generateDefinitions(DefinitionsNode * definitionsNode);
void generateDefinition(DefinitionNode * definitionNode);
void generateArgumentsBlockNode(ArgumentsBlockNode * argumentsBlockNode);
void generateArgumentsNode(ArgumentsNode * argumentsNode);

void generateVariables(AssignmentsNode * assignmentsNode);
void generateIdentifier(IdentifierNode * identifierNode);
void generateExpression(ValueNode * valueNode);

void generateImagenate(ImaginateNode * imaginateNode);

void generateFocus(FocusNode * FocusNode);

void generateForEachFocus(ForEachFocusNode * forEachFocusNode);
void generateMethodChain(MethodChainNode * methodChainNode, char * );

void generateRender(RenderNode * renderNode);
void generateParams(ParamsNode * paramsNode);
void generateParamsBlock(ParamsBlockNode * paramsBlockNode);
void generateValue(ValueNode * valueNode);
void generateMethodChain(MethodChainNode * methodChainNode, char * defIdentation);
void generateMethod(MethodNode * methodNode, char * defIdentation);
#endif

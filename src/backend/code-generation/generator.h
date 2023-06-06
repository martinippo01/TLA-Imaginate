#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER
#include "../semantic-analysis/abstract-syntax-tree.h"

void Generator(ProgramNode * program);

void generateImagenate(ImaginateNode * imaginateNode);

void generateFocus(FocusNode * FocusNode);

void generateForEachFocus(ForEachFocusNode * forEachFocusNode);
void generateMethodChain(MethodChainNode * methodChainNode);

void generateRender(RenderNode * renderNode);
void generateParams(ParamsNode * paramsNode);
void generateParamsBlock(ParamsBlockNode * paramsBlockNode);
void generateValue(ValueNode * valueNode);
void generateMethodChain(MethodChainNode * methodChainNode);
void generateMethod(MethodNode * methodNode);
#endif

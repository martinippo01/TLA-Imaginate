#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include <stdlib.h>

typedef struct ProgramNode {
    struct AssignmentsNode* assignments;
    struct DefinitionsNode* definitions;
    struct ImaginateNode* imaginate;
} ProgramNode;

typedef struct AssignmentsNode {
    struct AssignmentNode* assignment;
    struct AssignmentsNode* next;
} AssignmentsNode;

typedef struct DefinitionsNode {
    struct DefinitionNode* definition;
    struct DefinitionsNode* next;
} DefinitionsNode;

typedef struct ImaginateNode {
    struct FocusNode* focus;
    struct MethodChainNode* methodChain;
    struct RenderNode* render;
} ImaginateNode;

typedef struct AssignmentNode {
  	struct IdentifierNode * identifier;
    struct ExpressionNode* expression;
} AssignmentNode;

typedef struct DefinitionNode {
  	struct IdentifierNode * identifier;
    struct ParamsNode* params;
    struct MethodChainNode * methodChain;
} DefinitionNode;

typedef struct FocusNode {
    struct ValueNode* var;
} FocusNode;

typedef struct MethodChainNode {
    struct MethodNode* method;
    struct MethodChainNode* next;
} MethodChainNode;

typedef struct RenderNode {
} RenderNode;

typedef struct MethodNode{
} MethodNode;

typedef struct IdentifierNode {
} IdentifierNode;

typedef struct ValueNode{
} ValueNode;

typedef struct ExpressionNode{
} ExpressionNode;

typedef struct ParamsNode{
} ParamsNode;
#endif

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


typedef struct ExpressionNode{
} ExpressionNode;

typedef struct ParamsNode{
} ParamsNode;

typedef struct IdentifierNode {
    char* name;
} IdentifierNode;

typedef struct ValueNode {
    enum {INT_VALUE, STRING_VALUE, OBJECT_VALUE} type;
    union {
        int intValue;
        char* stringValue;
        IdentifierNode* objectValue;
    } value;
} ValueNode;

// Structure for a parameter node.
typedef struct ParamNode {
    ValueNode* value;
} ParamNode;

// Structure for a parameters block node.
typedef struct ParamsBlockNode {
    ParamNode* param;
    struct ParamsBlockNode* next;
} ParamsBlockNode;

// Structure for an optional node.
typedef struct OptionalNode {
    int isQuestionMarkPresent; // boolean (1 for yes, 0 for no)
} OptionalNode;

// Structure for a method identifier node.
typedef struct MethodIdentifierNode {
    char* name;
} MethodIdentifierNode;
#endif

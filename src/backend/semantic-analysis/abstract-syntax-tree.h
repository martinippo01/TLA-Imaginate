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
    struct ParamsBlockNode* params;
    struct MethodChainNode * methodChain;
} DefinitionNode;

typedef struct FocusNode {
    struct ValueNode* var;
} FocusNode;

typedef struct MethodChainNode {
    struct MethodNode* method;
    struct MethodChainNode* next;
} MethodChainNode;
enum renderType{
    RENDER,
    RENDERALL
};
typedef struct RenderNode {
    renderType type;
} RenderNode;


typedef struct ExpressionNode{
} ExpressionNode;

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

typedef struct ParamNode {
    ValueNode* value;
} ParamNode;

typedef struct ParamsBlockNode {
    ParamNode* param;
    struct ParamsBlockNode* next;
} ParamsBlockNode;

typedef struct OptionalNode {
    int isQuestionMarkPresent; 
} OptionalNode;

typedef struct MethodIdentifierNode {
    char* name;
} MethodIdentifierNode;

typedef struct EmptyParamsNode {
    int isEmpty; 
} EmptyParamsNode;

typedef struct MethodNode {
    MethodIdentifierNode* identifier;
    ParamsBlockNode* params;
} MethodNode;

typedef struct CustomMethodIdentifierNode {
    char* name;
} CustomMethodIdentifierNode;

typedef struct ObjectIdentifierNode {
    char* name;
} ObjectIdentifierNode;

typedef struct ObjectContentNode {
    struct ObjectContentNode* next;
    struct ObjectAssignmentNode* assignment;
} ObjectContentNode;

typedef struct ObjectAssignmentNode {
    IdentifierNode* variable;
    ValueNode* value;
} ObjectAssignmentNode;

typedef struct ObjectElementNode {
    IdentifierNode* identifier;
    ValueNode* value;
} ObjectElementNode;

typedef struct InlineObjectNode {
    ObjectContentNode* content;
} InlineObjectNode;
#endif

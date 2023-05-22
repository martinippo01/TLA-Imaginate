#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include <stdlib.h>
/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Expression Expression;

/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/
typedef struct {
	int value;
} Constant;

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/
typedef enum {
	EXPRESSION,
	CONSTANT
} FactorType;

typedef struct {
	FactorType type;
	Expression * expression;
} Factor;

typedef enum {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTOR
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression * leftExpression;
	Expression * rightExpression;
};

typedef struct {
	Expression * expression;
} Program;

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

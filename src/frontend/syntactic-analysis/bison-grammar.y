%{

#include "bison-actions.h"

%}

%union {
	struct ProgramNode* program;
  
  struct AssignmentsNode* assignments;
  struct DefinitionsNode* definitions;
  struct ImaginateNode* imaginate;
	
  struct AssignmentNode * assignment;
  struct DefinitionNode * definition;
	struct FocusNode * focus;
  struct MethodChainNode * methodChain;
  struct RenderNode * render;

  struct MethodIdentifierNode * methodIdentifier; 
  struct IdentifierNode * variableIdentifier; 
  struct ValueNode * value; 
  struct ParamNode * param;
  struct ParamsBlockNode * params;
  struct ParamsBlockNode * paramsBlock;
  struct OptionalNode * optional;

	struct EmptyParamsNode * emptyParams;
	struct MethodNode * method;
  struct CustomMethodIdentifierNode * customMethodIdentifier;
  struct ObjectIdentifierNode * objectIdentifier;
  struct ObjectContentNode * objectContent;
  struct ObjectAssignmentNode * objectAssignment;
  struct ObjectElementNode * objectElement;
  struct InlineObjectNode * inlineObject;

// Terminales.
	token token;
	int integer;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <integer> INTEGER
%token <token> VAL 
%token <token> COLON
%token <token> IDENTIFIER
%token <token> STRING_IDENTIFIER 
%token <token> STRING_DELIMITER 
%token <token> DEF_KEYWORD
%token <token> OPEN_PARENTHESES CLOSE_PARENTHESES CLOSE_CURLY_BRACE OPEN_CURLY_BRACE
%token <token> DOT COMMA QUESTION_SIGN
%token <token> RENDER RENDER_ALL
%token <token> IMAGINATE ADDFOCUS FOREACHFOCUS
%token <token> ADDBACKGROUND ADDFLAVOUR PICKFLAVOUR ADDGRAYSCALE ADDCONTRAST ADDBLACKANDWHITE



// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <assignment> assignment
%type <assignments> assignments
%type <definitions> definitions 

%type <variableIdentifier> variableIdentifier
%type <value> value


%type <definition> definition 
%type <customMethodIdentifier> customMethodIdentifier
%type <methodIdentifier> methodIdentifier
%type <param> param
%type <params> params
%type <paramsBlock> paramsBlock
%type <optional> optional
%type <emptyParams> emptyParams
%type <methodChain> methodChain
%type <method> method
%type <focus> focus
%type <render> render
%type <imaginate> imaginate
%type <objectIdentifier> objectIdentifier
%type <objectAssignment> objectAssignment
%type <objectContent> objectContent
%type <objectElement> objectElement
%type <inlineObject> inlineObject
// El símbolo inicial de la gramatica.
%start program

%%

program: assignments definitions imaginate   { $$ = ProgramGrammarAction($1, $2, $3); };

assignments: assignment assignments             { $$ =  AssignmentsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyAssignmentsGrammarAction(); };

assignment: VAL variableIdentifier COLON value  { $$ = AssignmentGrammarAction($2, $4); };

variableIdentifier: IDENTIFIER    { $$ = VariableIdentifierGrammarAction($1); };

value: STRING_IDENTIFIER                        { $$ = ValueStringGrammarAction($1); }
     | INTEGER                                  { $$ = ValueIntegerGrammarAction($1); }
     | objectIdentifier                         { $$ = ValueObjectGrammarAction($1); };

definitions: definition definitions             { $$ = DefinitionsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyDefinitionsGrammarAction(); };

definition: DEF_KEYWORD customMethodIdentifier paramsBlock COLON methodChain { $$ = DefinitionGrammarAction($2, $3, $5); };

emptyParams: OPEN_PARENTHESES CLOSE_PARENTHESES  { $$ = EmptyParamsGrammarAction(); };

imaginate: IMAGINATE focus methodChain render    { $$ = ImaginateGrammarAction($2, $3, $4); };

focus: DOT ADDFOCUS paramsBlock                  { $$ = FocusAddGrammarAction($3); }
     | DOT FOREACHFOCUS paramsBlock              { $$ = FocusForEachGrammarAction($2); };

methodChain: method methodChain  { $$ = MethodChainGrammarAction($1, $2); }
           | /* empty */          { $$ = EmptyMethodChainGrammarAction(); };

method: DOT optional methodIdentifier paramsBlock
      { $$ = MethodGrammarAction($2, $3, $4); };

paramsBlock: OPEN_PARENTHESES params CLOSE_PARENTHESES
           { $$ = ParamsBlockGrammarAction($2); };

optional: QUESTION_SIGN           { $$ = OptionalQuestionSignGrammarAction(); }
        | /* empty */              { $$ = EmptyOptionalGrammarAction(); };

params: param         { $$ = ParamGrammarAction($1); }
	  	| param COMMA params        { $$ = ParamsGrammarAction($1, $3); }
      | /* empty */               { $$ = EmptyParamsGrammarAction(); };

param: STRING_IDENTIFIER          { $$ = ParamStringGrammarAction($1); }
     | INTEGER                   { $$ = ParamIntegerGrammarAction($1); }
      | variableIdentifier        { $$ = ParamVariableGrammarAction($1); }
      | objectElement             { $$ = ParamObjectElementGrammarAction($1); }
      | inlineObject              { $$ = ParamInlineObjectGrammarAction($1); };

inlineObject: OPEN_CURLY_BRACE objectContent CLOSE_CURLY_BRACE { $$ = InlineObjectGrammarAction($2); };

objectElement: variableIdentifier DOT variableIdentifier { $$ = ObjectElementGrammarAction($1, $3); };

render: RENDER emptyParams        { $$ = RenderGrammarAction(); }
      | RENDER_ALL emptyParams    { $$ = RenderAllGrammarAction(); };

methodIdentifier: ADDBACKGROUND   { $$ = MethodIdentifierGrammarAction($1); }
                | ADDFLAVOUR      { $$ = MethodIdentifierGrammarAction($1); }
                 | PICKFLAVOUR     { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDGRAYSCALE    { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDBLACKANDWHITE { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDCONTRAST     { $$ = MethodIdentifierGrammarAction($1); } 
                 | customMethodIdentifier { $$ = MethodIdentifierGrammarAction($1); };

customMethodIdentifier: IDENTIFIER { $$ = VariableIdentifierGrammarAction($1); };

objectIdentifier: OPEN_CURLY_BRACE objectContent CLOSE_CURLY_BRACE { $$ = ObjectIdentifierGrammarAction($2); };

objectContent: objectAssignment objectContent { $$ = ObjectContentGrammarAction($1, $2); }
             | /* empty */                   { $$ = EmptyObjectContentGrammarAction(); };

objectAssignment: variableIdentifier COLON value COMMA { $$ = ObjectAssignmentGrammarAction($1, $3); }
                | variableIdentifier COLON value        { $$ = ObjectAssignmentGrammarAction($1, $3); }
								| variableIdentifier COLON variableIdentifier COMMA { $$ = ObjectAssignmentGrammarAction($1, $3); }
                | variableIdentifier COLON variableIdentifier       { $$ = ObjectAssignmentGrammarAction($1, $3); };


%%

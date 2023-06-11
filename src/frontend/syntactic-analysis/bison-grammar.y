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
	struct ForEachFocusNode * foreachFocus;
  struct MethodChainNode * methodChain;
  struct RenderNode * render;

  struct MethodIdentifierNode * methodIdentifier; 
  struct IdentifierNode * variableIdentifier; 
  struct ValueNode * value; 
  struct ParamNode * param;
  struct ParamsNode * params;
  struct ParamsBlockNode * paramsBlock;
  struct ArgumentsBlockNode * argumentsBlock;
  struct ArgumentNode * argument;
  struct ArgumentsNode * arguments;
  struct OptionalNode * optional;

	struct ParamsNode * emptyParams;
	struct MethodNode * method;
  struct ObjectNode * object;
  struct ObjectContentNode * objectContent;
  struct ObjectAssignmentNode * objectAssignment;
  struct ObjectElementNode * objectElement;
  struct InlineObjectNode * inlineObject;

// Terminales.
	token token;
	int integer;
	char * string;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <integer> INTEGER
%token <token> VAL 
%token <token> COLON
%token <string> IDENTIFIER
%token <string> STRING_IDENTIFIER 
%token <string> STRING_DELIMITER 
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

%type <argumentsBlock> argumentsBlock
%type <arguments> arguments
%type <argument> argument

%type <definition> definition 
%type <methodIdentifier> methodIdentifier
%type <param> param
%type <params> params
%type <paramsBlock> paramsBlock
%type <optional> optional
%type <emptyParams> emptyParams
%type <methodChain> methodChain
%type <method> method
%type <focus> focus
%type <foreachFocus> foreachFocus 
%type <render> render
%type <imaginate> imaginate
%type <object> object
%type <objectAssignment> objectAssignment
%type <objectContent> objectContent
%type <objectElement> objectElement
%type <inlineObject> inlineObject
%start program

%%

program: assignments definitions imaginate   { $$ = ProgramGrammarAction($1, $2, $3); };

assignments: assignment assignments             { $$ =  AssignmentsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyAssignmentsGrammarAction(); };

assignment: VAL variableIdentifier COLON value  { $$ = AssignmentGrammarAction($2, $4); };

variableIdentifier: IDENTIFIER    { $$ = VariableIdentifierGrammarAction($1); };

value: STRING_IDENTIFIER                        { $$ = ValueStringGrammarAction($1); }
     | INTEGER                                  { $$ = ValueIntegerGrammarAction($1); }
     | object                         { $$ = ValueObjectGrammarAction($1); };

definitions: definition definitions             { $$ = DefinitionsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyDefinitionsGrammarAction(); };

definition: DEF_KEYWORD IDENTIFIER argumentsBlock COLON methodChain { $$ = DefinitionGrammarAction($2, $3, $5); };

emptyParams: OPEN_PARENTHESES CLOSE_PARENTHESES  { $$ = EmptyParamsGrammarAction(); };

imaginate: IMAGINATE focus methodChain render    { $$ = ImaginateGrammarActionFocus($2, $3, $4); }
				 |IMAGINATE foreachFocus methodChain render    { $$ = ImaginateGrammarActionForEachFocus($2, $3, $4); }; 

focus: DOT ADDFOCUS paramsBlock                  { $$ = FocusAddGrammarAction($3); };

foreachFocus: DOT FOREACHFOCUS paramsBlock              { $$ = FocusForEachGrammarAction($3); };

methodChain: method methodChain  { $$ = MethodChainGrammarAction($1, $2); }
           | /* empty */          { $$ = EmptyMethodChainGrammarAction(); };

method: DOT optional methodIdentifier paramsBlock
      { $$ = MethodGrammarAction($2, $3, $4); };

paramsBlock: OPEN_PARENTHESES params CLOSE_PARENTHESES
           { $$ = ParamsBlockGrammarAction($2); };

argumentsBlock: OPEN_PARENTHESES arguments CLOSE_PARENTHESES
           { $$ = ArgumentsBlockGrammarAction($2); };


arguments: argument         { $$ = ArgumentGrammarAction($1); }
	  	   | argument COMMA arguments        { $$ = ArgumentsGrammarAction($1, $3); }
         | /* empty */               { $$ = EmptyArgumentsGrammarAction(); };

argument: IDENTIFIER { $$ = ArgumentIdentifierGrammarAction($1); }

optional: QUESTION_SIGN           { $$ = OptionalQuestionSignGrammarAction(); }
        | /* empty */              { $$ = EmptyOptionalGrammarAction(); };

params: param         { $$ = ParamGrammarAction($1); }
	  	| param COMMA params        { $$ = ParamsGrammarAction($1, $3); }
      | /* empty */               { $$ = EmptyParamsGrammarAction(); };

param:  STRING_IDENTIFIER          { $$ = ParamStringGrammarAction($1); }
      | INTEGER                   { $$ = ParamIntegerGrammarAction($1); }
      | variableIdentifier        { $$ = ParamVariableGrammarAction($1); }
      | objectElement             { $$ = ParamObjectElementGrammarAction($1); }
/*       | inlineObject              { $$ = ParamInlineObjectGrammarAction($1); }; */
/**/
/* inlineObject: OPEN_CURLY_BRACE objectContent CLOSE_CURLY_BRACE { $$ = InlineObjectGrammarAction($2); }; */

objectElement: variableIdentifier DOT variableIdentifier { $$ = ObjectElementGrammarAction($1, $3); };

render: RENDER emptyParams        { $$ = RenderGrammarAction(); }
      | RENDER_ALL emptyParams    { $$ = RenderAllGrammarAction(); };

methodIdentifier: ADDBACKGROUND   { $$ = AddBackgroundMethodIdentifierGrammarAction($1); }
                | ADDFLAVOUR      { $$ = AddFlavourMethodIdentifierGrammarAction($1); }
                 | PICKFLAVOUR     { $$ = PickFlavourMethodIdentifierGrammarAction($1); }
                 | ADDGRAYSCALE    { $$ = AddGrayScaleMethodIdentifierGrammarAction($1); }
                 | ADDBLACKANDWHITE { $$ = AddBlackAndWhiteIdentifierGrammarAction($1); }
                 | ADDCONTRAST     { $$ = AddContrastMethodIdentifierGrammarAction($1); } 
                 | IDENTIFIER { $$ = CustomMethodIdentifierGrammarAction($1); };


object: OPEN_CURLY_BRACE objectContent CLOSE_CURLY_BRACE { $$ = ObjectNodeGrammarAction($2); };

objectContent: objectAssignment objectContent { $$ = ObjectContentGrammarAction($1, $2); }
             | /* empty */                   { $$ = EmptyObjectContentGrammarAction(); };

objectAssignment: variableIdentifier COLON value COMMA { $$ = ObjectAssignmentValueGrammarAction($1, $3); }
                | variableIdentifier COLON value        { $$ = ObjectAssignmentValueGrammarAction($1, $3); }
								/* | variableIdentifier COLON variableIdentifier COMMA { $$ = ObjectAssignmentIdentifierGrammarAction($1, $3); } */
        /*         | variableIdentifier COLON variableIdentifier       { $$ = ObjectAssignmentIdentifierGrammarAction($1, $3); }; */


%%

%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
  	int variable;
	
   // No-terminales (frontend).
	int program;
	int assignment;
	int assignments;
	int variableIdentifier;
	int methodIdentifier;
	int param;
	int definition;
	int definitions;

	int value;

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
%token <token> DEF_KEYWORD
%token <token> OPEN_PARENTHESES CLOSE_PARENTHESES
%token <token> DOT COMMA QUESTION_SIGN
%token <token> RENDER RENDER_ALL
%token <token> IMAGINATE ADDFOCUS FOREACHFOCUS
%token <token> ADDBACKGROUND ADDFLAVOUR PICKFLAVOUR ADDGRAYSCALE ADDCONTRAST



// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <assignment> assignment
%type <assignments> assignments
%type <definitions> definitions 

%type <variableIdentifier> variableIdentifier
%type <value> value


%type <definition> definition 
%type <assignments> assignments
%type <methodIdentifier> methodIdentifier
%type <param> param
%type <params> params

%type <emptyParams> emptyParams
%type <methodChain> methodChain
%type <focus> focus
%type <render> render


// El símbolo inicial de la gramatica.
%start program

%%

program: assignments definitions imaginate   { $$ = ProgramGrammarAction($1, $2, $3); };

assignments: assignment assignments             { $$ =  AssignmentsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyAssignmentsGrammarAction(); };

assignment: VAL variableIdentifier COLON value  { $$ = AssignmentGrammarAction($2, $4); };

variableIdentifier: IDENTIFIER    { $$ = VariableIdentifierGrammarAction($1); };

value: STRING_IDENTIFIER                        { $$ = ValueStringGrammarAction($1); }
     | INTEGER                                  { $$ = ValueIntegerGrammarAction($1); };

definitions: definition definitions             { $$ = DefinitionsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyDefinitionsGrammarAction(); };

definition: DEF_KEYWORD variableIdentifier emptyParams COLON methodChain
                                                  { $$ = DefinitionGrammarAction($2, $5); };

emptyParams: OPEN_PARENTHESES CLOSE_PARENTHESES  { $$ = EmptyParamsGrammarAction(); };

imaginate: IMAGINATE focus methodChain render    { $$ = ImaginateGrammarAction($2, $3, $4); };

focus: DOT ADDFOCUS paramsBlock                  { $$ = FocusAddGrammarAction($2); }
     | DOT FOREACHFOCUS paramsBlock              { $$ = FocusForEachGrammarAction($2); };

methodChain: method methodChain  { $$ = MethodChainGrammarAction($1, $2); }
           | /* empty */          { $$ = EmptyMethodChainGrammarAction(); };

method: DOT optional methodIdentifier paramsBlock
                                  { $$ = MethodGrammarAction($2, $3, $4); };

paramsBlock: OPEN_PARENTHESES params CLOSE_PARENTHESES
                                  { $$ = ParamsBlockGrammarAction($2); };

optional: QUESTION_SIGN           { $$ = OptionalQuestionSignGrammarAction(); }
        | /* empty */              { $$ = EmptyOptionalGrammarAction(); };

params: param COMMA params        { $$ = ParamsGrammarAction($1, $3); }
      | /* empty */               { $$ = EmptyParamsGrammarAction(); };

param: STRING_IDENTIFIER          { $$ = ParamStringGrammarAction($1); }
      | INTEGER                   { $$ = ParamIntegerGrammarAction($1); };

render: RENDER emptyParams        { $$ = RenderGrammarAction(); }
      | RENDER_ALL emptyParams    { $$ = RenderAllGrammarAction(); };

variableIdentifier: IDENTIFIER    { $$ = VariableIdentifierGrammarAction($1); };

methodIdentifier: ADDBACKGROUND   { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDFLAVOUR      { $$ = MethodIdentifierGrammarAction($1); }
                 | PICKFLAVOUR     { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDGRAYSCALE    { $$ = MethodIdentifierGrammarAction($1); }
                 | ADDCONTRAST     { $$ = MethodIdentifierGrammarAction($1); };

%%
%%

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


// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <assignment> assignment
%type <variableIdentifier> variableIdentifier
%type <value> value
%type <assignments> assignments

// El símbolo inicial de la gramatica.
%start program

%%

program: assignments       { $$ = ProgramGrammarAction($1); };

assignments: assignment assignments             { $$ =  AssignmentsGrammarAction($1, $2); }
           | /* empty */                        { $$ = EmptyAssignmentsGrammarAction(); };

assignment: VAL variableIdentifier COLON value  { $$ = AssignmentGrammarAction($2, $4); };

variableIdentifier: IDENTIFIER    { $$ = VariableIdentifierGrammarAction($1); };

value: STRING_IDENTIFIER                        { $$ = ValueStringGrammarAction($1); }
     | INTEGER                                  { $$ = ValueIntegerGrammarAction($1); };

%%

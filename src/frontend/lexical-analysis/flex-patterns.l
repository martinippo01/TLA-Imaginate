%{
#include "flex-actions.h"
%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */

/* Patrones reutilizables. */
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]
letter        [a-zA-Z]
alphanumeric [a-zA-Z0-9]
str             .+

%%
"val"                   { return ValKeywordPatternAction(yytext); }
":"                     { return ColonOperatorPatternAction(yytext); }
"\""                    { return StringDelimiterPatternAction(yytext); }
"def"                   { return DefKeywordPatternAction(yytext); }
"("                     { return OpenParenthesisPatternAction(yytext); }
")"                     { return CloseParenthesisPatternAction(yytext); }
"{"                     { return OpenCurlyBracePatternAction(yytext); }
"}"                     { return CloseCurlyBracePatternAction(yytext); }
"."                     { return DotPatternAction(yytext); }
","                     { return CommaPatternAction(yytext); }
"?"                     { return QuestionSignPatternAction(yytext); }
".render"                { return RenderKeywordPatternAction(yytext); }
".renderAll"             { return RenderAllKeywordPatternAction(yytext); }
"Imaginate"             { return ImaginateKeywordPatternAction(yytext); }
"addFocus"              { return AddFocusKeywordPatternAction(yytext); }
"forEachFocus"          { return ForEachFocusKeywordPatternAction(yytext); }
"addBackground"         { return AddBackgroundKeywordPatternAction(yytext); }
"addFlavour"            { return AddFlavourKeywordPatternAction(yytext); }
"pickFlavour"           { return PickFlavourKeywordPatternAction(yytext); }
"addGrayscale"          { return AddGrayscaleKeywordPatternAction(yytext); }
"addContrast"           { return AddContrastKeywordPatternAction(yytext); }
"blackAndWhite"       { return AddBlackAndWhitePatternAction(yytext); }
{digit}+                { return IntegerPatternAction(yytext, yyleng); }
{whitespace}+                   /* ignore whitespace */;
{letter}({alphanumeric}|-)* { return IdentifierPatternAction(yytext); }
\"{str}\"                   {return StringDelimiterPatternAction(yytext);}
%%

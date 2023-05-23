#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

token IntegerPatternAction(const char * lexeme, int length) {
    LogDebug("IntegerPatternAction: %s \n", lexeme);
    yylval.integer = atoi(lexeme);
    return INTEGER;
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}

void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}

//_____________________________________________________________________________
token ValKeywordPatternAction(const char * lexeme) {
    LogDebug("ValKeywordPatternAction: %s \n", lexeme);
    yylval.token = VAL;
    return VAL;
}

token ColonOperatorPatternAction(const char * lexeme) {
    LogDebug("ColonOperatorPatternAction: %s \n", lexeme);
    yylval.token = COLON;
    return COLON;
}

token StringDelimiterPatternAction(const char * lexeme) {
    LogDebug("StringDelimiterPatternAction: %s \n", lexeme);

    char * text = (char *) calloc(length + 1, sizeof(char));
    strncpy(text, lexeme, length);
    yylval.token = text;
    return STRING_IDENTIFIER;
}

token IdentifierPatternAction(const char * lexeme) {
    LogDebug("IdentifierPatternAction: %s \n", lexeme);
    yylval.token = IDENTIFIER;
    return IDENTIFIER;
}

token DefKeywordPatternAction(const char * lexeme) {
    LogDebug("DefKeywordPatternAction: %s \n", lexeme);
    yylval.token = DEF_KEYWORD;
    return DEF_KEYWORD;
}

token OpenParenthesisPatternAction(const char * lexeme) {
    LogDebug("OpenParenthesisPatternAction: %s \n", lexeme);
    yylval.token = OPEN_PARENTHESES;
    return OPEN_PARENTHESES;
}

token CloseParenthesisPatternAction(const char * lexeme) {
    LogDebug("CloseParenthesisPatternAction: %s \n", lexeme);
    yylval.token = CLOSE_PARENTHESES;
    return CLOSE_PARENTHESES;
}

token OpenCurlyBracePatternAction(const char * lexeme) {
    LogDebug("OpenCurlyBracePatternAction: %s \n", lexeme);
    yylval.token = OPEN_CURLY_BRACE;
    return OPEN_CURLY_BRACE;
}

token CloseCurlyBracePatternAction(const char * lexeme) {
    LogDebug("CloseCurlyBracePatternAction: %s \n", lexeme);
    yylval.token = CLOSE_CURLY_BRACE;
    return CLOSE_CURLY_BRACE;
}

token DotPatternAction(const char * lexeme) {
    LogDebug("DotPatternAction: %s \n", lexeme);
    yylval.token = DOT;
    return DOT;
}

token CommaPatternAction(const char * lexeme) {
    LogDebug("CommaPatternAction: %s \n", lexeme);
    yylval.token = COMMA;
    return COMMA;
}

token QuestionSignPatternAction(const char * lexeme) {
    LogDebug("QuestionSignPatternAction: %s \n", lexeme);
    yylval.token = QUESTION_SIGN;
    return QUESTION_SIGN;
}

token RenderKeywordPatternAction(const char * lexeme) {
    LogDebug("RenderKeywordPatternAction: %s \n", lexeme);
    yylval.token = RENDER;
    return RENDER;
}

token RenderAllKeywordPatternAction(const char * lexeme) {
    LogDebug("RenderAllKeywordPatternAction: %s \n", lexeme);
    yylval.token = RENDER_ALL;
    return RENDER_ALL;
}

token ImaginateKeywordPatternAction(const char * lexeme) {
    LogDebug("ImaginateKeywordPatternAction: %s \n", lexeme);
    yylval.token = IMAGINATE;
    return IMAGINATE;
}

token AddFocusKeywordPatternAction(const char * lexeme) {
    LogDebug("AddFocusKeywordPatternAction: %s \n", lexeme);
    yylval.token = ADDFOCUS;
    return ADDFOCUS;
}

token ForEachFocusKeywordPatternAction(const char * lexeme) {
    LogDebug("ForEachFocusKeywordPatternAction: %s \n", lexeme);
    yylval.token = FOREACHFOCUS;
    return FOREACHFOCUS;
}

token AddBackgroundKeywordPatternAction(const char * lexeme) {
    LogDebug("AddBackgroundKeywordPatternAction: %s \n", lexeme);
    yylval.token = ADDBACKGROUND;
    return ADDBACKGROUND;
}

token AddFlavourKeywordPatternAction(const char * lexeme) {
    LogDebug("AddFlavourKeywordPatternAction: %s \n", lexeme);
    yylval.token = ADDFLAVOUR;
    return ADDFLAVOUR;
}

token PickFlavourKeywordPatternAction(const char * lexeme) {
    LogDebug("PickFlavourKeywordPatternAction: %s \n", lexeme);
    yylval.token = PICKFLAVOUR;
    return PICKFLAVOUR;
}

token AddGrayscaleKeywordPatternAction(const char * lexeme) {
    LogDebug("AddGrayscaleKeywordPatternAction: %s \n", lexeme);
    yylval.token = ADDGRAYSCALE;
    return ADDGRAYSCALE;
}

token AddContrastKeywordPatternAction(const char * lexeme) {
    LogDebug("AddContrastKeywordPatternAction: %s \n", lexeme);
    yylval.token = ADDCONTRAST;
    return ADDCONTRAST;
}

token AddBlackAndWhitePatternAction(const char * lexeme) {
    LogDebug("AddBlackAndWhitePatternAction: %s \n", lexeme);
    yylval.token = ADDBLACKANDWHITE;
    return ADDBLACKANDWHITE;
}

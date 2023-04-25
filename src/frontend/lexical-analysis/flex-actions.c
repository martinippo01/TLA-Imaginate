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
    yylval.token = STRING_DELIMITER;
    return STRING_DELIMITER;
}

token IdentifierPatternAction(const char * lexeme) {
    LogDebug("IdentifierPatternAction: %s \n", lexeme);
    yylval.token = IDENTIFIER;
    return IDENTIFIER;
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

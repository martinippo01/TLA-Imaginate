#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);


typedef int token;

token AddBlackAndWhitePatternAction(const char * lexeme);
token ValKeywordPatternAction(const char * lexeme);
token ColonOperatorPatternAction(const char * lexeme);
token StringDelimiterPatternAction(const char * lexeme);
token IdentifierPatternAction(const char * lexeme);
token DefKeywordPatternAction(const char * lexeme);
token OpenParenthesisPatternAction(const char * lexeme);
token CloseParenthesisPatternAction(const char * lexeme);
token DotPatternAction(const char * lexeme);
token CommaPatternAction(const char * lexeme);
token QuestionSignPatternAction(const char * lexeme);
token RenderKeywordPatternAction(const char * lexeme);
token RenderAllKeywordPatternAction(const char * lexeme);
token ImaginateKeywordPatternAction(const char * lexeme);
token AddFocusKeywordPatternAction(const char * lexeme);
token ForEachFocusKeywordPatternAction(const char * lexeme);
token AddBackgroundKeywordPatternAction(const char * lexeme);
token AddFlavourKeywordPatternAction(const char * lexeme);
token PickFlavourKeywordPatternAction(const char * lexeme);
token AddGrayscaleKeywordPatternAction(const char * lexeme);
token AddContrastKeywordPatternAction(const char * lexeme);
token IntegerPatternAction(const char * lexeme, int length);

#endif

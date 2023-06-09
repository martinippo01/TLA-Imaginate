#include "logger.h"

void Log(FILE * const stream, const char * color, const char * prefix, const char * const format, const char * suffix, va_list arguments) {
	fprintf(stream, "%s%s", color, prefix);
	vfprintf(stream, format, arguments);
	fprintf(stream, "%s%s", suffix, ANSI_COLOR_RESET);
}

void LogDebug(const char * const format, ...) {
	#ifdef DEBUG
	va_list arguments;
	va_start(arguments, format);
	Log(stdout, ANSI_COLOR_CYAN, "[DEBUG] ", format, "\n", arguments);
	va_end(arguments);
	#endif
}

void LogError(const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	Log(stderr, ANSI_COLOR_RED, "[ERROR] ", format, "\n", arguments);
	va_end(arguments);
}

void LogErrorRaw(const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	Log(stderr, ANSI_COLOR_RED, "", format, "", arguments);
	va_end(arguments);
}

void LogInfo(const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	Log(stdout, ANSI_COLOR_GREEN, "[INFO ] ", format, "\n", arguments);
	va_end(arguments);
}

void yyerror_(const char *fmt, ...) {
    char string[1024];  // Buffer to hold the generated string.
    va_list args;
    va_start(args, fmt);
    vsnprintf(string, sizeof(string), fmt, args);  // Generate the string.
    va_end(args);

    LogError("Compilation Error : %s .", string);
    LogErrorRaw("\n\n");
}

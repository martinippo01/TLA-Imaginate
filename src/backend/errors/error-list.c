#include "error-list.h"

void initErrorsList(ErrorList list) {
    list.head = NULL;
    list.tail = NULL;
}

void DestroyErrorList(ErrorList *list) {
    ErrorNode *current = list->head;
    while (current != NULL) {
        ErrorNode *next = current->next;
        free(current->error);
        free(current);
        current = next;
    }
    free(list);
}

void AppendError(ErrorList *list, const char *format, ...) {
    // Format the error string.
    char error[MAX_STRING];
    va_list args;
    va_start(args, format);
    vsnprintf(error, sizeof(error), format, args);
    va_end(args);

    ErrorNode *node = malloc(sizeof(ErrorNode));
    node->error = strdup(error);  // Duplicate the string to store it in the node.
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

void TraverseErrorList(ErrorList *list) {
    for (ErrorNode *node = list->head; node != NULL; node = node->next) {
        yyerror_("%s\n", node->error);
    }
}

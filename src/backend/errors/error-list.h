
#ifndef ERROR_LIST_H
#define ERROR_LIST_H

#include "../support/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MAX_STRING 1024

typedef struct ErrorNode {
    char *error;
    struct ErrorNode *next;
} ErrorNode;

typedef struct {
    ErrorNode *head;
    ErrorNode *tail;
} ErrorList;

void initErrorsList(ErrorList list_);

void DestroyErrorList(ErrorList *list);

void AppendError(ErrorList *list, const char *format, ...);

void TraverseErrorList(ErrorList *list);

#endif  // ERROR_LIST_H



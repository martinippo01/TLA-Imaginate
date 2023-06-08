#ifndef _HEADER_DEF_EXECUTION_
#define _HEADER_DEF_EXECUTION_

#include "../symbols-table/definitions/hashmap_defs.h"

void applyCustomMethod(DefsTable, const char *, ParamsBlockNode *);

void applyBuiltInMethod(int, ParamsBlockNode *);


int validateDefinitionSignature(DefsTable hashmap, char * identifier, ParamsBlockNode * params);

#endif

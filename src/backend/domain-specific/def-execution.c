
#include "def-execution.h"

int validateDefinitionSignature(DefsTable hashmap, char * identifier, ParamsBlockNode * params) {

    ValueDef * value = getOrDefaultDefsTable(hashmap, identifier, &DEFAULT_VALUE_NODE);

    if (!value->definition->args || !params) return 0;

    int i = 0;

    ArgumentsNode *args = value->definition->args->params;
    ParamsNode *paramNode = params->params;

    while(args != NULL && paramNode != NULL) {
        i++;
        args = args->next;
        paramNode = paramNode->next;
    }

    return args == NULL && paramNode == NULL;
}

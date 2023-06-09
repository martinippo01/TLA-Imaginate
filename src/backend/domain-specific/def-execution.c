
#include "def-execution.h"

void applyCustomMethod(DefsTable hashmap, const char * identifier, ParamsBlockNode * params) {

}

void applyBuiltInMethod(int id, ParamsBlockNode * params) {

}

int validateDefinitionSignature(DefsTable hashmap, char * identifier, ParamsBlockNode * params) {

    ValueDef * value = getOrDefaultDefsTable(hashmap, identifier, &DEFAULT_VALUE_NODE);

    if (!value->definition->args || !params) return 0;

    ArgumentsNode *args = value->definition->args->params;
    ParamsNode *paramNode = params->params;

    while(args != NULL && paramNode != NULL) {
        args = args->next;
        paramNode = paramNode->next;
    }

    return args == NULL && paramNode == NULL;
}

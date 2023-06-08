#include "hashmap_defs.h"

ValueDef DEFAULT_VALUE_NODE = { .arguments = NULL};

int validateDefinitionSignature(DefsTable hashmap, char * identifier, ParamsBlockNode * params) {

    ValueDef * value = getOrDefaultDefsTable(hashmap, identifier, &DEFAULT_VALUE_NODE);

    // Ensure that value and params are not NULL
    if (!value->arguments || !params) return 0;

    ArgumentsNode *args = value->arguments->params;
    ParamsNode *paramNode = params->params;

    while(args != NULL && paramNode != NULL) {
        args = args->next;
        paramNode = paramNode->next;
    }

    // If both args and paramNode are NULL, then they have the same number of elements
    return args == NULL && paramNode == NULL;
}

static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % SIZE;
}

void initDefsTable(DefsTable hashmap) {
    for (int i = 0; i < SIZE; i++) {
        hashmap[i] = NULL;
    }
}

int putDefsTable(DefsTable hashmap, const char *id, ValueDef value) {
    unsigned long index = hash(id);
    DefNode *node = malloc(sizeof(DefNode));
    if (!node)
        return 0; // memory allocation failed
    node->id = strdup(id);
    if (!node->id) {
        free(node);
        return 0; // memory allocation failed
    }
    node->value = malloc(sizeof(ValueDef));
    if (!node->value) {
        free(node->id);
        free(node);
        return 0; // memory allocation failed
    }
    memcpy(node->value, &value, sizeof(ValueDef));
    node->next = hashmap[index];
    hashmap[index] = node;
    return 1; // operation succeeded
}

ValueDef* getOrDefaultDefsTable(DefsTable hashmap, const char *id, ValueDef * defaultValue) {
    unsigned long index = hash(id);
    for (DefNode *node = hashmap[index]; node != NULL; node = node->next) {
        if (strcmp(node->id, id) == 0) {
            return node->value;
        }
    }
    return defaultValue;
}

int existsDefsTable(DefsTable hashmap, const char *id) {
    unsigned long index = hash(id);
    for (DefNode *node = hashmap[index]; node != NULL; node = node->next) {
        if (strcmp(node->id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

void destroyDefsTable(DefsTable hashmap) {
    for (int i = 0; i < SIZE; i++) {
        DefNode *node = hashmap[i];
        while (node != NULL) {
            DefNode *temp = node;
            node = node->next;
            free(temp->id);
            free(temp->value);
            free(temp);
        }
        hashmap[i] = NULL;
    }
}


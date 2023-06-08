#include "hashmap_defs.h"

unsigned long hash(const char *str) {
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

void destroy(DefsTable hashmap) {
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


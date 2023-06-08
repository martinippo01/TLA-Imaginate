#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>

#define SIZE 101 // A prime number

typedef struct value {
    enum {INT_TYPE, STRING_TYPE} type_enum; 
    char type[256];
    char initialization[256];
} ValueDef;

typedef struct hashnode {
    char *id; 
    ValueDef *value;
    struct hashnode *next;
} DefNode;

typedef DefNode * DefsTable[SIZE];

// Función para inicializar el hashmap
void initDefsTable(DefsTable);

// Función para añadir un elemento al hashmap
// Devuelve 1 si la operación tuvo éxito, 0 en caso contrario
int putDefsTable(DefsTable, const char *, ValueDef);

// Función para obtener un elemento del hashmap
// Devuelve Value si el elemento no está en el hashmap
ValueDef * getOrDefaultDefsTable(DefsTable, const char *, ValueDef *);

// Función para verificar si un elemento está en el hashmap
int existsDefsTable(DefsTable, const char *);

// Función para eliminar y liberar la memoria del hashmap
void destroyDefsTable(DefsTable);

#endif


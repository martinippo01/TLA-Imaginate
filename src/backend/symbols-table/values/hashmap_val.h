#ifndef HASHMAP_VAL_H
#define HASHMAP_VAL_H

#include <stdlib.h>
#include <string.h>

#define SIZE 101 // A prime number

typedef struct valueVal {
    enum {INT_TYPE, STRING_TYPE} type_enum; 
    char type[256];
    char initialization[256];
} Value;

typedef struct hashnode {
    char *id; 
    Value *value;
    struct hashnode *next;
} HashNode;

typedef HashNode* HashMap[SIZE];

// Función para inicializar el hashmap
void initHashMap(HashMap);

// Función para añadir un elemento al hashmap
// Devuelve 1 si la operación tuvo éxito, 0 en caso contrario
int put(HashMap, const char *, Value);

// Función para obtener un elemento del hashmap
// Devuelve Value si el elemento no está en el hashmap
Value* getOrDefault(HashMap, const char *, Value *);

// Función para verificar si un elemento está en el hashmap
int exists(HashMap, const char *);

// Función para eliminar y liberar la memoria del hashmap
void destroy(HashMap);

#endif


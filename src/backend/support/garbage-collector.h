#ifndef GARBAGE_COLLECTOR
#define GARBAGE_COLLECTOR

#include <stdlib.h>
#include <string.h> 
typedef struct Node * List;

struct Node {
    void * ptr;
    List next;
};


char * strdup_(const char * str);

void * calloc_(size_t nitems, size_t size);

void * malloc_(size_t bytes);

void free_all();


#endif

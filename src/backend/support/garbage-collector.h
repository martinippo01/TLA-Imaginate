#ifndef GARBAGE_COLLECTOR
#define GARBAGE_COLLECTOR

#include <stdlib.h>

typedef struct Node * List;

struct Node {
    void * ptr;
    List next;
};

void * calloc_(size_t nitems, size_t size);

void free_all();


#endif

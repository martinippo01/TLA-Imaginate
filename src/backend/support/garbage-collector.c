#include "garbage-collector.h"

List allocated_memory = NULL;

char * strdup_(const char * str) {
  char * alloc = malloc_(strlen(str) + 1);
  strcpy(alloc, str); 
  return alloc;
}

void * calloc_(size_t nitems, size_t size) {
  List new_node = calloc(sizeof(struct Node), 1);
  void * requested_memory = calloc(nitems, size);
  new_node->ptr = requested_memory;
  new_node->next = allocated_memory;
  allocated_memory = new_node;
  return requested_memory;
}


void * malloc_(size_t bytes) {
  List new_node = calloc(sizeof(struct Node), 1);
  void * requested_memory = malloc(bytes);
  new_node->ptr = requested_memory;
  new_node->next = allocated_memory;
  allocated_memory = new_node;
  return requested_memory;
}

static inline void free_all_rec(List node) {
  if(node == NULL) return;
  free_all_rec(node->next);
  free(node->ptr);
  free(node);
}

void free_all() {
  free_all_rec(allocated_memory);
}

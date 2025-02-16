#include "template.h"

metadata* initializeHeap() {
  //char inital_heap[HEAP_SIZE];
  char *inital_heap=(char*)malloc(sizeof(char)*HEAP_SIZE);
  metadata *freeList=(metadata*)inital_heap;
  freeList->size=HEAP_SIZE-sizeof(metadata);
  freeList->next=NULL;
  freeList->free=1;
  return freeList;
}

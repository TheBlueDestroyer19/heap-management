#include <stdio.h>
#include <stdlib.h>
#define HEAP_SIZE 32768

typedef struct metadata{
  size_t size;
  struct metadata* next;
  int free;
}metadata;

metadata* initializeHeap();
void mergeList(metadata **);
void freeBlock(metadata** , metadata* );
void freeHeap(metadata** , metadata* [], int );
metadata* allocate(metadata** , size_t );
void showFreeList(metadata* );

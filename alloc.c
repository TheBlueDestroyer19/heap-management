#include "template.h"

metadata* allocate(metadata** freeList, size_t request) {
  metadata *fptr=*freeList,*prev=NULL;
  int found=0;
  char* end;

  while(fptr!=NULL && !found) {
    if(fptr->size>request+sizeof(metadata)) found=1;
    else {
      prev=fptr;
      fptr=fptr->next;
    }
  }
  if(found) {
    fptr->free=0;
    metadata* leftover=(metadata*)((char*)fptr+sizeof(metadata)+request);

    leftover->size=fptr->size - sizeof(metadata)-request;
    fptr->size=request;

    if(prev!=NULL) prev->next=fptr->next;
    else *freeList=fptr->next;
    metadata* temp=*freeList; prev=NULL; found=0;

    while(temp!=NULL && !found) {
      end=(char*)temp+sizeof(metadata)+temp->size;
      if(end<=(char*)leftover) {
        prev=temp; 
        temp=temp->next;
      }
      else found=1;
    }

    if(prev!=NULL) prev->next=leftover;
    else *freeList=leftover;
    leftover->next=temp;

    printf("Allocated a space from the free space:\n");
    printf("Metadata (size): %u | Size of the block: %u | Free space: %u\n",sizeof(metadata),request,leftover->size);
  }
  else {
    printf("Heap has exhausted! No more allocations can be made!!!\n");
    fptr=NULL;
  }

  return fptr;
}

#include "template.h"

void mergeList(metadata **freeList) {
  metadata *current=*freeList, *prev=*freeList;
  char *end;

  if(current==NULL) printf("No free memory!!\n");
  else if(current->next==NULL) printf("No need to merge!!\n");
  else {
    current=prev->next;
    while(current!=NULL) {
      end=(char*)prev+sizeof(metadata)+prev->size;
      if(end==(char*)current) {
        prev->size=prev->size+sizeof(metadata)+current->size;
        prev->next=current->next;
      }
      else {
        prev=current;
        current=current->next;
      }
    }
  }
}

void freeBlock(metadata** freeList, metadata* block) {
  metadata* fptr=*freeList, *prev=NULL;
  int found=0;
  char* end;

  if(block!=NULL && block->free==0) {
    block->free=1;

    while(fptr!=NULL && !found) {
      end=(char*)fptr+sizeof(metadata)+fptr->size;
      if(end<=(char*)block) {
        prev=fptr;
        fptr=fptr->next;
      }
      else found=1;
    }
    if(prev==NULL) *freeList=block;
    else prev->next=block;
    block->next=fptr;

    mergeList(freeList);
  }
  else printf("Error!! Double free called!!!\n");
}

void freeHeap(metadata** freeList, metadata* nums[], int n) {
  for(int i=0;i<n;i++) freeBlock(freeList,nums[i]);
}

void showFreeList(metadata* freeList) {
  metadata* temp=freeList;
  while(temp!=NULL) {
    printf("||Size of metadata: %u | Size of available: %u|| --> ",sizeof(metadata),temp->size);
    temp=temp->next;
  }
  printf("\n");
}

#include "template.h"

int main() {
  size_t request;
  int n, ch, j;
  metadata* freeList=initializeHeap();

  printf("How many requests do you want to make: "); scanf("%d",&n);
  metadata** nums=(metadata**)malloc(sizeof(metadata*)*n);
  
  for(int i=0;i<n;i++) {
    printf("\n\nOffset: %d\n",i);
    printf("Enter the number of bytes to be allocated: ");
    scanf("%u",&request);
    nums[i]=allocate(&freeList,request);

    printf("Do you want to clear any memory?\nEnter 1 to clear and 0 to continue with allocation:\n");
    scanf("%d",&ch);
    if(ch) {
      printf("Enter the offset of the memory block you want to free: ");
      scanf("%d",&j);
      freeBlock(&freeList,nums[j]);
    }
    printf("The free list upto now:\n");
    showFreeList(freeList);
  }
  
  freeHeap(&freeList,nums,n);
  free(freeList);
}

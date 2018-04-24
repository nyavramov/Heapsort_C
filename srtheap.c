#include "srt.h"	
#include <stdlib.h>

void checkCorrect(void *base, size_t nelem, size_t size);

void printArray(void *base, size_t nelem, size_t size){
    for(size_t j = 0; j < nelem; j++){
        char *anElement = (char *)base + size * j;
        
        if(j < nelem - 1) {
            printf("%f, ", *(double *)anElement);
        }
        
        if(j == nelem - 1){
            printf("%f", *(double *)anElement);
            printf("\n\n");
        }
    }
}

//Local function with the purpose of checking whether elements are sorted correctly
void checkCorrect(void *base, size_t nelem, size_t size){
    int x = 0;

    for(size_t j = 0; j < nelem - 1; j++){
        char *previous = (char *)base + size * j;
        char *next = (char *)base + size * (j+1);
        
        if(!(*(double *)previous <= *(double *)next)){
            x = 1;//Used as a boolean value
        }
    }
    
    if(x == 0){
        printf("\n\nSuccessful sort\n\n");
    } else {
        printf("\n\nKind of close but uhh not really..!\n\n");
    }
}

void maxHeapify(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *), size_t index);

void srtheap(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *)) {
    //Binary tree has no leaves after n/2 - 1 so we start there
    size_t startingPoint = (nelem / 2) - 1;

    //Create the initial heap. j < 18000000... is there to prevent a segfault. Fix this later.
    for(size_t j = startingPoint; j >= (double)0 && j < 18000000000000000000; j--){
        maxHeapify(base, nelem, size, compar, j);
    }
    
    //Remove largest elements of array 1 by one
    for(size_t index = nelem - 1; index >= (double)0 && index < 18000000000000000000; index--){
        char *firstElement = (char *)base;
        char *currentElement = (char *)base + (index * size);
    
        swap(firstElement, currentElement, size);
        maxHeapify(base, index, size, compar, 0);
    }
}

void maxHeapify(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *), size_t index){
    //Index of left child equation:  L(x) = 2 * index + 1
    size_t leftChildIndex = 2 * index + 1;
    
    //Index of right child equation: L(x) = 2 * index + 2
    size_t rightChildIndex = 2 * index + 2;
    
    char *currNode = (char *)base + index * size;
    char *greatest = currNode;
    char *left  = (char *)base + 2 * size * index + 1 * size;
    char *right = (char *)base + 2 * size * index + 2 * size;

    //Condition (leftChildIndex < nelem) ensures element exists in heap
    if(leftChildIndex < nelem && compar(left, greatest) > 0){
        greatest = left;
        index = leftChildIndex;
    }
    
    //Condition (rightChildIndex < nelem) ensures element exists in heap
    if (rightChildIndex < nelem && compar(right, greatest) > 0) {
        greatest = right;
        index = rightChildIndex;
    }
    
    if(greatest != currNode){
        swap(currNode, greatest, size);
        maxHeapify(base, nelem, size, compar, index);
    }
}




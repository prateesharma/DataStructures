/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include<string.h>
#include<stdio.h>
#include "heap.h"

/*define private macros used by the heap implementation */

#define heap_parent(npos)((int)(((npos)-1)/2))

#define heap_left(npos)(((npos)*2)+1)

#define heap_right(npos)(((npos)*2)+2)

void heap_init(Heap *heap, int(*compare)(const void *key1, const void*key2),void(*destroy)(void *data)){
  /*Initialize the heap*/
heap->size = 0;
heap->compare = compare;
heap->destroy = destroy;
heap->tree = NULL;

}

void person_init(Person *person, const char *name, int age, double height){
  //initializes the person
  person->name = name;
  person->age = age;
  person->height = height;
}

void heap_destroy(Heap *heap){
  int i;
  /*remove all nodes from the heap*/
  if(heap->destroy !=NULL){
    for(i=0;i<heap_size(heap);i++){ //loops through heap and calls destroy
      heap->destroy(heap->tree[i]);
    }
  }
  free(heap->tree);

  //memset(heap,0,sizeof(Heap));
}

int heap_insert(Heap *heap, const void *data){
  void *temp; //void pointer used for swap
  int ipos, ppos;

  //Allocate storage for the node
  if((temp=(void **)realloc(heap->tree,(heap_size(heap)+1)* sizeof(void *)))==NULL){
    return -1;
  }else{
    heap->tree = temp;
  }
  //insert the node after the last node
  heap->tree[heap_size(heap)] = (void *)data;

  //Heapify the tree by pushing the contents of the new node upward

  ipos = heap_size(heap); //sets position equal to the size of the heap
  ppos = heap_parent(ipos); //sets parent equal to the index of parent of ipos

  while(ipos >0 && heap->compare(heap->tree[ppos],heap->tree[ipos])<0){
    temp = heap->tree[ppos];
    heap->tree[ppos] = heap->tree[ipos];
    heap->tree[ipos] = temp;

    //move up one level in the tree to continue heapifying
    ipos = ppos;
    ppos = heap_parent(ipos);
  }
  //adjust the size of the heap to account for inserted node
  heap->size++;

  return 0;
}

int heap_extract(Heap *heap, void **data){
  
  void *save,*temp;
  int ipos, lpos, rpos,mpos;

  //do not allow extraction from an empty heap
  if(heap_size(heap)==0){
    return -1;
  }

  //extract the node at the top of the heap
  *data = heap->tree[0];
  // printf("This is the item we are removing: %s\n",((Person *)*data)->name);

  //Adjust the storage used by the heap

  save = heap->tree[heap_size(heap)-1];

  if(heap_size(heap)-1>0){
    if((temp = (void **)realloc(heap->tree,(heap_size(heap)-1)*sizeof(void *)))==NULL){
      return -1; //allocates memory
    }else{
      heap->tree = temp;
    }
    heap->size--; //decreases the size
  }else{
    //manage the heap when extracting the last node
    free(heap->tree);
    heap->tree = NULL;
    heap->size = 0;
    return 0;
  }
  //copy the last node to the top
  heap->tree[0] = save;

  //heapify the tree by pushing the contents of the new top downward
  ipos = 0;
  lpos = heap_left(ipos);
  rpos = heap_right(ipos);

  while(1){
    /*select the child to swap with the current node*/
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    if(lpos<heap_size(heap)&& heap->compare(heap->tree[lpos],heap->tree[ipos])>0){
      mpos = lpos; //checks compare function to see which value is greater
    }else{
      mpos = ipos;
    }
    if(rpos<heap_size(heap)&&heap->compare(heap->tree[rpos],heap->tree[mpos])>0){
      mpos = rpos;
    }
    if(mpos == ipos){
      break;
    }else{
      //Swap the contents of the current node and the selected child
      temp = heap->tree[mpos];
      heap->tree[mpos] = heap->tree[ipos];
      heap->tree[ipos] = temp;

      //move down one level in the tree to continue heapifying
      ipos = mpos;
    }

  }
  return 0;
}

int compare(const void *pKey1, const void *pKey2){
  Person *person1 = (Person *)pKey1;

  Person *person2 = (Person *)pKey2;
  // if(person1->age > person2->age){
  //   return -1;
  // }else{
  //   return 1;
  // }

  if(person1->height > person2->height){
    return -1;
  }else{
    return 1;
  }
  // if(strcmp(person1->name,person2->name)<0){
  //   return 1; //checks if the first name is less than the second
  // }else if(strcmp(person1->name,person2->name)>0){
  //   return -1;
  // }else{
  //   return 0;
  // }
}

void outputSorted(const Person people[], int numPeople, int (*compare)(const void *pey1, const void *pKey2)){
  Heap heap; //creates a heap
  heap_init(&heap,compare,free); //initializes the heap
  printf("This is the size of the heap: %d\n",heap.size
  );

  for(int i=0;i<numPeople;i++){ //loops through the people array
    heap_insert(&heap,&people[i]);
    printf("Just inserted element in heap: \n");
  }
    
  for(int j=0;j<numPeople;j++){
    printf("This is the item we are removing: %f\n",((Person *)heap.tree[0])->height);
    heap_extract(&heap,&heap.tree[0]);
  }

}
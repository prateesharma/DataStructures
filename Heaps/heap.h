#ifndef HEAP_H
#define HEAP_H

//define a struct for heap

typedef struct Heap_{
  int size;

  int(*compare)(const void *key1, const void *key2);
  void(*destroy)(void *data);

  void **tree; //array of void pointers
}Heap;


typedef struct Person_{
  const char *name;
  int age;
  double height;
}Person;
/*Public Interface*/
void heap_init(Heap *heap, int(*compare)(const void *key1, const void*key2),void(*destroy)(void *data));

void person_init(Person *person, const char *name, int age, double height);

int compare(const void *key1,const void *key2);

void heap_destroy(Heap *heap);

int heap_insert(Heap *heap, const void *data);

int heap_extract(Heap *heap, void **data);

void outputSorted(const Person people[],int numPeople,int (*compare)(const void *pkey1,const void *pkey2));

#define heap_size(heap)((heap)->size)

#endif


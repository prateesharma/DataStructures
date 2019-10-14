/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hw2header.h
 * Author: prateeshsharma
 *
 * Created on July 15, 2019, 5:07 PM
 */

#ifndef HW2HEADER_H
#define HW2HEADER_H

#include <stdlib.h>

#define list_data(l)((l)->data)

typedef struct ListElmt_{
    //listelement is going to have a data pointer and next pointer
    double data;
    struct ListElmt_ *next; //next pointer which points to next element
    
}ListElmt;


typedef struct List_{
    //list has a size, and a head and tail
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void* data);
    //destroy is a pointer to a function that takes a void pointer data and returns void
    
    ListElmt *head;
    ListElmt *tail;
    
    
}List;

void listInit(List *list, void (*destroy)(void *data));
//constructor for the list

void list_destroy(List *list);

List* appendTerm(List *list, double constant);

void display(List *list);

double evaluate(List *list, double x);


#define list_size(list)((list)->size)
//macro to get the list size

#define list_head(list)((list)->head)
//macro to get the head of the list

#define list_tail(list)((list)->tail)
//macro to get the tail of the list

#define list_is_head(list,element)((element)==(list)->head ? 1:0)
//checks if the element is the head of the list, 1 if true or 0 is false

#define list_is_tail(list, element)((element)->next==NULL ? 1:0)

#define list_is_data(element)((element)->data)

#define list_next(element)((element)->next)





#endif /* HW2HEADER_H */


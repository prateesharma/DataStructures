/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list.h
 * Author: prateeshsharma
 *
 * Created on July 7, 2019, 8:03 PM
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/*
 Singly-linked list element
 */

#define list_data(l) ((l)->data)

typedef struct ListElmt_{ 
    void *data; //void pointer data because we cant point it to whatever
                //kind of datatype that we want
    struct ListElmt_ *next; //next pointer which points to next element
    
}ListElmt;

/*
 * Singly-linked list
 */
typedef struct List_{
    int size; //number of elements that we want in the list
    
    int (*match)(const void *key1, const void *key2);
    void(*destroy)(void *data); //destroy is a pointer to a function that 
                                //takes a void pointer and returns void
    
    ListElmt *head;
    ListElmt *tail;
    
}List;

/*
 Public interface
 
 */

void list_init(List *list, void (*destroy)(void *data));
//a constructor for the list

int list_ins_next(List *list, ListElmt *element, const void *data);
//takes a list parameter, the pointer to element and a constant void parameter
//if return type is 0 then it is success

int list_rem_next(List *list, ListElmt *element, void **data);
//pointer to list, second parameter is the pointer to the next element
//third parameter is a pointer to a pointer allows caller to have a pointer to the pointer for the data that got removed

void list_destroy(List *list);

#define list_size(list)((list)->size)
//creates a function to access the size of the list

#define list_head(list)((list)->head)
//creates a function to access the head pointer of the list

#define list_tail(list)((list)->tail)
//creates a function to access the tail pointer

#define list_is_head(list, element)((element)==(list)->head ? 1 :0)
//returns true or false if the element is the head of the list

#define list_is_tail(element)((element)->next == NULL ? 1:0)
//returns true or false if the element is tail of the list if nextpointer is Null

#define list_is_data(element)((element)->data)
//takes an element pointer and gets the data in the element

#define list_next(element)((element)->next)
//takes an element and gets the next element




#endif /* LIST_H */


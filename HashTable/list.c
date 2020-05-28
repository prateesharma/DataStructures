/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list.c
 * Author: prateeshsharma
 *
 * Created on July 7, 2019, 8:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data)){
    //Initializes the list
    list->size = 0; //indicates list is empty
    list->destroy = destroy; //store the destroy pointer
    list->head = NULL; //set head and tail to null
    list->tail = NULL;
    
}

void list_destroy(List *list){
    void *data; 
    
    //remove each element
    while(list_size(list)>0){ //as long as there are elements in the list
        if(list_rem_next(list, NULL, (void **)&data) == 0 && list ->destroy != NULL){
            //going to remove the head and return a pointer to the data that we removed
            //checks if the list has a destroy function
            
            /*Call a user-defined function to free dynamically allocated data */
            list->destroy(data);
            
        }
        
    }
    /*No operations are allowed now, but clear the structure as a precaution */
    memset(list, 0, sizeof(List)); //safety net to make sure that the list is zerod out
    //probably don't need it
}

/*
 * 
 */

int list_ins_next(List *list, ListElmt *element, const void *data){
    
    ListElmt *new_element;
    //allocate storage for the element;
    if(((new_element) = (ListElmt *)malloc(sizeof(ListElmt))) == NULL){
        return -1;
    }

    
    //insert the element into the list
    new_element ->data = (void *)data;
    if(element == NULL){
        /*Handle insertion at the head of the list*/
        if(list_size(list)==0){ //if list is empty then new head is also tail
            list->tail = new_element; //sets tail as new element
        }
        new_element ->next = list->head; //new element's next pointer is old head
        list ->head = new_element; //lists head points to new element
        //lists head and tail are the same, head has a next poitner to null
        
    }else{

        if (element->next == NULL){
            list->tail = new_element;
        }
        new_element->next = element->next;
        element->next = new_element;
        
        
        
    }
    list ->size++;
    return 0;

}

int list_rem_next(List *list, ListElmt *element, void **data){
    ListElmt *old_element;
    
    if(list_size(list)==0){
        return -1; //checks if the size if 0 because you can't remove anything
    }
    /*remove the element from the list*/
    if(element == NULL){
        //handle removal from the head of list
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        
        if(list_size(list)==1){
            list->tail = NULL;
        }
    }else{
     //handle removal from somewhere other than the head
        if(element ->next == NULL){
            return -1;
            
        }
        *data = element->next->data;
        old_element = element ->next;
        element->next = element ->next->next;
        if(element->next == NULL){
            list->tail = element;
        }
        
    }
    //Free the storage allocated by the abstract data type
    free(old_element);
    
    //Adjust the size of the list to account for the removed element
    list->size --;
    return 0;
}





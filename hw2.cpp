/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hw2.cpp
 * Author: prateeshsharma
 *
 * Created on July 14, 2019, 8:30 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <iostream>

#include "list.h"

using namespace std;

/*
 * 
 */
void appendTerm(List *pPolynomial, void *constant){
    //function should insert at the end the value constant to pPolynomial
    ListElmt *element;
    pPolynomial ->tail = element;
    element->data = constant;
    element->next = NULL;
    
    
}

void list_init(List *list, void (*destroy)(void *data)){
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
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



int main(int argc, char** argv) {
    
}


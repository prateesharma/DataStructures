/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chtbl.c
 * Author: prateeshsharma
 *
 * Created on August 11, 2019, 1:45 PM
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "list.h"
#include "chtbl.h"

int chtbl_init(CHTbl *htbl, int buckets, int(*h)(const void *key,int a),
        int(*match)(const void *key1, const void *key2),void(*destroy)(void*data),
        double maxLoadFactor, double resizeMultiplier){
    int i;
    //checks if resizeMultiplier is greater than 1
    if(resizeMultiplier <=1){
        return -1;
    }
    //Allocate space for the hash table

    if((htbl->table = (List *)malloc(buckets * sizeof(List)))==NULL){
        printf("Could not allocate memory for table:  \n");
        return -1;
    }
    //initialize the buckets
    htbl->buckets = buckets;
    
    for(i=0;i<htbl->buckets;i++){
        list_init(&htbl->table[i],destroy);
    }

    //encapsulate the functions
    htbl->h = h;
    htbl->match = match;
    //htbl->destroy = destroy;
    
    //initializes the maxLoadFactor and resizeMultiplier
    htbl->maxLoadFactor = maxLoadFactor;
    htbl->resizeMultiplier = resizeMultiplier;
    //initialize the number of elements in the table
    
    htbl->size = 0;
    return 0;
}
/*
 * 
 */

void chtbl_destroy(CHTbl *htbl){
    int i;
    //destroy each bucket
    for(i = 0;i<htbl->buckets;i++){
        list_destroy(&htbl->table[i]);
    }
    
    //free storage allocated for the hash table
    free(htbl->table);
    
    //No operations are allowed now, but clear the structure as a precaution
    
    memset(htbl,0,sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl,const void*data){
    void *temp; //creates void pointer temp
    int bucket, retval; //creates int bucket and retval
    
    //Do nothing if the data is already in the table
    temp = (void*)data;
    
    if(chtbl_lookup(htbl, &temp)==0){ //checks if the value was already in table
        printf("The value was already in the table: %d\n", *(int *)temp);
        return 0;
    }
    
    //Hash the key
    bucket = htbl->h(data,htbl->buckets);
    
    //Insert the data into buckets
    
    if((retval = list_ins_next(&htbl->table[bucket],NULL,data))==0){

        htbl->size++; //increases the size
    }
    double currLoadFactor = (double)(htbl->size)/(htbl->buckets);
    if(currLoadFactor>htbl->maxLoadFactor){
        //if the load factor is greater than maxloadFactor
        int b = resize_table(htbl); //call resize function

        printf("buckets %d, elements %d, lf %f, max lf %f, resize multiplier %f \n",
                htbl->buckets, htbl->size,currLoadFactor, htbl->maxLoadFactor, htbl->resizeMultiplier);

        return retval; //return the retval

    }else{
      printf("buckets %d, elements %d, lf %f, max lf %f, resize multiplier %f \n",
              htbl->buckets, htbl->size,currLoadFactor, htbl->maxLoadFactor, htbl->resizeMultiplier);
      //otherwise print the values in the smaller hash table
    }
    return retval;
}


int chtbl_remove(CHTbl *htbl,void **data){
    ListElmt *element, *prev;
    int bucket;
    //Hash the key
    bucket = htbl->h(*data,htbl->buckets);
    
    //search for the data in the bucket
    prev = NULL;
    
    for(element = list_head(&htbl->table[bucket]);element !=NULL;element = list_next(element)){
        if(htbl->match(*data,list_data(element))){
            //remove the data from the bucket
            if(list_rem_next(&htbl->table[bucket],prev,data)==0){ //calls remove next
                htbl->size--; //reduce the size
                double currLoadFactor = htbl->size/htbl->buckets; //checks current load factor
                return 0;
            }else{
                return -1;
            }
        }
        prev = element;
    }
    //return that the data was not found
    return -1;
}



int chtbl_lookup(const CHTbl *htbl, void **data){
    ListElmt *element;
    int bucket;
    
    //Hash the key
    bucket = htbl->h(*data,htbl->buckets);
    
    //search for the data in the bucket
    for(element = list_head(&htbl->table[bucket]);element!=NULL;element=list_next(element)){
        if(htbl->match(*data,list_data(element))==0){
            //pass back the data from the table
            
            *data = list_data(element); //stores the data in the element as the pointer for data
            return 0;
        }
        
    }
    return -1;
}

//match function;
int match(const void*key1,const void *key2){

    if(*(int *)key1 == *(int *)key2){ //compares the two values and returns 0 if match
      return 0;
    }else{
      return -1;
    }

}





int resize_table(CHTbl *htbl){
    CHTbl resize; //creates a chained hash table
    int newsize = (htbl->buckets)*(htbl->resizeMultiplier); //sets the new size for the resize
    resize.buckets = newsize;
    chtbl_init(&resize,newsize,h,match,NULL,htbl->maxLoadFactor,htbl->resizeMultiplier); //initializes the table
    
    ListElmt *element;
    ListElmt *newelement; //creates two ListElmt to loop through the list
    
    for(int i=0;i<htbl->buckets;i++){ //loop through the buckets
      for(element = list_head(&htbl->table[i]);element!=NULL;element=list_next(element)){ //loop through the list
        chtbl_insert(&resize,element->data); //inserts the data in resize
      }
    }

    for(int j=0;j<resize.buckets;j++){ //loop through the buckets
      for(newelement = resize.table[j].head;newelement!=NULL;newelement=newelement->next){ //loop through tresize

        chtbl_remove(htbl,&newelement->data); //remoes the data from the old list
      }
    }
    return 0;
    
}


int h(const void *key, int numbucket){
    //multiplication method
    int code = *(int *)key; //gets the code of the key which is an int
    int m = numbucket; //creates number of buckets
    double a = .618; //A value of .618
    int bucket = floor(m*fmod(code*a,1.0)); //multiplication method for getting new key

    return bucket;
}


int main(int argc, char** argv) {
    CHTbl htbl; //creates a hash table
    int buckets = 2; //creates number of buckets
    double maxLoadFactor = 2; //creates max load factor
    double resizeMultiplier = 2; //creates resie multiplier
    //initializes the table
    chtbl_init(&htbl, buckets, h,match,NULL,maxLoadFactor, resizeMultiplier);
    int a = 2; //inserts values
    chtbl_insert(&htbl,&a);
    int b =3;
    chtbl_insert(&htbl,&b);
    int c = 10;
    chtbl_insert(&htbl,&c);



    int d = 11;
    chtbl_insert(&htbl,&d);
    int e=11;
    chtbl_insert(&htbl,&e);
    int f=12;
    chtbl_insert(&htbl,&f);
    
    int *notThere;
    *notThere= 8;
    
    if(chtbl_lookup(&htbl,(void **)&notThere)==-1){
        printf("The value was not in the resized table: \n");
    }
    int *isThere;
    *isThere = 11;
    
    if(chtbl_lookup(&htbl,(void **)&isThere)==-1){
        printf("Found the value after the resize: \n");
    }

    
    return(EXIT_SUCCESS);
}


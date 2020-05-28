/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chtbl.h
 * Author: prateeshsharma
 *
 * Created on August 11, 2019, 1:38 PM
 */

#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

typedef struct CHTbl_{
    int buckets;
    
    int(*h)(const void *key, int numbuckets);
    int(*match)(const void *key1,const void *key2);
    void(*destroy)(void *data);
    
    int size;
    List *table;
    
    double maxLoadFactor;
    double resizeMultiplier;
}CHTbl;

/*Public Interface*/

int chtbl_init(CHTbl *htbl, int buckets, int(*h)(const void *key,int a),
        int(*match)(const void*key1,const void*key2),void(*destroy)(void *data),
        double maxLoadFactor,double resizeMultiplier);

void chtbl_destroy(CHTbl *htbl);

int chtbl_insert(CHTbl *htbl, const void *data);

int chtbl_remove(CHTbl *htbl, void **data);

int chtbl_lookup(const CHTbl *htbl, void **data);

int resize_table(CHTbl *htbl);

int match(const void *key1, const void *key2);

int h(const void *key, int numbucket);


#define chtbl_size(htbl)((htbl)->size);


#endif /* CHTBL_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: prateeshsharma
 *
 * Created on August 27, 2019, 7:19 PM
 */

#include <stdio.h>
#include <string.h>

#include "heap.h"

int main(void) {

  Person p1 = {"james",5,10};
  person_init(&p1,"james",5,10);
  Person p2 = {"prateesh",6,11};
  person_init(&p2,"prateesh",6,11);
  Person p3 = {"matt",7,12};
  person_init(&p3,"matt",7,12);
  Person p4 = {"quan",12,6};
  person_init(&p4,"quan",12,6);
  Person p5 = {"jeint",1,10};
  person_init(&p5,"pdlfd",1,10);
  // Person p6 = {"asdf",0,23};
  // person_init(&p6,"asdf",0,23);

  Person person[] = {p1,p2,p3,p4,p5};


  outputSorted(person,5,compare);
  printf("Finished : \n");

}


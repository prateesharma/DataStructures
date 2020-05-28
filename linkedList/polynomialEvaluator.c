/******************************************************************************


 *  HW2.c
 * Prateesh Sharma
 * 
*******************************************************************************/
#include <stdio.h>
#include <math.h>

#include "hw2header.h"


void list_init(List *pPolynomial, void (*destroy)(void *data)){
    pPolynomial->size = 0; //initializes size and a destroy function
    pPolynomial->destroy = destroy;
    pPolynomial->head = NULL;//initializes head and tail pointer
    pPolynomial->tail = NULL;
    
}

void list_destroy(List *pPolynomial){
    
    ListElmt *next; //creates a next pointer for ListElmt
    for(ListElmt *curr = pPolynomial->head; curr; curr=next){
        next = curr->next; //sets next pointer to the next element from current
        free(curr); //frees current node
        pPolynomial->size --;//reduces size
    }
}



List* appendTerm(List *pPolynomial, double constant){
//inserting value at the end of the list
    ListElmt *element; //creates a pointer of type ListElmt
    element = (ListElmt *)malloc(sizeof(ListElmt)); //creates memory for size ListElmt
    if(element == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n"); 
        exit(0); //checks if there is an element otherwise exits function
    }
    element->data = constant; //sets the constant as the data in element
    if(pPolynomial->size == 0){
        //if there was no head
        
        pPolynomial->head = element; //set head pointer of list to listelement
        pPolynomial->tail = element; //set tail pointer of list to listelement
        element->next = NULL; //next pointer of element is NULL
        
    }
    else{
        //if there is already a head
        pPolynomial->tail->next = element;//tail's next pointer is now element
        pPolynomial->tail = pPolynomial->tail->next;//tail pointer is now at newly inserted element
        
        element->next = NULL; //next pointer of the element is null    
    }
    pPolynomial->size++; //increments size

    return pPolynomial; //returns the list
    free(element); //frees element
}

void display(List *pPolynomial){
    ListElmt *tmp; //creates a ListElmt pointer tmp
    int xsize = pPolynomial->size; //creates a local variable xsize
    tmp = pPolynomial->head; //sets tmp as the head pointer
    printf("%.2fx^%d",tmp->data, xsize-1); // prints the head of the polynomial
    while(tmp->next != NULL && xsize >0){
      tmp=tmp->next; //sets next pointer to tmp
      xsize--; //decrements size
        if(tmp->data >0 && xsize-1!=0){
          printf("+%.2fx^%d", tmp->data, xsize-1); // prints positive elements except last element
        }else if(tmp->data <0 && xsize-1!=0){ //prints negative elements except last element
          printf("%.2fx^%d",tmp->data, xsize-1);
        }else if(xsize-1==0 && tmp->data>0){//prints last element if positive
          printf("+%.2f", tmp->data);
        }else if(xsize-1==0 && tmp->data<0){//prints last element if negative
          printf("%.2f", tmp->data);
        }
  }
  printf("\n");
}
     

double evaluate(List *pPolynomial, double x){
  ListElmt *temp; //creates ListELmt pointer temp
  double answer = 0; //creates local variable answer for result
  int size = pPolynomial->size; //sets size as the size of the list
  temp = pPolynomial->head;//sets temp to the head pointer
  
  while(temp != NULL && size >=0){
    answer +=(temp->data)*pow(x,size-1); //evaluates the polynomial element by element
    temp = temp->next; //goes to the next list element
    size--; //decreases the size
  }
  printf("The result is %.2f \n", answer);
  return answer;

}


int main() {
    List* listOfInts; //creates a List pointer
    ListElmt *pElmt; //creates a List Element pointer
    

    list_init(listOfInts, free); //initializes the list
    appendTerm(listOfInts, 1); //appends the first element of polynomial
    appendTerm(listOfInts,1); //appends to the list
    display(listOfInts); //calls display function
    if(evaluate(listOfInts,1.0) - 2.0 < .0000001){ //checks to see the result is 2
      printf("x+1.0 works \n");
      //return 0;
    }
    //free(&listOfInts);
    list_destroy(listOfInts); //destroys the list

    list_init(listOfInts, free); //initializes the list
    appendTerm(listOfInts, 1); //appends elements
    appendTerm(listOfInts, 0);
    appendTerm(listOfInts, -1);
    display(listOfInts);//calls display function
    if(evaluate(listOfInts,2.03)- 3.1209< .0000001){ //checks if value is 3.1209
      printf("x^2-1.0 works \n");
    }
    list_destroy(listOfInts); //destroys list

    list_init(listOfInts, free); //initializes list
    appendTerm(listOfInts, -3); //appends to list
    appendTerm(listOfInts, .5);
    appendTerm(listOfInts, -2.0);
    appendTerm(listOfInts,0);
    display(listOfInts); //displays list

    if(evaluate(listOfInts,05.0)- -372.5 < .0000001){ //checks if value is -372.5
      printf("It works \n");
    }

    list_destroy(listOfInts); //destroys list
    
    list_init(listOfInts, free); //initializes list
    appendTerm(listOfInts, -.3125); //appends list
    appendTerm(listOfInts, 0);
    appendTerm(listOfInts, -9.915);
    appendTerm(listOfInts, -7.75);
    appendTerm(listOfInts,-40);
    display(listOfInts); //displays list

    if(evaluate(listOfInts,123.45)- -72731671.686258 < .0000001){
      printf("It works \n"); //checks if value is correct
    }
    return (EXIT_SUCCESS);
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   traverse.c
 * Author: prateeshsharma
 *
 * Created on August 18, 2019, 7:47 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "traverse.h"

/*
 * 
 */

int preorder(const BiTreeNode *node, List *list){
    //Load the list with a preorder listing of tree
    if(!bitree_is_eob(node)){
      printf("This is the node: %d\n",*(int *)node->data);
        if(list_ins_next(list,list_tail(list),bitree_data(node))!=0){
          printf("was not able to insert: \n\n\n");
            return -1;
        }
      printf("Just inserted the node into a list: \n");
        if(!bitree_is_eob(bitree_left(node))){
      printf("Just checked if the node is not at end of a branch in left tree: \n");
          if(preorder(bitree_left(node),list)!=0){
            printf("Was not able to call the function: \n\n\n");
            return -1;
          }
          printf("Just recursively called the function to move to the next node in left tree \n");
      }if(!bitree_is_eob(bitree_right(node))){
          printf("Just checked if the right node is not at end of branch in right tree: \n");
          if(preorder(bitree_right(node),list) !=0){
            printf("Was not able to call the function: \n\n\n");
            return -1;
          }
          printf("Just recursively called the function to move to next node: in right tree \n");
        }
    }


    return 0;
}



int inorder(const BiTreeNode *node, List *list){
    if(!bitree_is_eob(node)){
        if(!bitree_is_eob(bitree_left(node))){
          printf("This node: %d was not at the end of branch: \n",*(int *)node->data);
            if(inorder(bitree_left(node),list)!=0){
                return -1;
            }
        }if(list_ins_next(list, list_tail(list),bitree_data(node))!=0){
            return -1;
        
        }printf("This is the node inorder: %d\n",*(int *)node->data);
        if(!bitree_is_eob(bitree_right(node))){
          printf("This node: %d was not at the end of branch: \n",*(int *)node->data);
            if(inorder(bitree_right(node),list)!=0){
                return -1;
            }

        }
    }
    return 0;
}


int postorder(const BiTreeNode *node, List *list){
    if(!bitree_is_eob(node)){
        if(!bitree_is_eob(bitree_left(node))){
          printf("This node: %d was not at the end of branch: \n",*(int *)node->data);
            if(postorder(bitree_left(node),list)!=0){
                return -1;
            }

        }if(!bitree_is_eob(bitree_right(node))){
          printf("This node %d was not at the end of the branch in the right tree: \n",*(int *)node->data);
            if(postorder(bitree_right(node),list)!=0){
                return -1;
            }
        }if(list_ins_next(list, list_tail(list),bitree_data(node))!=0){
            return -1;
        }
        printf("This is the node postorder: %d\n",*(int *)node->data);

    }
    return 0;
}



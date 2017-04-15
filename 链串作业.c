//
//  main.c
//  链串作业
//
//  Created by Alchemist on 2017/4/3.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//
//x, y两个单链表串，找出x中第一个不在y中出现的字符



#include <stdio.h>
#include <stdlib.h>


typedef char ElementType;

typedef enum{
    ERROR = 1,
    OK = 0
}Status;

typedef struct Node {
    ElementType data;
    struct Node *next;
    
}LNode, *LinkedList;



Status LinkListInit(LinkedList* L);
Status LinkedListCreate1(LinkedList* L, ElementType a[], int n);
void LinkedListTraverse(LinkedList* L);




Status LinkListInit(LinkedList* L){
    *L = (LinkedList) malloc(sizeof(ElementType));
    if (*L == NULL) {
        printf("申请空间分配失败");
        return 1;
    }
    (*L)->data = ' ';
    (*L) -> next = NULL;
    return 0;
}




Status LinkedListCreate1(LinkedList* L, ElementType a[], int n){
    LinkedList p;
    
    LinkListInit(L);
    
    for (int i = 0; i < n; i++){
        p = (LinkedList) malloc(sizeof(LNode));
        if (p == NULL){
            printf("分配空间失败");
            return 1;
        }
        p -> data = a[i];
        //此时包含了末尾next的null化
        p -> next = (*L) -> next;
        (*L) -> next = p;
    }
    
    return 0;
}



void LinkedListTraverse(LinkedList* L){
    LinkedList p;
    p = (*L)->next;
    
    while(p != NULL){
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}



ElementType findChar(LinkedList* X, LinkedList* Y){
    LinkedList px, py;
    
    
    for (px = (*X)->next; px != NULL; px = px ->next) {
        py = (*Y)->next;
        while (py != NULL) {
            if (px->data == py->data){
                break;
            }
            else{
                py = py->next;
            }
            
        }
        if (py == NULL){
            return px->data;
        }
        
    }
    exit(0);
}





int main(){
    LinkedList x, y;
    char cx[3] = {'a','f','e'}, cy[3] = {'e', 'b', 'c'};
    
    LinkedListCreate1(&x, cx, 3);
    LinkedListTraverse(&x);
    LinkedListCreate1(&y, cy, 3);
    LinkedListTraverse(&y);
    
    printf("char: %c\n", findChar(&x, &y));
    printf("what");
    
    return 1;
}
























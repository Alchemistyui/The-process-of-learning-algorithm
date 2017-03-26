//
//  main.c
//  反序合并单链表
//
//  Created by Alchemist on 17/3/15.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;


typedef struct Node {
    ElementType data;
    struct Node *next;
    
}LNode, *LinkedList;



void LinkListInit(LinkedList* L){
    *L = (LinkedList) malloc(sizeof(ElementType));
    if (L == NULL) {
        printf("申请空间分配失败");
        
    }
    (*L) -> next = NULL;
    
}

void LinkedListInsert(LinkedList* L, ElementType elem, LinkedList p){
    LinkedList q;
    q = (LinkedList) malloc(sizeof(LNode));
    
    if (q == NULL){
        printf("分配失败");
    }
    q -> data = elem;
    
    p -> next = q;
    q -> next = NULL;
    
}


LinkedList    LinkedListGet(LinkedList* L, int i){
    LinkedList p;
    int j = 0;
    
    if (i <= 0){
        printf("the value of i is illegal");
        exit(0);
    }
    if (L == NULL){
        printf("list is empty");
        exit(0);
    }
    
    p = (*L) -> next;
    while ((p != NULL) && (j < i)) {
        p = p -> next;
        j++;
    }
    return p;
}




void Bubble(LinkedList* L){
    int i,j,temp;
    LinkedList p = *L;
    int count = 0;
    while(p -> next != NULL)
    {
        count++;
        p = p->next;
    }
    
    for(i=0;i<count-1;i++) /* 冒泡法排序 */
    {
        p = (*L) -> next;
        for(j=0;j<count-i-1;j++)
        {
            if(p->data < p->next->data)
            {
                temp=p->data;
                p->data = p->next->data;
                p->next->data=temp;
            }
            p = p->next;
        }
    }

}


LinkedList LinkedListSort (LinkedList* La, LinkedList* Lb){
    LinkedList Lc, pa;
    
    Lc = *Lb;
    pa = (*La) -> next;
    
    while (pa -> next != NULL) {
        pa = pa -> next;
    }
    
    pa -> next = (*Lb) -> next;
    
    Bubble(La);
    
    Lc = *La;
    
    free(*Lb);
    return Lc;
    
}



int main() {
    LinkedList La, Lb, Lc, p, q, pc;
    
    LinkListInit(&La);
    LinkListInit(&Lb);
    LinkListInit(&Lc);
    
    
    p = La;
    q = Lb;
    pc = Lc;
    
    for (int i = 1; i <= 5; i++){
        LinkedListInsert(&La, i, p);
        printf("%d", p -> next -> data);
        p = p -> next;
    }
    
    
    for (int i = 6; i <= 10; i++){
        LinkedListInsert(&Lb, i, q);
        printf("%d", q -> next -> data);
        q = q -> next;
    }
    printf("\n");
    Lc = LinkedListSort(&La, &Lb);
    pc = Lc;
    for (int i = 1; i <= 10; i++){
        printf("%d\n", pc -> next -> data);
        pc = pc -> next;
    }
    
}
























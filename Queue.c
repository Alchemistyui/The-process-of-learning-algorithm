//
//  main.c
//  队列
//
//  Created by Alchemist on 17/3/17.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef int ElementType;


typedef struct Node{
    ElementType data[MAX_SIZE];
    int front, rear;
}CirQueue;


//此处采用的是循环队列。。。。



void CirQueueInit (CirQueue* Q);
bool CirQueueIsEmpty (CirQueue Q);
void EnCirQueue (CirQueue* Q, ElementType elem);
ElementType DeCirQueue (CirQueue* Q);
void CirQueueTraverse (CirQueue* Q);



void CirQueueInit (CirQueue* Q){
    Q -> front = Q -> rear = 0;
}


bool CirQueueIsEmpty (CirQueue Q){
    return (Q.front == Q.rear);
}



void EnCirQueue (CirQueue* Q, ElementType elem) {
    
    if ((Q -> rear + 1) % MAX_SIZE == Q -> front){
        printf(" queue is full");
        exit(0);
    }
    //这里要注意不能简单的加一而要模运算一下
    Q -> rear = (Q -> rear + 1) % MAX_SIZE;
    Q -> data[Q -> rear] = elem;
    
}



ElementType DeCirQueue (CirQueue* Q){
    
    if ((Q -> rear) == (Q -> front)){
        printf(" queue is empty");
        exit(0);
    }
    //同上
    Q -> front = (Q -> front + 1) % MAX_SIZE;
    return Q -> data[Q -> front];
}


void CirQueueTraverse (CirQueue* Q){
    
    if ((Q -> rear) == (Q -> front)){
        printf(" queue is empty");
        exit(0);
    }
    
    for(int i = Q->front + 1; i <= Q->rear; i++){
        printf(" %d\n", Q->data[i]);
    }
}




//-------------------------------------------------------
//链队列
//结点结构


typedef  struct Node2{
    ElementType data;
    struct Node2* next;
}LQNode, *LinkedQNode;

//封装的链式队列

typedef  struct Queue {
    LinkedQNode front;
    LinkedQNode rear;
}LQueue, *LinkedQueue;



void LinkedQueueInit (LinkedQueue Q);
bool LinkedQueueIsEmpty (LinkedQueue Q);
void EnLinkedQueue (LinkedQueue Q, ElementType elem);
ElementType DeLinkedQueue (LinkedQueue Q);
void LinkedQueueTraverse (LinkedQueue Q);



void LinkedQueueInit (LinkedQueue Q){
    LinkedQNode p;
    
    p = (LinkedQNode) malloc(sizeof(LQNode));
    
    if ( p == NULL){
        printf("malloc fail");
        exit(0);
    }
    p -> next = NULL;
    Q -> front = p;
    Q -> rear = p;
    
}


bool LinkedQueueIsEmpty (LinkedQueue Q){
    return (Q -> front) == (Q -> rear);
}


void EnLinkedQueue (LinkedQueue Q, ElementType elem){
    LinkedQNode p;
    
    p = (LinkedQNode) malloc(sizeof(LQNode));
    if (p == NULL){
        printf("malloc fail");
        exit(0);
    }
    p -> data = elem;
    p -> next = NULL;
    
    Q -> rear -> next = p;
    Q -> rear = p;
}

//记得判空！******
ElementType DeLinkedQueue (LinkedQueue Q){
    LinkedQNode q;
    int elem;
    
    if (Q -> front == Q -> rear){
        printf("queue is empty");
        exit(0);
    }
    
    //注意此时Q -> front指向的是头结点
    q = Q -> front -> next;
    Q -> front -> next=q -> next;
    
    elem = q -> data;
    free(q);
    
    //不要忘了删后数组为空的情况
    if (Q -> front -> next == NULL){
        Q -> rear = Q -> front;
    }
    
    return elem;
}



void LinkedQueueTraverse (LinkedQueue Q){
    
    if (LinkedQueueIsEmpty(Q)){
        printf("queue is empty");
        exit(0);
    }
    
    for (LinkedQNode p = Q->front -> next; p != NULL; p = p->next){
        printf(" %d\n", p->data);
    }
}





int main() {
    CirQueue Q;
    LQueue   LQ;
    
    CirQueueInit(&Q);
    printf("empty? %d\n", CirQueueIsEmpty(Q));
    
    for (int i = 0; i < 4; i++){
        EnCirQueue(&Q, i);
    }
    CirQueueTraverse(&Q);
    DeCirQueue(&Q);
    CirQueueTraverse(&Q);
    printf("----------------\n");
    //-----------------------------------------------------
    
    LinkedQueueInit(&LQ);
    printf("empty? %d\n", LinkedQueueIsEmpty(&LQ));
    for (int i = 0; i < 4; i++){
        EnLinkedQueue(&LQ, i);
    }
    LinkedQueueTraverse(&LQ);
    DeLinkedQueue(&LQ);
    LinkedQueueTraverse(&LQ);
}

















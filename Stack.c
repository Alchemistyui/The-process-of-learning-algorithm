//
//  main.c
//  栈
//
//  Created by Alchemist on 17/3/16.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef int ElementType;


typedef struct Node {
    ElementType data[MAX_SIZE];
    int top;
}SeqStack;





void SeqStackInit (SeqStack* S);
bool IsEmpty (SeqStack* S);
void Push (SeqStack* S, ElementType elem);
ElementType Pop (SeqStack* S);
ElementType GetTop (SeqStack* S);





void SeqStackInit (SeqStack* S) {
    (*S).top = -1;
}

bool IsEmpty (SeqStack* S){
    if ((*S).top == -1){
        return true;
    }
    else
        return false;
}


void Push (SeqStack* S, ElementType elem){
    if ((*S).top == MAX_SIZE - 1){
        printf("stack is full");
        exit(0);
    }
    (*S).top++;
    (*S).data[(*S).top] = elem;
}

ElementType Pop (SeqStack* S){
    int elem;
    if (IsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    elem = (*S).data[(*S).top];
    (*S).top--;
    return elem;
}



ElementType GetTop (SeqStack* S){
    if (IsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    return (*S).data[(*S).top];
}

//---------------------------------------------------
//链栈

typedef struct Node2{
    ElementType data;
    struct Node2* next;
}LStackNode;

typedef struct{
    LStackNode* top;
}LinkedStack;





void LinkedStackInit (LinkedStack* S);
bool LinkedStackIsEmpty (LinkedStack* S);
void LinkedStakePush (LinkedStack* S, ElementType elem);
ElementType LinkedStackPop (LinkedStack* S);
ElementType LinkedStackGetTop (LinkedStack* S);





void LinkedStackInit (LinkedStack* S){
    S -> top = NULL;
}


bool LinkedStackIsEmpty (LinkedStack* S){
    if (S -> top == NULL){
        return true;
    }
    return false;
}


void LinkedStakePush (LinkedStack* S, ElementType elem){
    //注意此处p的类型不能是Linkedstack，因为前面这个是一个结构体
    LStackNode * p;
    
    p = (LStackNode *) malloc(sizeof(LStackNode));
    if (p == NULL){
        printf("malloc false");
        exit(0);
    }
    
    p -> data = elem;
    p -> next = S -> top;
    S -> top  = p;
}



ElementType LinkedStackGetTop (LinkedStack* S){
    if (LinkedStackIsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    return S->top->data;
}





ElementType LinkedStackPop (LinkedStack* S){
    int elem;
    LStackNode* p;
    
    if (LinkedStackIsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    elem = S -> top -> data;
    p = S -> top;
    S -> top = S -> top -> next;
    //free超重要！！一定不能忘,结点什么的都要free掉
    free(p);
    
    return elem;
}







int main (){
    SeqStack S;
    LinkedStack LS;
    
    SeqStackInit(&S);
    printf("empty?: %d\n", IsEmpty(&S));
    for (int i = 0; i <4; i++){
        Push(&S, i);
        printf("top element: %d\n", GetTop(&S));
    }
    Pop(&S);
    printf("now top: %d\n", GetTop(&S));
    printf("empty?: %d\n", IsEmpty(&S));
    printf("---------\n");
    //----------------------------------------------------------------
    
    LinkedStackInit(&LS);
    printf("empty?: %d\n", LinkedStackIsEmpty(&LS));
    
    for (int i = 0; i <4; i++){
        LinkedStakePush(&LS, i);
        printf("top element: %d\n", LinkedStackGetTop(&LS));
    }
    LinkedStackPop(&LS);
    printf("now top: %d\n", LinkedStackGetTop(&LS));
    printf("empty?: %d\n", LinkedStackIsEmpty(&LS));
    
}














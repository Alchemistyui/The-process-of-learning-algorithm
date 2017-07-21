//
//  main.c
//  树
//
//  Created by Alchemist on 2017/4/3.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef char ElementType;

typedef struct Node{
    ElementType data;
    struct Node *lchild, *rchild;
}BinNode, *BinTree;


//链栈------

typedef struct Node2{
    BinTree data;
    struct Node2* next;
}LStackNode;

typedef struct{
    LStackNode* top;
}LinkedStack;
//----------

//顺序栈
typedef struct Node3 {
    int data[MAX_SIZE];
    int top;
}SeqStack;



//栈的内容---------------------------------------

void LinkedStackInit (LinkedStack* S){
    S -> top = NULL;
}


bool LinkedStackIsEmpty (LinkedStack* S){
    if (S -> top == NULL){
        return true;
    }
    return false;
}


void LinkedStakePush (LinkedStack* S, BinTree BT){
    //注意此处p的类型不能是Linkedstack，因为前面这个是一个结构体
    LStackNode * p;
    
    p = (LStackNode *) malloc(sizeof(LStackNode));
    if (p == NULL){
        printf("malloc false");
        exit(0);
    }
    
    p -> data = BT;
    p -> next = S -> top;
    S -> top  = p;
}




BinTree LinkedStackGetTop (LinkedStack* S){
    if (LinkedStackIsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    return S->top->data;
}



BinTree LinkedStackPop (LinkedStack* S){
    BinTree elem;
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




bool IsEmpty (SeqStack* S){
    if ((*S).top == -1){
        return true;
    }
    else
        return false;
}



void Push (SeqStack* S, int elem){
    if ((*S).top == MAX_SIZE - 1){
        printf("stack is full");
        exit(0);
    }
    (*S).top++;
    (*S).data[(*S).top] = elem;
}


int Pop (SeqStack* S){
    int elem;
    if (IsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    elem = (*S).data[(*S).top];
    (*S).top--;
    return elem;
}



int GetTop (SeqStack* S){
    if (IsEmpty(S)){
        printf("stack is empty");
        exit(0);
    }
    
    return (*S).data[(*S).top];
}


//------------------------------------------




//前序递归遍历:记得判空
void PreTraverse (BinTree BT){
    
    if (BT){
        printf("%c ", BT->data);
        PreTraverse(BT->lchild);
        PreTraverse(BT->rchild);
    }
}

//其余递归遍历相同



//非递归遍历

void PreOderTraverse (BinTree BT){
    LinkedStack S;
    BinTree p = BT;
    
    LinkedStackInit(&S);
    
    while (p != NULL || !LinkedStackIsEmpty(&S)){
        
        if (p != NULL){
            printf("%c ", p->data);
            LinkedStakePush(&S, p);
            p = p->lchild;
        }
        else {
            p = LinkedStackPop(&S);
            p = p->rchild;
        }
        
    }
    
}



void InOrderTraverse (BinTree BT){
    LinkedStack S;
    BinTree p = BT;
    
    LinkedStackInit(&S);
    
    while (p != NULL || !LinkedStackIsEmpty(&S)){
        
        if (p != NULL){
            LinkedStakePush(&S, p);
            p = p->lchild;
        }
        else {
            p = LinkedStackPop(&S);
            printf("%c ", p->data);
            p = p->rchild;
        }
        
    }
}


void PostOrderTraverse (BinTree BT){
    LinkedStack S;
    SeqStack tag;
    BinTree p = BT;
    
    LinkedStackInit(&S);
    
    while (p != NULL || !LinkedStackIsEmpty(&S)){
        while (p != NULL){
            LinkedStakePush(&S, p);
            Push(&tag, 0);
            p = p->lchild;
        }
        
        if (!LinkedStackIsEmpty(&S)){
            if (GetTop(&tag) == 1){
                p = LinkedStackPop(&S);
                printf("%c ", p->data);
                Pop(&tag);
            }
            else {
                p = LinkedStackGetTop(&S);
                if (!LinkedStackIsEmpty(&S)){
                    p = p->rchild;
                    Pop(&tag);
                    Push(&tag, 1);
                }
            }
        }
    }
    
}
























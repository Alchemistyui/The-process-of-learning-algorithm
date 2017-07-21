//
//  main.c
//  树递归作业
//
//  Created by Alchemist on 2017/4/23.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#define MAX_DEPTH 20

typedef char ElementType;

typedef struct Node{
    ElementType data;
    struct Node *lchild, *rchild;
}BinNode, *BinTree;


void nodeCount(BinTree T,int depth, int a[]){
    
    if (T) {
        a[depth]++;
    }
    
    nodeCount(T->lchild, depth + 1, a);
    nodeCount(T->rchild, depth + 1, a);
    
}//层数


void PreTraverse (BinTree BT){
    
    if (BT){
        printf("%c ", BT->data);
        PreTraverse(BT->lchild);
        PreTraverse(BT->rchild);
    }
}

int isEqual(BinTree T1, BinTree T2) {
    
    if (T1 && T2){
        if (T1->lchild != T2->lchild || T1->rchild != T2->rchild){
            printf(" not equal");
            return 1;
        }
        isEqual(T1->lchild, T2->lchild);
        isEqual(T1->rchild, T2->rchild);
    }
    
   
    return 0;
}




int main() {
    BinTree T = NULL;
    int a[MAX_DEPTH];
    
    createTree(T);
    nodeCount(T, 1, a);
}













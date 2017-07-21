//
//  main.c
//  好友作业
//
//  Created by Alchemist on 2017/5/28.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//


//用来查找a用户与c用户是否是二重好友：即a为b的好友，c为b的好友，但a，c不为好友
#include <stdio.h>

#define MAX_VERTEX 1000
#define ID int

//普通结点
typedef struct node{
    ID adjvex;                            //尾域
    struct node *nextArc;       //链域
}EdgeNode;

//表头结点
typedef struct vnode{
    ID vexdata;                     //数据域
    EdgeNode *firstArc;       //边表头指针
}VertexNode;

//邻接表
typedef struct{
    VertexNode vertex[MAX_VERTEX];
    int vexnum, arcnum;                    //图中当前顶点数和边数
}AdjList;


int TwoDimentionFriend (AdjList *O, ID a, ID b) {
    EdgeNode *p, *q;
    p = O->vertex[a].firstArc;
    ID c;
    
    for ( ; p != NULL; p = p ->nextArc){
        c = p->adjvex;
        q = O->vertex[c].firstArc;
        
        for (; q != NULL; q = q->nextArc) {
            if (q->adjvex == b){
                return 1;
            }
        }
    }
    
    return 0;
}















//
//  main.c
//  实验3
//
//  Created by Alchemist on 2017/5/29.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 10
#define MAX_EDGE 20


typedef struct {
    int vexh;
    int vext;
    int weight;
    int flag;
}Edge;


typedef  struct {
    int vex[MAX_VEX];
    Edge edge[MAX_EDGE];
    int v, e;
}Graph;

/*
void CreatGraph (Graph *G) {
    
    printf("input vexNum & edgeNum:\n");
    scanf("%d %d", &(G->v), &(G->e));
    
    printf("input vex:\n");
    for (int i = 0; i < G->v; i++) {
        scanf("%d", &(G->vex[i]));
        
    }
    
    printf("input vexh & vext & weight of edge:\n");
    for (int i = 0; i < G->e; i++) {
        scanf("%d %d %d", &(G->edge[i].vexh), &(G->edge[i].vext), &(G->edge[i].weight));
        G->edge[i].flag = 0;
    }
}
*/

void CreatGraph (Graph *G) {
    FILE* fp;
    
    fp=fopen("/Users/ryshen/Desktop/test.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        exit(0);
    }
    
    fscanf(fp, "%d %d", &(G->v), &(G->e));
    
    for (int i = 0; i < G->v; i++) {
        fscanf(fp, "%d", &(G->vex[i]));
    }
    
    for (int i = 0; i < G->e; i++) {
        fscanf(fp, "%d %d %d", &(G->edge[i].vexh), &(G->edge[i].vext), &(G->edge[i].weight));
        G->edge[i].flag = 0;
    }

    fclose(fp);
}


void Kruskal(Graph *G, Graph *M) {
    Edge *minEdge = NULL;
    int i, j = 0, k;
    int set[MAX_VEX];
    
    
    for (i = 0; i < G->v; i++) {
        set[i] = i;
    }
    
    
    M->v = G->v;
    for (i = 0; i < G->v; i++) {
        M->vex[i] = G->vex[i];
    }
    
    for (i = 0; i < G->v - 1; ) {
        while (j != 0){
            j++;
        }
        minEdge = &G->edge[j];
        
        
        for (k = 0; k < G->e; k++) {
            if (G->edge[k].weight < minEdge->weight && G->edge[k].flag == 0){
                minEdge = &G->edge[k];
            }
        }
        
        
        if ((set[minEdge->vexh] != set[minEdge->vext])) {
            (*minEdge).flag = 1;
            M->edge[M->e] = *minEdge;
            M->e++;
            
            for ( j = 0; j < G->v; j++) {
                if (set[j] == set[minEdge->vext]) {
                   set[j] = set[minEdge->vexh];
                }
            }
            set[minEdge->vexh] = set[minEdge->vext];
            i++;
        }
        else {
            minEdge->flag = 2;
        }
        
    }
    
    
}



int main () {
    Graph G, M;
    
    CreatGraph(&G);
    Kruskal(&G, &M);
    
    
    for (int i = 0; i < M.e; i++){
        
        printf("vexh:%d  vext:%d  weight:%d  flag:%d\n", M.edge[i].vexh, M.edge[i].vext, M.edge[i].weight, M.edge[i].flag);
    }
    
}




















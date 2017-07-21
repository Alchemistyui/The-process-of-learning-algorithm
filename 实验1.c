//
//  main.c
//  数据结构实验1
//
//  Created by Alchemist on 2017/4/15.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20


typedef struct stuInfo {
    int   stuID;
    char  stuName[10];      /*学生姓名*/
    int    Age; /*年龄*/
} ElemType;


typedef struct node {
    ElemType  data;
    struct  node  *next;
} ListNode, *ListPtr;




void LinkListInit(ListPtr* L){
    *L = (ListPtr) malloc(sizeof(ElemType));
    if (*L == NULL) {
        printf("申请空间分配失败");
        
    }
    (*L) -> next = NULL;
    
}


void Bubble(ListPtr* L){
    int i,j;
    ListPtr p = *L;
    ElemType temp;
    
    
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
            if(p->data.stuID > p->next->data.stuID)
            {
                temp = p->data;
                p->data = p->next->data;
                p->next->data=temp;
            }
            p = p->next;
        }
    }
    
}



void LinkedListCreate(ListPtr* L, ElemType a[], int n){
    ListPtr p;
    
    LinkListInit(L);
    
    for (int i = 0; i < n; i++){
        p = (ListPtr) malloc(sizeof(ListNode));
        if (p == NULL){
            printf("分配空间失败");
            
        }
        p -> data = a[i];
        //此时包含了末尾next的null化
        p -> next = (*L) -> next;
        (*L) -> next = p;
    }
    Bubble(L);

    
}



void LinkedListInsert(ListPtr* L, ElemType stu, ListPtr p){
    ListPtr q, pre;
    q = (ListPtr) malloc(sizeof(ListNode));
    
    if (q == NULL){
        printf("分配失败");
        
    }
    
    q -> data = stu;
    
    pre = *L;
    while ((pre != NULL) && (pre -> next != p)) {
        pre = pre -> next;
    }
    
    q -> next = pre -> next;
    pre -> next = q;
    
    Bubble(L);
    
    
}

void DelRepetition(ListPtr* L){
        ListPtr p, pre;
        
        pre = (*L)->next;
        
        while ((pre->next != NULL) && ((pre->data.stuID) != (pre->next->data.stuID))) {
            pre = pre -> next;
        }
        p = pre -> next;
        
        if (p != NULL){
            if (p->data.Age < pre->data.Age){
                pre -> next = p -> next;
            }
            else {
                pre->data = p->data;
                pre -> next = p -> next;
            }
            
           free(p);
        }
        
    
    
}


void LinkedListMerge(ListPtr* La, ListPtr* Lb, ListPtr* Lc){
    ListPtr pa, pb, pc;
    
    pa = (*La) -> next;
    pb = (*Lb) -> next;
    (*Lc) = (*La);
    pc = *Lc;
    
    while ((pa != NULL) && (pb != NULL)) {
        if (pa -> data.stuID <= pb -> data.stuID){
            pc -> next = pa;
            pc = pa;
            pa = pa -> next;
        }
        else {
            pc -> next = pb;
            pc = pb;
            pb = pb -> next;
        }
    }
    
    if (pa != NULL){
        pc -> next = pa;
        
    }
    else {
        pc -> next = pb;
    }
    
    DelRepetition(Lc);
    
    free(*Lb);
    free(*La);
}




void LinkedListReverseSort(ListPtr* La, ListPtr* Lb){
    ListPtr pa = (*La)->next, pb = (*Lb)->next, temp = NULL;
    
    (*La) -> next = NULL;
    
    while (pa != NULL && pb != NULL) {
        if ((pa ->data.stuID) <= (pb->data.stuID)){
            
            temp = pa->next;
            pa->next = (*La)->next;
            (*La)->next = pa;
            pa = temp;
        }
        else {
            temp = pb->next;
            pb->next = (*La)->next;
            (*La)->next = pb;
            pb = temp;
        }
    }
    while (pa != NULL){
        temp = pa -> next;
        pa->next = (*La)->next;
        (*La)->next = pa;
        pa = temp;
    }
    while (pb != NULL){
        temp = pb->next;
        pb->next = (*La)->next;
        (*La)->next = pb;
        pb = temp;
    }
    
    DelRepetition(La);
    
    
}




void LinkedListTraverse(ListPtr* L){
    ListPtr p;
    p = (*L)->next;
    
    while(p != NULL){
        printf("%d  %s  %d\n", p->data.stuID, p->data.stuName, p->data.Age);
        p = p->next;
    }
    printf("\n");
}




int main() {
    ListPtr La, Lb, Lc;
    int i;
    ElemType stu[MAX_SIZE],elem;
    FILE *fp, *fp2;
    
    
    
    fp = fopen("/Users/ryshen/Desktop/la.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        return 0;
    }
    for(i = 0; !feof(fp); i++)
    {
        fscanf(fp, "%d %s %d", &stu[i].stuID, stu[i].stuName, &stu[i].Age);
    }
    fclose(fp);
    
    LinkedListCreate(&La, stu, i);
    printf("la:\n");
    LinkedListTraverse(&La);
    
    
    printf("输入插入数据\n");
    scanf("%d %s %d", &elem.stuID, elem.stuName, &elem.Age);
    LinkedListInsert(&La, elem, La->next);
    printf("insert\n");
    LinkedListTraverse(&La);
    
    
    
    fp2 = fopen("/Users/ryshen/Desktop/lb.txt","r");
    if(!fp2)
    {
        printf("The file does not exist!\n");
        return 0;
    }
    for(i = 0; !feof(fp2); i++)
    {
        fscanf(fp2, "%d %s %d", &stu[i].stuID, stu[i].stuName, &stu[i].Age);
        
    }
    fclose(fp2);
    
    LinkedListCreate(&Lb, stu, i);
    printf("lb:\n");
    LinkedListTraverse(&Lb);

    
    LinkedListMerge(&La, &Lb, &Lc);
    printf("合并:\n");
    LinkedListTraverse(&Lc);
    
    
    //------------------
    
    
    fp = fopen("/Users/ryshen/Desktop/la.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        return 0;
    }
    for(i = 0; !feof(fp); i++)
    {
        fscanf(fp, "%d %s %d", &stu[i].stuID, stu[i].stuName, &stu[i].Age);
    }
    fclose(fp);
    
    LinkedListCreate(&La, stu, i);
    
    
    
    fp2 = fopen("/Users/ryshen/Desktop/lb.txt","r");
    if(!fp2)
    {
        printf("The file does not exist!\n");
        return 0;
    }
    for(i = 0; !feof(fp2); i++)
    {
        fscanf(fp2, "%d %s %d", &stu[i].stuID, stu[i].stuName, &stu[i].Age);
        
    }
    fclose(fp2);
    
    LinkedListCreate(&Lb, stu, i);

    //--------------------
    
    
    
    
    LinkedListReverseSort(&La, &Lb);
    printf("reverse\n");
    LinkedListTraverse(&La);
    
    return 0;
}





















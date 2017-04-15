//
//  main.c
//  链表的操作
//
//  Created by Alchemist on 17/3/8.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;

typedef enum{
    ERROR = 1,
    OK = 0
}Status;
//定义
typedef struct Node {
    ElementType data;
    struct Node *next;
    
}LNode, *LinkedList;



Status LinkListInit(LinkedList* L);
Status LinkListInit2(LinkedList* L);
int    LinkedListLength(LinkedList* L);
int    LinkedListLength2(LinkedList* L);
LinkedList    LinkedListGet(LinkedList* L, int i);
LinkedList    LinkedListGet2(LinkedList* L, int i);
LinkedList    LinkedListLocate(LinkedList* L, ElementType elem);
LinkedList    LinkedListLocate2(LinkedList* L, ElementType elem);
Status LinkedListInsert(LinkedList* L, ElementType elem, LinkedList p);
Status LinkedListInsert2(LinkedList* L, ElementType elem, LinkedList p);
Status LinkedListDel(LinkedList* L, ElementType elem);
Status LinkedListDel2(LinkedList* L, ElementType elem);
Status LinkedListCreate1(LinkedList* L, ElementType a[], int n);
Status LinkedListCreate2(LinkedList* L, ElementType a[], int n);
void LinkedListMerge(LinkedList* La, LinkedList* Lb, LinkedList* Lc);
void LinkedListReverseSort(LinkedList* La, LinkedList* Lb);
void LinkedListTraverse(LinkedList* L);



Status LinkListInit(LinkedList* L){
    L = NULL;
    return 0;
}


//一定要记得判断！还要把新的指针赋空
Status LinkListInit2(LinkedList* L){
    *L = (LinkedList) malloc(sizeof(ElementType));
    if (*L == NULL) {
        printf("申请空间分配失败");
        return 1;
    }
    (*L) -> next = NULL;
    return 0;
}


int    LinkedListLength(LinkedList* L){
    LinkedList p;
    int i = 0;
    
    p = (*L);
    
    while (p != NULL) {
        i++;
        p = p -> next;
    }
    return i;
}




int    LinkedListLength2(LinkedList* L){
    LinkedList p;
    int i = 0;
    
    p = (*L) -> next;
    
    while (p != NULL){
        i++;
        p = p -> next;
    }
    return i;
}

//无头:此时j是指位置所以应从1开始
LinkedList    LinkedListGet(LinkedList* L, int i){
    LinkedList p;
    int j = 1;
    
    if (i <= 0){
        printf("the value of i is illegal");
        exit(0);
    }
    
    p = (*L);
    while ((p != NULL) && (j < i)) {
        p = p -> next;
        j++;
    }
    return p;
}
           


LinkedList  LinkedListGet2(LinkedList* L, int i){
    LinkedList p;
    int j = 1;
    
    p = (*L) -> next;
    
    while (p != NULL && j < i){
        p = p->next;
        j++;
    }
    return p;
}
           
LinkedList    LinkedListLocate(LinkedList* L, ElementType elem){
    LinkedList p;
    
    p = *L;
    while ((p != NULL) && (p ->data != elem)){
        p = p -> next;
    }
    return p;
}



LinkedList  LinkedListLocate2(LinkedList* L, ElementType elem){
    LinkedList p;
    
    p = (*L) -> next;
    
    while (p != NULL && p -> data != elem){
        p = p -> next;
    }
    return p;
}
          

Status LinkedListInsert(LinkedList* L, ElementType elem, LinkedList p){
    LinkedList q, pre;
    
    q = (LinkedList) malloc(sizeof(LNode));
    if (q == NULL){
        printf("分配空间失败");
        return 1;
    }
    q -> data = elem;
    if (p == *L){
        q -> next = (*L) -> next;
        *L = q;
        return 0;
    }
    
    pre = *L;
    while ((pre != NULL) && (pre -> next != p)){
        pre = pre -> next;
    }
    q -> next = pre -> next;
    pre -> next = q;
    
    return 0;
}


//带头插入,前插
Status LinkedListInsert2(LinkedList* L, ElementType elem, LinkedList p){
    LinkedList q, pre;
    q = (LinkedList) malloc(sizeof(LNode));
    
    if (q == NULL){
        printf("分配失败");
        return 1;
    }
    q -> data = elem;
    //当pre取next的时候，万一为空，循环时pre就没有next
    //只要后面有p -> next就不能取next
    pre = *L;
    while ((pre != NULL) && (pre -> next != p)) {
        pre = pre -> next;
    }
    
    q -> next = pre -> next;
    pre -> next = q;
    
    return 0;
}



//记得判断是否存在
//不带头删除
Status LinkedListDel(LinkedList* L, ElementType elem){
    LinkedList p, pre;
    pre = *L;
    
    //l为空时无next，所以不能取next
    while ((pre != NULL) && (pre -> next -> data != elem)) {
        pre = pre -> next;
    }
    
    p = pre -> next;
    if (p == *L){
        *L = p -> next;
        free(p);
    }
    if (p != NULL){
        pre -> next = p -> next;
        free(p);
    }
    
    
    return 0;
}




//带头删除
Status LinkedListDel2(LinkedList* L, ElementType elem){
    LinkedList p, pre;
    //同上
    pre = *L;
    
    while ((pre != NULL) && (pre ->next ->data != elem)) {
        pre = pre -> next;
    }
    p = pre -> next;
    
    if (p != NULL){
        pre -> next = p -> next;
        free(p);
    }
    
    return 0;
}





//头插
Status LinkedListCreate1(LinkedList* L, ElementType a[], int n){
    LinkedList p;
    
    LinkListInit2(L);
    
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


Status LinkedListCreate2(LinkedList* L, ElementType a[], int n){
    LinkedList p, tail;
    
    LinkListInit2(L);
    //此处的tail因为以后要取next所以不能去next；
    tail = *L;
    for (int i = 0; i < n; i++){
        p = (LinkedList) malloc(sizeof(LNode));
        if (p == NULL){
            printf("分配空间失败");
            return 1;
        }
        p -> data = a[i];
        p -> next = NULL;
        tail -> next = p;
        tail = p;
    }
    
    return 0;
}


void LinkedListMerge(LinkedList* La, LinkedList* Lb, LinkedList* Lc){
    LinkedList pa, pb, pc;
    
    pa = (*La) -> next;
    pb = (*Lb) -> next;
    (*Lc) = (*La);
    pc = *Lc;
    
    while ((pa != NULL) && (pb != NULL)) {
        if (pa -> data <= pb -> data){
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
    
    free(*Lb);
    free(*La);
}


//小到大换为大到小,头插法
void LinkedListReverseSort(LinkedList* La, LinkedList* Lb){
    LinkedList pa = (*La)->next, pb = (*Lb)->next, temp;
    
    (*La) -> next = NULL;
    
    while (pa != NULL && pb != NULL) {
        if (pa ->data <= pb->data){
            //将后面的结点保存起来
            temp = pa->next;
            pa->next = (*La)->next;
            (*La)->next = pa;
            pa = temp;
        }
        else {
            temp = pb->next;
            pb->next = (*Lb)->next;
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
        pb->next = (*Lb)->next;
        (*La)->next = pb;
        pb = temp;
    }
    
}



void LinkedListTraverse(LinkedList* L){
    LinkedList p;
    p = *L;
    
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}




int main(){
    LinkedList La, Lb, HLa, HLb, HLc;
    LinkedList p, loc;
    int la[3] = {3,2,1}, lb[3] = {4,5,6}, lc[8] = {0,0,0,0,0,0,0,0};
    
    LinkedListCreate1(&La, la, 3);
    LinkedListCreate2(&Lb, lb, 3);
    LinkedListTraverse(&La);
    LinkedListTraverse(&Lb);
    
    
    printf("length:%d\n", LinkedListLength(&La));
    p = LinkedListGet(&La, 1);
    printf("first data:%d\n", p->data);
    
    
    
    loc = LinkedListLocate(&La, 1);
    LinkedListInsert(&La, 1, loc);
    LinkedListTraverse(&La);
    printf("\n\n");
    
//----------------------------------------------------------
    LinkedListCreate1(&HLa, la, 3);
    LinkedListCreate2(&HLb, lb, 3);
    LinkedListCreate1(&HLc, lc, 8);
    //
    LinkedListTraverse(&HLa);
    LinkedListTraverse(&HLb);
    
    
    printf("len: %d\n", LinkedListLength2(&HLa));
    p = LinkedListGet2(&HLa, 2);
    printf("data: %d\n", p-> data);
    
    loc = LinkedListLocate2(&HLa, 2);
    LinkedListDel2(&HLa, 1);
    LinkedListInsert2(&HLa, 0, loc);
    
    LinkedListTraverse(&HLa);
    
    
    LinkedListMerge(&HLa, &HLb, &HLc);
    LinkedListTraverse(&HLc);
    LinkedListReverseSort(&HLa, &HLb);
    LinkedListTraverse(&HLa);
    
}


























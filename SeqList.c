//
//  main.c
//  顺序表的操作
//
//  Created by Alchemist on 17/3/4.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100


typedef enum Status{
    ERROR = 0, OK = 1
}Status;

typedef int ElementType;

//定义结构体
//struct的标识符
typedef struct node {
    ElementType data[MAX_SIZE];
    int length;
    //别名,而当没有typedef时才是其中的一个变量，此时不用定义可直接用
}SeqList;


Status SeqListInit(SeqList* L);
int SeqListLength(SeqList* L);
ElementType SeqListGet(SeqList* L, int i);
int SeqListLocate(SeqList* L, ElementType elem);
ElementType SeqListPrior(SeqList* L, ElementType elem);
ElementType SeqListNext(SeqList* L, ElementType elem);
Status SeqListInsert(SeqList* L, ElementType elem, int i);
Status SeqListDel(SeqList* L, int i);
bool SeqListEmpty(SeqList* L);
Status SeqListTraverse(SeqList* L);
Status SeqListUnion(SeqList* La, SeqList* Lb);
Status SeqListMerge(SeqList* La, SeqList* Lb, SeqList* Lc);



//初始化
Status SeqListInit(SeqList* L){
    L->length = 0;
    return 1;
}

//求长度操作
int SeqListLength(SeqList* L){
    
    return L->length;
}

//取元素操作:记得判断是否合法
ElementType SeqListGet(SeqList* L, int i){
    
    if (i < 1 || i > L->length){
        printf("The value of i is illegal\n");
        exit(0);      //程序正常退出的库函数<stdlib.h>
    }
    else {
        return L->data[i - 1];
    }
}

//定位操作
int SeqListLocate(SeqList* L, ElementType elem){
    int i = 1;
    
    for ( ; i <= L->length; i++){
        if (elem == L->data[i - 1]){
            return i;
        }
    }
    
    printf("This element is not in the list");
    return 0;
}

//求前驱:注意特例
ElementType SeqListPrior(SeqList* L, ElementType elem){
    int i;
    
    i = SeqListLocate(L, elem);
    if (1 == i){
        printf("The first element don't have prior element");
        exit(0);
    }
    else if (i != 0){
        return L->data[i - 2];
    }
    else{
        printf("This element is not in the list");
        exit(0);
    }
    
}

//求后继：特例
ElementType SeqListNext(SeqList* L, ElementType elem){
    int i;
    
    i = SeqListLocate(L, elem);
    if (L->length == i){
        printf("The last element don't have next element");
        exit(0);
    }
    else if (i != 0){
        return L->data[i];
    }
    else{
        printf("This element is not in the list");
        exit(0);
    }
    
}

//前插:对表的判断,注意循环时j的取值
Status SeqListInsert(SeqList* L, ElementType elem, int i){
    
    if (i < 1 || i > L->length + 1){
        printf("The value of i is illegal\n");
        return 1;
    }
    if (L->length == MAX_SIZE){
        printf("The SeqList is full");
        return 1;
    }
    for (int j = L->length - 1; j >= i - 1; j--){
        L->data[j + 1] = L->data[j];
    }
    L->data[i - 1] = elem;
    L->length++;
    
    return 0;
}

//删除：循环时j的取值
Status SeqListDel(SeqList* L, int i){
    
    if (i < 1 || i > L->length){
        printf("The value of i is illegal");
        return 1;
    }
    if (L->length == 0){
        printf("The SeqList is empty");
        return 1;
    }
    for (int j = i; j <= L->length - 1; j++){
        L->data[j - 1] = L->data[j];
    }
    L->length--;
    
    return 0;
}

//判空
bool SeqListEmpty(SeqList* L){
    
    return !L->length;
}

//遍历
Status SeqListTraverse(SeqList* L){
    
    if (SeqListEmpty(L)){
        printf("This list is empty");
        return 1;
    }
    for (int i = 1; i <= L->length; i++){
        printf("%d\n", L->data[i - 1]);
    }
    return 0;
}

//直接合并
Status SeqListUnion(SeqList* La, SeqList* Lb){
    ElementType elem;
    Status status = 1;
    if(La->length > Lb->length){
        for (int i = 1; i <= Lb->length; i++){
            elem = SeqListGet(Lb, i);
            if (SeqListLocate(La, elem) == 0){
                
                status = SeqListInsert(La, elem, 1);
                if(status == 0){
                    break;
                }
                
            }
        }
    }
    
    else {
        for (int i = 1; i<= La->length; i++){
            if (SeqListGet(Lb, Lb->data[i]) == 0){
                SeqListInsert(La, Lb->data[i], 1);
            }
        }
    }
    return status;
}


//保序合并
Status SeqListMerge(SeqList* La, SeqList* Lb, SeqList* Lc){
    int i = 1, j = 1, k = 0;
    Status status = 1;
    
    status = SeqListInit(Lc);
    
    while(i <= La->length && j <= Lb->length ){
        if(SeqListGet(La,i) <= SeqListGet(Lb, j) ){
            status = SeqListInsert(Lc, SeqListGet(La, i),k + 1);
            i++;
            k++;
        }
        else {
            status = SeqListInsert(Lc, SeqListGet(Lb, j), k + 1);
            j++;
            k++;
        }
        
    }
    while(i <= SeqListLength(La)){
        SeqListInsert(Lc, SeqListGet(La, i), k + 1);
        
        i++;
        k++;
    }
    while(j <= SeqListLength(Lb)){
        SeqListInsert(Lc, SeqListGet(Lb, j), k + 1);
        j++;
        k++;
    }
    Lc->length = k;
    return status;
}



int main() {
    SeqList list1, list2, list3;
    int len, m =4;
    
    SeqListInit(&list1);
    len = SeqListLength(&list1);
    printf("len: %d\n", len);
    
    for (int i = 1; i <= 3; i++){
        SeqListInsert(&list1, i, i);
    }
    
    for (int i = 1; i <= 3; i++){
        SeqListInsert(&list2, m++, i);
    }
    
    SeqListTraverse(&list1);
    len = SeqListLength(&list1);
    printf("len :%d\n", len);
    
    
    printf("the second elem: %d\n", SeqListGet(&list1, 3));
    printf("the location : %d\n", SeqListLocate(&list1, 2));
    printf("the prior of 3: %d\n",SeqListPrior(&list1, 3));
    printf("the next of 2: %d\n",SeqListNext(&list1, 2));
    
    
    SeqListInsert(&list1, 0, 1);
    SeqListTraverse(&list1);
    
    
    printf("is empty: %d\n", SeqListEmpty(&list1));
    
    SeqListMerge(&list1, &list2, &list3);
    SeqListTraverse(&list3);
    
    
}



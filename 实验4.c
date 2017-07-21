//
//  main.c
//  实验4
//
//  Created by Alchemist on 2017/6/4.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void readData(int a[], int* num) {
    FILE* fp;
    int c;
    
    *num = 0;
    
    fp=fopen("/Users/ryshen/Desktop/test2.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        exit(0);
    }

    for (int i = 0; fscanf(fp,"%d",&c)!=EOF; i++) {
        a[i] = c;
        (*num)++;
    }
    
    fclose(fp);
}

void swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(int a[],int start, int tail) {
    int i, j, x;
    
    i = start;
    j = tail;
    x = a[start];
    
    while (i < j) {
        
        while(a[j] >= x && j > i) {
            j--;
        }
        swap(&a[i], &a[j]);
        
        while(a[i] <= x && i < j) {
            i++;
        }
        
        swap(&a[i], &a[j]);

    }
    
    if (start < tail) {
        quickSort(a, start, i-1);
        quickSort(a, i+1, tail);

    }
    
}


int binSearch(int a[], int x, int num) {
    int low = 0, high = num-1, mid, time = 0;
    
    while(low <= high) {
        mid = (low + high) / 2;
        if (x == a[mid]) {
            time++;
            if (a[mid-1] == x || a[mid+1] == x){
                printf("existence & number > 1\n");
            }
            else {
                printf("existence & number = 1\n");
            }
            return 1;
        }
        else if (x < a[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    printf("nonexistence\n");
    return 0;
}


int main() {
    int a[MAX];
    int num, x;
    
    readData(a, &num);
    
    printf("before:");
    for (int i = 0; i < num; i++){
        printf(" %d", a[i]);
    }
    printf("\n");
    
    
    quickSort(a, 0, num-1);
    
    printf("sort:");
    for (int i = 0; i < num; i++){
        printf(" %d", a[i]);
    }
    printf("\n");
    
    for (int i = 0; i < 3; i++){
        printf("input search data:\n");
        scanf("%d", &x);
        binSearch(a, x, num);
    }
    
}
































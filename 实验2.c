//
//  main.c
//  real数据结构实验2
//
//  Created by Alchemist on 2017/4/27.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define MAX_CHARLEN 10


typedef struct {
    char data;
    int weight;
    int parent;
    int lchild;
    int rchild;
}HFTreeNode, *HFTree;


typedef struct CodeNode
{
    char ch;	//存储字符
    char bits[MAX_CHARLEN+1];	//存放编码位串
}HuffmanCode;




void countTimes(int count[], int* num) {
    int i = 0, c;
    FILE* fp;
    char ch;
    
    for (i = 0; i < 52; i++){
        count[i] = 0;
    }
    
    fp=fopen("/Users/ryshen/Desktop/test.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        exit(0);
    }
    for (i = 0; fscanf(fp,"%c",&ch)!=EOF; i++) {
        if (ch >= 97) {
            c = ch - 'a';
        }
        else {
            c = ch - 'A' + 26;
        }
        
        count[c]++;
    }
    fclose(fp);
    
    for (i = 0; i < 52; i++){
        if (count[i] != 0) {
            (*num)++;
        }
    }
}



void SelectMin (HFTree T, int n, int* p1, int* p2){
    int i, j;
    
    
    for (i = 1; i <= n; i++){
        if (T[i].parent == 0){
            (*p1) = i;
            break;
        }
    }
    
    for (j = 1; j <= n; j++){
        if ((T[j].parent == 0) && (T[j].weight < T[i].weight)){
            (*p1) = j;
            i = j;
        }
    }
    
    for (i = 1; i <= n; i++){
        if ((T[i].parent == 0) && i != (*p1)){
            (*p2) = i;
            break;
        }
    }
    
    for (j = 1; j <= n; j++){
        if ((T[j].parent == 0) && T[j].weight < T[i].weight && j != (*p1)){
            (*p2) = j;
            i = j;
        }
    }
    
}





int createHFTree(HFTreeNode T[], int sum, int count[]){
    int i, p1 = 0, p2 = 0, c = 1;
    
    if (sum < 1 || sum > MAX_SIZE){
        printf("sum is illegal\n");
        return 1;
    }
    
    
    for (i = 1; i < 2 * sum; i++){
        T[i].parent = 0;
        T[i].lchild = 0;
        T[i].rchild = 0;
        T[i].weight = 0;
    }
    
    
    for (i = 0; i <= 52 && c<=sum; i++){
        if (count[i] != 0){
            
            T[c].weight = count[i];
            if (i < 26){
                T[c].data =  i + 'a';
            }
            else {
                T[c].data =  i + 'A' - 26;
            }
            c += 1;
        }
    }
    
    
    for (i = sum + 1; i <= 2 * sum; i++){
        SelectMin (T, i - 1, &p1, &p2);
        
        T[p1].parent = i;
        T[p2].parent = i;
        
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
    }
    
    return 0;
}





void CharSetHuffmanEncoding(HFTreeNode T[], HuffmanCode H[], int sum) {
    int c, p, i;
    char cd[sum + 1];
    int start = 0;
    
    
    
    cd[sum] = '\0';
    
    for(i = 1; i <= sum; i++){
        H[i].ch = T[i].data;
        start = sum;
        c = i;
        while((T[c].parent > 0)) {
            p = T[c].parent;
            if(T[p].lchild == c)  {
                cd[--start] = '0';
            }
            else {
                cd[--start] = '1';
            }
            c = p;
        }
        strcpy(H[i].bits, &cd[start]);
        
    }
    
}





int main() {
    int count[52];
    int num, i;
    
    
    countTimes(count, &num);
    
    HuffmanCode H[MAX_CHARLEN];
    HFTreeNode T[2*num];
    
    createHFTree(T, num, count);
    
    
    for (i = 0; i < 52; i++){
        if (count[i] != 0) {
            if (i < 26){
                printf("%c:%d\t", i+'a', count[i]);
                
            }
            else{
                printf("%c:%d\t", i+'A'-26, count[i]);
                
            }
        }
    }
    printf("\n");
    
    CharSetHuffmanEncoding(T, H, num);
    
    for (i = 1; i <= num; i++) {
        printf(" char: %c\t code: %s\n", H[i].ch, H[i].bits);
    }
    
    return 0;
}

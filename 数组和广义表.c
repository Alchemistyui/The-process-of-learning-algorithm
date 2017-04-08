//
//  main.c
//  数组和广义表
//
//  Created by Alchemist on 2017/4/2.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>
#define MAXSIZE 20

typedef int ElementType;

//三元组存放稀疏矩阵
typedef struct{
    int i, j;
    ElementType e;
}Triple;


int transMatrix (Triple Ma[], Triple Mb[]){
    int k = 1;
    
    if (Ma[0].e == 0){
        return 0;
    }
    
    Mb[0].i = Ma[0].j;
    Mb[0].j = Ma[0].i;
    Mb[0].e = Ma[0].e;
    
    for (int col = 1; col <= Ma[0].j; col++){
        for (int p = 1; p <= Ma[0].e; p++){
            if (Ma[p].j == col) {
                Mb[k].i=Ma[p].j;
                Mb[k].j=Ma[p].i;
                Mb[k].e=Ma[p].e;
                k++;

            }
        }
    }
    
    return 1;
}




int fastTransMatirx (Triple Ma[], Triple Mb[]){
    int col, k;
    //不使用num【0】，使下标与行数相等
                      //存放每一列起始元素的位置
    int num[Ma[0].j + 1], cpot[Ma[0].j + 1];
    
    
    
    
    if (Ma[0].e == 0){
        return 0;
    }
    
    Mb[0].i = Ma[0].j;
    Mb[0].j = Ma[0].i;
    Mb[0].e = Ma[0].e;
    
    for (int i = 0; i <= Ma[0].j; i++){
        num[i] = 0;
    }
    
    for (int i = 1; i <= Ma[0].e; i++){
        num[Ma[i].j]++;
    }
    
    cpot[0]=0;
    cpot[1]=1;
    
    for(col=2;col<=Ma[0].j;col++){
        cpot[col]=cpot[col-1]+num[col-1];
    }

    for(int p = 1;p <= Ma[0].e; p++)
    {   col = Ma[p].j;
        k = cpot[col];
        Mb[k].i = Ma[p].j;
        Mb[k].j = Ma[p].i;
        Mb[k].e = Ma[p].e;
        cpot[col]++;
    }
    return 1;

}




int main()
{
    Triple ma[MAXSIZE],mb[MAXSIZE];
    FILE *fp;
    fp = fopen("/Users/ryshen/Desktop/data.txt","r");
    if(!fp)
    {
        printf("The file does not exist!\n");
        return 0;
    }
    fscanf(fp,"%d",&ma[0].i);
    fscanf(fp,"%d",&ma[0].j);
    fscanf(fp,"%d",&ma[0].e);
    
    for(int i=1;i<=ma[0].e;i++)
    {
        fscanf(fp,"%d",&ma[i].i);
        fscanf(fp,"%d",&ma[i].j);
        fscanf(fp,"%d",&ma[i].e);
    }
    fclose(fp);
    for(int i=1;i<=ma[0].e;i++)
        printf("%d,%d,%d\n",ma[i].i,ma[i].j,ma[i].e);
    
    transMatrix(ma,mb);
    //	fast_transpos(ma,mb);
    printf("\n");
    for(int i=1;i<=mb[0].e;i++)
        printf("%d,%d,%d\n",mb[i].i,mb[i].j,mb[i].e);
}




























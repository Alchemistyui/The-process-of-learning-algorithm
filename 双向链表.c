//
//  main.c
//  双向链表
//
//  Created by Alchemist on 17/3/12.
//  Copyright © 2017年 Ry Shen. All rights reserved.
//

#include <stdio.h>

typedef  int  ElementType;

typedef struct Node{
    ElementType data;
    struct Node *next, *prior;
}DLNode, *DLinkedList;


/*insert
q -> prior = p -> prior;
p -> prior -> next = q;
q -> next = p;
p -> prior  = q;
*/

/*delet
 p -> prior -> next = p -> next;
 p -> next -> prior = p -> prior;
 free(p);
 */

//----------------------------------------------------------
//循环链表：一般带头








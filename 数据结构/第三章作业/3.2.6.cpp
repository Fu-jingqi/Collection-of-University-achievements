/*  数据结构算法题(假设以带头结点的循环链表表示队列,
 *  并且只设一个指针指向队尾元素结点(注意不设头指针)
 *  试编写相应的队列初始化,入队列和出队列的算法!) 
 */
#include<bits/stdc++.h>
using namespace std;
typedef struct QNode 
{
    int data;
    struct QNode * rear;
    struct QNode * next;
}QNode;

//链式队列的初始化
int InitLinkQueue(QNode * &L){

    L = new QNode;
    if(L==NULL){
        printf("内存分配失败！\n");
        return 1;
    }
    L->rear=L;
    return 1;
}

//链式队列的建立
int Create(QNode * & L,int n)
{
    srand(time(0));
    QNode *P;
    for(int i=0;i<n;i++)
    {
        P = new QNode;
        P->data=rand()%100+1;
        L->rear->next=P;
        L->rear=P;
    }
    P->next=L;
    return 1;
}

//入队操作
int EnQueue(QNode * & L,int e)
{
    QNode * P;
    P=(QNode *)malloc(sizeof(QNode));
    P->data=e;
    P->next=L;
    L->rear->next=P;
    L->rear=P;
    return 1;
}


//出队操作
int DeQueue(QNode * & L,int * e)
{
    QNode * temp;
    *e=L->next->data;
    temp=L->next;
    L->next=L->next->next;
    delete(temp);
    return 1;

}

//输出
void Print(QNode * & L)
{
    QNode * P;
    P=L->next;
    printf("输出元素:\n");
    while(P!=L)
    {
        printf("%d ",P->data);
        P=P->next;
    }
    printf("\n");
}


int main()
{
    return 0;
}
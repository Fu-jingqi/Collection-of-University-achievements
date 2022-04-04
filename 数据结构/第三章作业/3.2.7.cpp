/*
 *  假设以数组Q[m]存放循环队列中的元素, 同时设置一个标志tag，以tag
 *  = 0 和 tag = 1来区别在队头指针(front)和队尾指针(rear)相等时，
 *  队列状态为“空”还是“满”。试设计与此结构相应的插入和删除算法，编写
 *  代码，并带入数据运行验证通过
 */
#include<bits/stdc++.h>
using namespace std;
#define MaxSize 100
int tag;
typedef struct{
	int *Q;
	int front;
	int rear;
}QNode; 
//初始化
void Init(QNode &L){   
	L.Q = new int[MaxSize];
	L.front = L.rear = 0;
	tag = 0;
}
//入队列
int Enter(QNode &L,int m){     
	if(L.rear%MaxSize == L.front && tag == 1){
		cout<<"队列已满！";
		return 0; 
	}
	L.Q[L.rear] = m;
	L.rear = (L.rear+1)%MaxSize;
	if(L.rear == L.front)tag = 1;
	return 1;
}
// 出队列
int Out(QNode &L,int &m){    
	if(L.rear == L.front && tag == 0){
		cout<<"队列空！";
		return 0;
	}
	m = L.Q[L.front];
	L.front = (L.front+1)%MaxSize;
	if(L.rear == L.front)tag = 0;
	return 1;
}
// 判空
int JudgeEmpty(QNode L){
	if(L.rear == L.front && tag == 0){
		cout<<"队列空！";
		return 0;
	}
}
// 判满
int JudgeFullness(QNode L){
	if(L.rear%MaxSize == L.front && tag == 1){
		cout<<"队列已满！";
		return 0; 
	}
}

int main(){

	return 0;
}


#include<iostream>

using namespace std ;
const int Maxsize = 1e6 + 10 ;
typedef struct {
	int data[Maxsize] ;
	int front ;
	int rear ;
}SqQuene;

void Init(SqQuene &q){
	q.front = q.rear = 0 ;
}

int Is_Empty(SqQuene q){
	if(q.front == q.rear)
		return 1;
	else return 0 ;
}

int Is_Full(SqQuene q){
	return (q.rear + 1) % Maxsize == q.front ;
}

int EnterQuene(SqQuene &q,int x){
	if(Is_Full(q)) return 0 ;
	q.rear = (q.rear + 1) % Maxsize ;
	q.data[q.rear] = x ;
	return 1 ;
}

int Delete_Quene(SqQuene &q,int &x){
	if(Is_Empty(q)) return 0 ;
	q.front = (q.front + 1) % Maxsize ;
	x = q.data[q.front] ;
	return 1 ;
}

int main(){

	return 0 ;
}
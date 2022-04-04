#include <bits/stdc++.h>

using namespace std;
 
const int N = 100001;
 
typedef long long LL;
 
void setup(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}  
# define MaxInitLen 100 
typedef struct
{
	int top[2], bot[2];	//定义栈顶和栈底指针
	int *V;				//栈数组
	int m;				//栈最大可容纳元素个数
}DblStack;

void init(DblStack &s){
	s.m = MaxInitLen ;
	s.top[0] = -1 ;
	s.bot[0] = -1 ;
	s.top[1] = s.m - 1 ;
	s.bot[1] = s.m - 1 ;
	int *p = (int*)malloc(sizeof(int)) ;
	s.V = p ;
}
bool Is_Empty(DblStack s){
	if(s.top[0] == -1&&s.top[1] == s.m-1) return true ;
	return false ;
}
bool Is_Full(DblStack s){
	if(s.top[1] == s.top[0] || s.top[0] == s.m || s.top[1] < 0 ) return 1;//满栈返回1
	return 0;//否则返回0
}
void Enter_Left_Stack(DblStack &s,int x){
	if(s.top[0] != s.m && s.top[0] < s.top[1]){
		s.top[0] ++ ;
		s.V[s.top[0]] = x ;
	}else{
		cout << "栈已满，不可进栈" << "\n" ;
	}
}

void Enter_Right_Stack(DblStack &s,int x){
	if(s.top[0] != s.m && s.top[0] < s.top[1]){
		s.V[s.top[1]] = x ;
		s.top[1] -- ;
	}else{
		cout << "栈已满，不可进栈" << "\n" ;
	}
}
void Out_Left_Stack(DblStack &s){
	if(Is_Empty(s)){
		cout << "栈为空，不可执行出栈操作"<<"\n" ;
	}else{
		int e = s.V[s.top[0]];	//取出栈顶数据元素
    	s.top[0]--;	
	}
}

void Out_Right_Stack(DblStack &s){
	if(Is_Empty(s)){
		cout << "栈为空，不可执行出栈操作"<<"\n" ;
	}else{
		s.top[1]++;					//右栈栈顶指针加一
    	int e = s.V[s.top[1]];
	}
}

void Print_LeftStack(DblStack s){
	for(int i = 0 ; i <= s.top[0] ; i ++){
		cout << s.V[i] << " " ;
	}
	cout << "\n" ;
}

void Print_RightStack(DblStack s){
	for(int i = s.bot[1] ; i > s.top[1] ; i --){
		cout << s.V[i] << " " ;
	}
	cout << "\n" ;
}

int main() 
{
    setup();

    return 0;
}
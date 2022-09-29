#include<bits/stdc++.h>

using namespace std ;

const int N = 1e4 + 19 ;
int q[N] , cnt;
int l , r ;
int n , tar , f;

void dichotomy(int a[],int key,int l,int r){

	while(l <= r){
		int mid = (l + r) / 2 ;
		if(a[mid] > key) 
		{
			r = mid - 1;
			cnt ++;
		}
		else if(a[mid] < key) 
		{
			l = mid + 1;
			cnt ++;
		}
		else if(a[mid] == key) {
			cnt ++ ;
			f = 1 ;
			break ;
		}
	}
	if(f) {
		cout <<"目标值在数组中的位置为："<< l << "\n";
		cout << "\n" ;
		cout <<"查找次数为：" << cnt << "\n" ;
	}else {
		cout << "未找到该目标值" ;
		cout << "\n" ;
		cout <<"查找次数为：" << cnt << "\n" ;
	}
	return ;
}

int main(){
	cout << "输入数组大小:" ;
	cin >> n ;
	cout << "\n" ;
	cout << "输入数组的"<< n <<"个元素：" ;
	for(int i = 0 ; i < n ; i ++) cin >> q[i] ;
	cout << "\n" ;
	cout << "输入查找的目标值：";
	cin >> tar ;
	cout << "\n" ;
	dichotomy(q,tar,0,n-1) ;
	cout << "\n" ;
	return 0;
}

// //算法8.1 直接插入排序
// #include <iostream>
// using namespace std;
// #define  MAXSIZE  20          						//顺序表的最大长度
// typedef struct
// {
// 	int key;
// 	char *otherinfo;
// }ElemType;
// //顺序表的存储结构                         
// typedef struct
// {
//     ElemType *r;	         						//存储空间的基地址
//     int  length;            						//顺序表长度
// }SqList;											//顺序表类型

// void InsertSort(SqList &L)
// {
//    //对顺序表L做直接插入排序
// 	int i,j;
// 	for(i=2;i<=L.length;++i)
// 		if(L.r[i].key<L.r[i-1].key)
// 		{   										//"<"，需将r[i]插入有序子表
// 			L.r[0]=L.r[i];				 			//将待插入的记录暂存到监视哨中
//             L.r[i]=L.r[i-1];	            		//r[i-1]后移
//             for(j=i-2; L.r[0].key<L.r[j].key;--j)			//从后向前寻找插入位置
// 				L.r[j+1]=L.r[j];					//记录逐个后移，直到找到插入位置
//             L.r[j+1]=L.r[0];						//将r[0]即原r[i]，插入到正确位置
// 		}											//if
// }													//InsertSort

// void Create_Sq(SqList &L)
// {
// 	int i,n;
// 	cout<<"请输入数据个数，不超过"<<MAXSIZE<<"个。"<<endl;
// 	cin>>n;											//输入个数
// 	cout<<"请输入待排序的数据:\n";
// 	while(n>MAXSIZE)
// 	{
// 		cout<<"个数超过上限，不能超过"<<MAXSIZE<<"，请重新输入"<<endl;
// 		cin>>n;
// 	}
// 	for(i=1;i<=n;i++)
// 	{
// 		cin>>L.r[i].key;
// 		L.length++;
// 	}
// }
// void show(SqList L)
// {
// 	int i;
// 	for(i=1;i<=L.length;i++)
// 		cout<<L.r[i].key<<endl;
// }

// void main()
// {
// 	SqList L;
// 	L.r=new ElemType[MAXSIZE+1];
// 	L.length=0;
// 	Create_Sq(L);
// 	InsertSort(L);
// 	cout<<"排序后的结果为："<<endl;
// 	show(L);
// }
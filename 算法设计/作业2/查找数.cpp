#include <iostream>
 
using namespace std;
 
int tmp = 1;
 
int n, L, U;
 
int BinarySearch(int A[],int x, int l, int r)
{
	int mid = (l + r) / 2;
 
	cout<< x <<" " << l << " " << r << " " << A[mid]<< endl; 
	if (x == A[mid])
		return mid+tmp;
		
	else if (l == r || l == r-1) {
//		cout << l << tmp << endl;
		return (x-A[mid])>0 ? ((l-tmp)<n-1? mid+(tmp+1)/2 : n-1) : 0;//边界情况    找的都是小值 所以左边界... 
 
//		return (l-tmp)>-1 ? ((l-tmp)<n? mid+(tmp+1)/2 : n-1) : 0;//边界情况    找的都是小值 所以左边界... 
}
	return (x > A[mid]) ? BinarySearch(A, x, mid + 1, r) : BinarySearch(A, x, l, mid-1);
}
 
int main()
 
{
	cout << "请输入数组A的元素个数n" << endl;
 
	cin >> n;
 
	int *A = new int[n];
 
	//读入A
 
	cout << "请输入" << n << "个顺序的数组元素:" << endl;
 
	for (int i = 0; i < n; i++)
 
		cin >> A[i];
 
	while(1){
 
	cout << "请输入L和U"<<endl;
 
	cin >> L >> U;
	
	tmp = 1;
 
	int l = BinarySearch(A, L, 0, n-1);
 
	tmp = -1;
 
	int r = BinarySearch(A, U, 0, n-1);
 
	cout << "l="<<l <<" "<<"r="<< r<<endl;
 
	for (int i = l; i <= r; i++)
 
		cout << A[i] << " ";
 
	cout << endl; 
 
	}
 
    return 0; 
 
}
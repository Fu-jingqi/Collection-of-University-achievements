#include<iostream>
#include<fstream>
using namespace std;
int c=0;
void move(char x,int n,char z)
{cout<<++c<<","<<n<<","<<x<<","<<z<<endl;}
void Hanoi(int n,char A,char B,char C)
{ if(n==1) move(A,1,C);
  else
  {Hanoi(n-1,A,C,B); 
   move(A,n,C);
   Hanoi(n-1,B,A,C);  }}
int main(){Hanoi(3,'a','b','c');
return 0; 
}


#include <iostream>
#include <string>
#include <cstring> 
using namespace std;
int S_cnt;
int R_cnt;
int C_cnt;
int R_cnt2;
int C_cnt2; 
int S_cnt2; 
double S_P; 
double R_P; 
double C_P; 
double S_P2; 
double R_P2; 
double C_P2; 
double S_P3; 
double R_P3; 
double C_P3; 
void solve()
{
	S_cnt = 0;
	R_cnt = 0;
	C_cnt = 0;
	S_cnt2 = 0;
	R_cnt2 = 0;
	C_cnt2 = 0;
	char c;
	bool flag = false; 
	cout << "请输入近三十天天气情况（S代表晴天，R代表雨天，C代表多云）：";
	for (int i = 0; i < 30; ++i)
	{
		cin >> c;
		if(c == 'S') ++ S_cnt ;
		else if(c == 'R') ++ R_cnt ;
		else if(c == 'C') ++ C_cnt ;
		if (flag)
		{
			if(c == 'S') ++ S_cnt2 ;
			if(c == 'R') ++ R_cnt2 ;
			if(c == 'C') ++ C_cnt2 ;	
		}
		if (c == 'R') flag = true;
		else flag = false;
	}
	S_P = S_cnt / 30.0;
	C_P = C_cnt / 30.0;
	R_P = R_cnt / 30.0;
	
	S_P2 = S_cnt2*1.0 / R_cnt;
	C_P2 = C_cnt2*1.0 / R_cnt;
	R_P2 = R_cnt2 *1.0/ R_cnt;

	S_P3 = (S_P2 * R_P) / S_P;
	C_P3 = (C_P2 * R_P) / C_P;
	R_P3 = (R_P2 * R_P) / R_P;
}
int main()
{
	// SSSSC CRRSS SSCCR SCRRR CCCRS SSCRS
	solve();
	cout << "请输入今天天气(以便我们帮您预测明天出现雨天的概率):";
	char D;
	cin >> D;
	cout << "明天出现雨天的概率为：";
	if(D == 'S') cout << S_P3 << endl ;
	if(D == 'R') cout << R_P3 << endl ;
	if(D == 'C') cout << C_P3 << endl ;


	return 0;
}
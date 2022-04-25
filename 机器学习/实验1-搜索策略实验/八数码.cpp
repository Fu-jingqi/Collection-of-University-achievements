#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

char d[5] = "drul";
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int cnt = 0;
int cnt_a = 0 ;
string ed = "123804765";

unordered_map<string, int> p;
unordered_map<string, string> pp;

bool bfs(string s)
{
    queue<string> q;

    q.push(s);
    p[s] = 0;

    while (q.size())
    {
        string sh = q.front();
        q.pop();
        string h = sh;

        if (sh == ed) return true;

        int k = sh.find('0');
        int x = k / 3, y = k % 3;
        for (int i = 0; i < 4; i ++ )
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {

                int t = a * 3 + b;
                swap(sh[k], sh[t]);
                if (!p.count(sh))
                {
                    p[sh] = i;
                    pp[sh] = h;
                    q.push(sh);
                }
                swap(sh[t], sh[k]);
            }
        }
    }

    return false;
}

void Left_shift(string &a, int &b){
    int len = a.size() ;
    int f = 0 ;
    for(int i = 0 ; i < len ; i ++)
    {
        if(a[i] == '0')
        {
            f = i;
            break;
        }
    }
    swap(a[f],a[f-1]);
    cnt ++;
    cout << "**步数" << cnt <<endl ;
    cout << "|    "<< a[0] << "     " << a[1] << "     " << a[2] << "    |" << endl ;
    cout << "|    "<< a[3] << "     " << a[4] << "     " << a[5] << "    |" << endl ;
    cout << "|    "<< a[6] << "     " << a[7] << "     " << a[8] << "    |" << endl ;

}

void Right_shift(string &a, int &b){
    int len = a.size() ;
    int f = 0 ;
    for(int i = 0 ; i < len ; i ++)
    {
        if(a[i] == '0')
        {
            f = i;
            break;
        }
    }
    swap(a[f],a[f+1]);
    cnt ++;
    cout << "**步数" << cnt <<endl ;
    cout << "|    "<< a[0] << "     " << a[1] << "     " << a[2] << "    |" << endl ;
    cout << "|    "<< a[3] << "     " << a[4] << "     " << a[5] << "    |" << endl ;
    cout << "|    "<< a[6] << "     " << a[7] << "     " << a[8] << "    |" << endl ;
}

void Up_shift(string &a, int &b){
    int len = a.size() ;
    int f = 0 ;
    for(int i = 0 ; i < len ; i ++)
    {
        if(a[i] == '0')
        {
            f = i;
            break;
        }
    }
    int xi = f / 3 , yi = f % 3 ;
    int ff = (xi - 1) * 3 + yi ;
    swap(a[ff] , a[f]);
    cnt ++;
    cout << "**步数" << cnt <<endl ;
    cout << "|    "<< a[0] << "     " << a[1] << "     " << a[2] << "    |" << endl ;
    cout << "|    "<< a[3] << "     " << a[4] << "     " << a[5] << "    |" << endl ;
    cout << "|    "<< a[6] << "     " << a[7] << "     " << a[8] << "    |" << endl ;
}

void Down_shift(string &a, int &b){
    int len = a.size() ;
    int f = 0 ;
    for(int i = 0 ; i < len ; i ++)
    {
        if(a[i] == '0')
        {
            f = i;
            break;
        }
    }
    int xi = f / 3 , yi = f % 3 ;
    int ff = (xi + 1) * 3 + yi ;
    swap(a[ff] , a[f]);
    cnt ++;
    cout << "**步数" << cnt <<endl ;
    cout << "|    "<< a[0] << "     " << a[1] << "     " << a[2] << "    |" << endl ;
    cout << "|    "<< a[3] << "     " << a[4] << "     " << a[5] << "    |" << endl ;
    cout << "|    "<< a[6] << "     " << a[7] << "     " << a[8] << "    |" << endl ;
}

int Differences(string str1,string str2){
    int len = str1.size(),count = 0;
    for(int i = 0 ; i < len ; i ++){
        if(str1[i] != str2[i]) count ++ ;
    }
    return count ;
}

int main()
{
    string s, c;
    s = "283164705";
    cout << "请输入初始状态的八数码:" <<endl ;
    cout <<"|    2     8     3    |" << endl ;
    cout <<"|    1     6     4    |" << endl ;
    cout <<"|    7     0     5    |" << endl ;
    cnt_a = Differences(s,ed);
    cout << "差距：" << cnt_a << endl ;
    c = s ;
    cout << endl ;
    cout << "请输入最终状态的八数码:" <<endl ;
    cout <<"|    1     2     3    |" << endl ;
    cout <<"|    8     0     4    |" << endl ;
    cout <<"|    7     6     5    |" << endl ;
    cnt_a = Differences(ed,ed);
    cout << "差距：" << cnt_a << endl ;
    // for (int i = 0; i < 9; i ++ ) cin >> c1, ed += c1;
    cout << endl ;
    if (bfs(s))
    {
        vector<char> arr;
        string t = ed;
        while(t != s)
        {
            arr.push_back(d[p[t]]);  //将移动方式存下
            t = pp[t];
        }
        cout << "^^^搜索结果：^^^"<< endl ;
        cout << "**步数" << "0" <<endl ;
        cout <<"|    2     8     3    |" << endl ;
        cout <<"|    1     6     4    |" << endl ;
        cout <<"|    7     0     5    |" << endl ;
        cout << "差距：" << "5" << endl ;
        cout << endl ;cout << "------------" << endl;
        for (int i = arr.size() - 1; i >= 0; i -- )
        {
            if(arr[i] == 'l')
            {
                Left_shift(s,cnt) ;
                cnt_a = Differences(s,ed);
                cout << "差距：" << cnt_a << endl ;
                cout << endl ;cout << "------------" << endl;
            }
            else if(arr[i] == 'r') {
                Right_shift(s,cnt) ;
                cnt_a = Differences(s,ed);
                cout << "差距：" << cnt_a << endl ;
                cout << endl ;cout << "------------" << endl;
            }
            else if(arr[i] == 'u') {
                Up_shift(s,cnt) ;
                cnt_a = Differences(s,ed);
                cout << "差距：" << cnt_a << endl ;
                cout << endl ;cout << "------------" << endl;
            }
            else if(arr[i] == 'd') {
                Down_shift(s,cnt) ;
                cnt_a = Differences(s,ed);
                cout << "差距：" << cnt_a << endl ;
                cout << endl ;cout << "------------" << endl;
            }
        }

        cout << endl;
    }
    else cout << "unsolvable" << endl;
    return 0;
}



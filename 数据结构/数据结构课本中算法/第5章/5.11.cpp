//算法5.11 根据赫夫曼树求赫夫曼编码
#include<bits/stdc++.h>
using namespace std;
typedef struct
{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
int n,s1,s2,m,i,j,count2;

    /*  初始化：动态申请2*n个单元；然后循环2n-1次，
     *  从1号单元开始，依次将1至2n-1所有单元的双亲
     *  ，左孩子，右孩子的下标都初始化为0;最后再循
     *  环n次，输入前n个单元中叶子结点的权值。
     */

    /*  创建树：循环n-1次，通过n-1次循环，删除与合并
     *  来创建哈夫曼树。选择是从当前森林中选择双亲为0
     *  且权值最小的两个数根结点s1和s2；删除是指将结
     *  点s1和s2的双亲改为非0；合并就是将s1和s2的权
     *  值和作为一个新节点的权值依次存入到数组的第n+1
     *  之后的单元中，同时记录这个新结点左孩子的下标为
     *  s1，右孩子下标为s2。
     */

// select函数的作用：
/*
	得到s1和s2，找到没有被使用的结点里最小的和第二小的结点
	HT[s1].weight是所有权值里最小的
	HT[s2].weight是所有权值第二小的
*/
void Select(HuffmanTree HT,int len,int &s1,int &s2){
	// len为结点个数
	int min1=0x3f3f3f3f,min2=0x3f3f3f3f;//先赋予最大值
	// 在此循环中，遍历得到最小的结点的权重（min1）和它的下标（s1）
	for(int i=1;i<=len;i++)
	{
		if(HT[i].weight<min1&&HT[i].parent==0)


		{
			min1=HT[i].weight;
			s1=i;
		}	
	}
	int temp=HT[s1].weight;//将原值存放起来，然后先赋予最大值，防止s1被重复选择
	// 找到权重第二小的结点
	HT[s1].weight=0x3f3f3f3f;
	for(int i=1;i<=len;i++){
		if(HT[i].weight<min2&&HT[i].parent==0){
			min2=HT[i].weight;
			s2=i;
		}
	}
	HT[s1].weight=temp;//恢复原来的值
}

// 构造赫夫曼树
void CreatHuffmanTree(HuffmanTree &HT,int n){
	//构造赫夫曼树HT
	int m,s1,s2,i;
	if(n<=1) return;
	m=2*n-1;					// 一棵有n个叶子节点的赫夫曼树共有2n-1个节点
	HT=new HTNode[m+1];  		// 0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点   
	for(i=1;i<=m;++i)        	// 将1~m号单元中的双亲、左孩子，右孩子的下标都初始化为0   
	   { HT[i].parent=0;  HT[i].lchild=0;  HT[i].rchild=0; }
	cout<<"请输入叶子结点的权值：\n";
	for(i=1;i<=n;++i)        	// 输入前n个单元中叶子结点的权值  
		cin>>HT[i].weight;  
	/*――――――――――初始化工作结束，下面开始创建赫夫曼树――――――――――*/ 
	for(i=n+1;i<=m;++i) {  		//通过n-1次的选择、删除、合并来创建赫夫曼树
		Select(HT,i-1,s1,s2);
		//在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点,
		// 并返回它们在HT中的序号s1和s2
		HT[s1].parent=i; 	
		HT[s2].parent=i;   
		//得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为i
		HT[i].lchild=s1;   
		HT[i].rchild=s2 ;							//s1,s2分别作为i的左右孩子
		HT[i].weight=HT[s1].weight+HT[s2].weight; 	//i 的权值为左右孩子权值之和
	}
}	
	// CreatHuffmanTree
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
	//从叶子到根逆向求每个字符的赫夫曼编码，存储在编码表HC中
	int i,start,c,f;
	HC=new char*[n+1];         						//分配n个字符编码的头指针矢量
	char *cd=new char[n];							//分配临时存放编码的动态数组空间
	cd[n-1]='\0';                            		//编码结束符
	for(i=1;i<=n;++i){                      							//逐个字符求赫夫曼编码
		start=n-1;                          		//start开始时指向最后，即编码结束符位置
		c=i; 
		f=HT[i].parent;                 			//f指向结点c的双亲结点
		while(f!=0){                          					//从叶子结点开始向上回溯，直到根结点
			--start;                          		//回溯一次start向前指一个位置
			if(HT[f].lchild==c)  
				cd[start]='0';						//结点c是f的左孩子，则生成代码0
			else 
				cd[start]='1';                 		//结点c是f的右孩子，则生成代码1
			c=f; 
			f=HT[f].parent;             			//继续向上回溯
		}                                  			//求出第i个字符的编码      
		HC[i]=new char[n-start];         			// 为第i 个字符编码分配空间
		strcpy(HC[i], &cd[start]);        			//将求得的编码从临时空间cd复制到HC的当前行中
	}
	delete cd;                            			//释放临时空间
}

void TransCode(HuffmanTree HT,char a[],char ch[],char b[],int n){
    count2=0;
    int q=2*n-1;
    int k=0;
    for(int i=0; a[i]!='%'; i++)
    {
        if(a[i]=='0')
        {
            q=HT[q].lchild;
        }
        else if(a[i]=='1')
        {
            q=HT[q].rchild;
        }
        if(HT[q].lchild==0 && HT[q].rchild==0)
        {
            b[k++]=ch[q-1];
            q=2*n-1;
        }
    }
    count2=k;
    b[k]='\0';
}
void show(){
	cout<<"********************************************************************"<<endl;
    cout<<"********* 1.输入HuffmanTree的参数.                        **********"<<endl;
    cout<<"********* 2.初始化HuffmanTree参数(含有26字母及空格).      **********"<<endl;
    cout<<"********* 3.创建HuffmanTree和编码表.                      **********"<<endl;
    cout<<"********* 4.输出编码表.                                   **********"<<endl;
    cout<<"********* 5.输入编码，并翻译为字符.                       **********"<<endl;
    cout<<"********* 6.输入字符，并实现编码.                         **********"<<endl;
    cout<<"********* 7.退出.                                         **********"<<endl;
    cout<<"********* 以%为结束标识                                   **********"<<endl;
    cout<<"********************************************************************"<<endl;
}
int main(){
    /*<--测试样例-->*/
    // I love you
    // 01101111011110011100000010111100011100100001
    
    // 01101101111011000111111010111101101001100001
    // it is a dog

	HuffmanTree HT;
    HuffmanCode HC;
    int OpCode;
    int count1=0;
    char a[1000];
    char b[1000];
    char c[1000];
    char ch[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
    show();
    bool flag=true;
    while(flag)
    {
        cout<<"请输入操作码:"<<endl;
        cin>>OpCode;
        if(OpCode==1)
        {
            cout<<"请输入编码字符个数: ";
            cin>>n;
        }
        else if(OpCode==2)
        {
            cout<<"请输入权值: ";
            CreatHuffmanTree(HT,n);
        }
        else if(OpCode==3)
        {
            CreatHuffmanCode(HT,HC,n);
        }
        else if(OpCode==4)
        {
            cout<<"结点"<<"\t"<<"字符"<<"\t"<<"权值"<<"\t"<<"编码"<<endl;
            for(int i=1;i<=n;i++)
            {
                cout<<i<<"\t"<<ch[i-1]<<"\t"<< HT[i].weight<<"\t"<<HC[i]<<endl;
            }
            cout<<endl;
        }
        else if(OpCode==5)
        {
            cout<<"输入二进制编码: ";
            for(i=0;i<1000;i++)
            {
                cin>>a[i];
                char data = a[i];
                if(a[i]=='%')
                {
                    break;
                }

            }
            TransCode(HT,a,ch,b,n);
            cout<<"输出: ";
            for(i=0;i<count2;i++)
            {
                cout<<b[i];
            }
            cout<<endl;
        }
        else if(OpCode==6)
        {
            count1=0;
            cout<<"请输入一串字符: ";
            for(i=0;i<1000;i++)
            {
                cin>>c[i];
                char data = c[1];
                count1++;
                if(c[i]=='%')
                {
                    break;
                }
            }
            cout<<"输出: ";
            for(i=0;i<count1-1;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(c[i]==ch[j])
                    {
                        cout<<HC[j+1];
                        break;
                    }
                }
            }
            cout<<endl;
        }
        else if(OpCode==7)
        {
            flag=false;
        }
    }
    return 0;
}

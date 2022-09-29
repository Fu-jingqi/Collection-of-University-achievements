//�㷨5.11 ���ݺշ�������շ�������
#include<bits/stdc++.h>
using namespace std;
typedef struct
{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
int n,s1,s2,m,i,j,count2;

    /*  ��ʼ������̬����2*n����Ԫ��Ȼ��ѭ��2n-1�Σ�
     *  ��1�ŵ�Ԫ��ʼ�����ν�1��2n-1���е�Ԫ��˫��
     *  �����ӣ��Һ��ӵ��±궼��ʼ��Ϊ0;�����ѭ
     *  ��n�Σ�����ǰn����Ԫ��Ҷ�ӽ���Ȩֵ��
     */

    /*  ��������ѭ��n-1�Σ�ͨ��n-1��ѭ����ɾ����ϲ�
     *  ����������������ѡ���Ǵӵ�ǰɭ����ѡ��˫��Ϊ0
     *  ��Ȩֵ��С�������������s1��s2��ɾ����ָ����
     *  ��s1��s2��˫�׸�Ϊ��0���ϲ����ǽ�s1��s2��Ȩ
     *  ֵ����Ϊһ���½ڵ��Ȩֵ���δ��뵽����ĵ�n+1
     *  ֮��ĵ�Ԫ�У�ͬʱ��¼����½�����ӵ��±�Ϊ
     *  s1���Һ����±�Ϊs2��
     */

// select���������ã�
/*
	�õ�s1��s2���ҵ�û�б�ʹ�õĽ������С�ĺ͵ڶ�С�Ľ��
	HT[s1].weight������Ȩֵ����С��
	HT[s2].weight������Ȩֵ�ڶ�С��
*/
void Select(HuffmanTree HT,int len,int &s1,int &s2){
	// lenΪ������
	int min1=0x3f3f3f3f,min2=0x3f3f3f3f;//�ȸ������ֵ
	// �ڴ�ѭ���У������õ���С�Ľ���Ȩ�أ�min1���������±꣨s1��
	for(int i=1;i<=len;i++)
	{
		if(HT[i].weight<min1&&HT[i].parent==0)


		{
			min1=HT[i].weight;
			s1=i;
		}	
	}
	int temp=HT[s1].weight;//��ԭֵ���������Ȼ���ȸ������ֵ����ֹs1���ظ�ѡ��
	// �ҵ�Ȩ�صڶ�С�Ľ��
	HT[s1].weight=0x3f3f3f3f;
	for(int i=1;i<=len;i++){
		if(HT[i].weight<min2&&HT[i].parent==0){
			min2=HT[i].weight;
			s2=i;
		}
	}
	HT[s1].weight=temp;//�ָ�ԭ����ֵ
}

// ����շ�����
void CreatHuffmanTree(HuffmanTree &HT,int n){
	//����շ�����HT
	int m,s1,s2,i;
	if(n<=1) return;
	m=2*n-1;					// һ����n��Ҷ�ӽڵ�ĺշ���������2n-1���ڵ�
	HT=new HTNode[m+1];  		// 0�ŵ�Ԫδ�ã�������Ҫ��̬����m+1����Ԫ��HT[m]��ʾ�����   
	for(i=1;i<=m;++i)        	// ��1~m�ŵ�Ԫ�е�˫�ס����ӣ��Һ��ӵ��±궼��ʼ��Ϊ0   
	   { HT[i].parent=0;  HT[i].lchild=0;  HT[i].rchild=0; }
	cout<<"������Ҷ�ӽ���Ȩֵ��\n";
	for(i=1;i<=n;++i)        	// ����ǰn����Ԫ��Ҷ�ӽ���Ȩֵ  
		cin>>HT[i].weight;  
	/*�D�D�D�D�D�D�D�D�D�D��ʼ���������������濪ʼ�����շ������D�D�D�D�D�D�D�D�D�D*/ 
	for(i=n+1;i<=m;++i) {  		//ͨ��n-1�ε�ѡ��ɾ�����ϲ��������շ�����
		Select(HT,i-1,s1,s2);
		//��HT[k](1��k��i-1)��ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ��,
		// ������������HT�е����s1��s2
		HT[s1].parent=i; 	
		HT[s2].parent=i;   
		//�õ��½��i����ɭ����ɾ��s1��s2����s1��s2��˫������0��Ϊi
		HT[i].lchild=s1;   
		HT[i].rchild=s2 ;							//s1,s2�ֱ���Ϊi�����Һ���
		HT[i].weight=HT[s1].weight+HT[s2].weight; 	//i ��ȨֵΪ���Һ���Ȩֵ֮��
	}
}	
	// CreatHuffmanTree
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
	//��Ҷ�ӵ���������ÿ���ַ��ĺշ������룬�洢�ڱ����HC��
	int i,start,c,f;
	HC=new char*[n+1];         						//����n���ַ������ͷָ��ʸ��
	char *cd=new char[n];							//������ʱ��ű���Ķ�̬����ռ�
	cd[n-1]='\0';                            		//���������
	for(i=1;i<=n;++i){                      							//����ַ���շ�������
		start=n-1;                          		//start��ʼʱָ����󣬼����������λ��
		c=i; 
		f=HT[i].parent;                 			//fָ����c��˫�׽��
		while(f!=0){                          					//��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֱ�������
			--start;                          		//����һ��start��ǰָһ��λ��
			if(HT[f].lchild==c)  
				cd[start]='0';						//���c��f�����ӣ������ɴ���0
			else 
				cd[start]='1';                 		//���c��f���Һ��ӣ������ɴ���1
			c=f; 
			f=HT[f].parent;             			//�������ϻ���
		}                                  			//�����i���ַ��ı���      
		HC[i]=new char[n-start];         			// Ϊ��i ���ַ��������ռ�
		strcpy(HC[i], &cd[start]);        			//����õı������ʱ�ռ�cd���Ƶ�HC�ĵ�ǰ����
	}
	delete cd;                            			//�ͷ���ʱ�ռ�
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
    cout<<"********* 1.����HuffmanTree�Ĳ���.                        **********"<<endl;
    cout<<"********* 2.��ʼ��HuffmanTree����(����26��ĸ���ո�).      **********"<<endl;
    cout<<"********* 3.����HuffmanTree�ͱ����.                      **********"<<endl;
    cout<<"********* 4.��������.                                   **********"<<endl;
    cout<<"********* 5.������룬������Ϊ�ַ�.                       **********"<<endl;
    cout<<"********* 6.�����ַ�����ʵ�ֱ���.                         **********"<<endl;
    cout<<"********* 7.�˳�.                                         **********"<<endl;
    cout<<"********* ��%Ϊ������ʶ                                   **********"<<endl;
    cout<<"********************************************************************"<<endl;
}
int main(){
    /*<--��������-->*/
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
        cout<<"�����������:"<<endl;
        cin>>OpCode;
        if(OpCode==1)
        {
            cout<<"����������ַ�����: ";
            cin>>n;
        }
        else if(OpCode==2)
        {
            cout<<"������Ȩֵ: ";
            CreatHuffmanTree(HT,n);
        }
        else if(OpCode==3)
        {
            CreatHuffmanCode(HT,HC,n);
        }
        else if(OpCode==4)
        {
            cout<<"���"<<"\t"<<"�ַ�"<<"\t"<<"Ȩֵ"<<"\t"<<"����"<<endl;
            for(int i=1;i<=n;i++)
            {
                cout<<i<<"\t"<<ch[i-1]<<"\t"<< HT[i].weight<<"\t"<<HC[i]<<endl;
            }
            cout<<endl;
        }
        else if(OpCode==5)
        {
            cout<<"��������Ʊ���: ";
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
            cout<<"���: ";
            for(i=0;i<count2;i++)
            {
                cout<<b[i];
            }
            cout<<endl;
        }
        else if(OpCode==6)
        {
            count1=0;
            cout<<"������һ���ַ�: ";
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
            cout<<"���: ";
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

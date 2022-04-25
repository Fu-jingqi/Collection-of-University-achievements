#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int width = 10; //��ͼ�Ĵ�С
const int height = 10;
const int FAIL = -99;
const int BLOCK = 1; //�ϰ�
const int WALK = 0; //�����ߵ�·
const int PATH = 2; //���ó���·��
const int offseti[8]{ -1,-1,-1,0,0,1,1,1 }; //8����ƫ����
const int offsetj[8]{ -1,0,1,-1,1,-1,0,1 };

class Node
{
public:
	bool inOpenList = false; //�Ƿ���OpenList��
	bool inCloseList = false; //�Ƿ���CloseList��

	bool walkable = true;

	int i, j;

	Node *pre; //���ڵ� ���ͨ������õ�����·��

	float G = 99; //Gֵ����㵽��ǰ�ڵ�Ĵ���
	float H = 99; //Hֵ����ǰ�ڵ㵽�յ��Ԥ������,�����ϰ����б��
	float fn = 99; //F(n) = G+H ����ѡ����һ���ڵ�

	void UpdateFn() { fn = G + H; }

	Node(int _i, int _j) :i(_i), j(_j) {};
	Node() {};
	~Node() {};
};


inline void ShowNode(Node node)
{
	cout << " (" << node.i << "," << node.j << ")" << " ";
	cout << " inOpen: " << node.inOpenList;
	cout << " inClose: " << node.inCloseList;
	cout << " node data: " << node.G << " " << node.H << " " << node.fn;
	if (node.pre != NULL)
		cout << " (" << node.pre->i << "," << node.pre->j << ")";
	else
		cout << " pre:null";
	cout << endl;
}

inline void ShowMap(int map[][width])
{
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == 0)
				cout << " - ";
			else if (map[i][j] == BLOCK)
				cout << " # ";
			else if (map[i][j] == PATH)
				cout << " * ";
		}
		cout << endl;
	}

}

inline void ShowVec(vector<Node*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		ShowNode(*list[i]);
	}
	cout << endl;

}

//����n1��n2�Ĵ���(8����)
float Cost(const Node& n1,const Node& n2)
{
	//ֱ�����ڴ���Ϊ10
	if ((abs(n1.i - n2.i) == 1 && n1.j == n2.j || n1.i == n2.i && abs(n1.j - n2.j)) == 1)
		return 10;
	//б���ڴ���Ϊsqrt(10*10) = 14
	else if ((abs(n1.i - n2.i) == 1 && abs(n1.j - n2.j)) == 1)
		return 14;
	else
		return FAIL;
}

//ͨ��n1�õ�n2��G
float GetG(const Node& n1, const Node& n2)
{
	return Cost(n1, n2) + n1.G;
}

//�õ�Hֵ
float GetH(const Node& cur,const Node& end)
{
	return (abs(cur.i - end.i) + abs(cur.j - end.j)) * 10;
}

void AddToOpenList(Node* node, vector<Node*>& list)
{
	list.push_back(node);
	node->inOpenList = true;
	node->inCloseList = false;
}

void AddToCloseList(Node* node, vector<Node*>& list)
{
	list.push_back(node);
	node->inOpenList = false;
	node->inCloseList = true;
}

//��OpenList������СF(n)��������
int FindMinF_n(vector<Node*> nodes)
{
	if (nodes.size() == 0)
		return FAIL;
	float min = nodes[0]->fn;
	int idx = 0;
	for (int i = 1; i < nodes.size(); i++)
	{
		if (nodes[i]->fn < min)
		{
			min = nodes[i]->fn;
			idx = i;
		}
	}
	return idx;
}

//�Ե�ǰ�ڵ��8����ڵ���в���
void GetSurroundNode(Node* node, Node* nodes[][width], vector<Node*>& openList,const Node& end)
{
	for (int k = 0; k < 8; k++)
	{
		if ((node->i + offseti[k]) >= 0 && (node->i + offseti[k]) < height && (node->j + offsetj[k]) >= 0 && (node->j + offsetj[k]) < width)
		{
			//���Ϸ���
		}
		else
		{
			continue;
		}
		Node* temp = nodes[node->i + offseti[k]][node->j + offsetj[k]];
		if (temp->inCloseList || temp->walkable == false)
			continue;
		//����ڵ��Ѿ���OpenList��
		if (temp->inOpenList)
		{
			//ͨ����ǰ�ڵ����¼���Gֵ,����������G��С,���ڵ�ĸ��ڵ�����Ϊ��ǰ�ڵ�
			if (GetG(*node, *temp) < temp->G)
			{
				temp->G = GetG(*node, *temp);
				temp->pre = node;
				temp->UpdateFn();
			}
		}
		//����ڵ㲻��OpenList��,�ڵ�ĸ��ڵ�����Ϊ��ǰ�ڵ�,����G,H,F(n)ֵ������OpenList
		else if (!temp->inOpenList)
		{
			temp->pre = node;
			//cout << "temp";
			temp->G = GetG(*node, *temp);
			temp->H = GetH(*temp, end);
			temp->UpdateFn();
			AddToOpenList(temp, openList);
			//ShowNode(*temp);
		}

	}
}

//����Ƿ��յ��Ѿ�����OpenList,����Ǳ���Ѱ·����
bool CheckEnd(const vector<Node*>& openList, const Node& end)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->i == end.i&&openList[i]->j == end.j)
			return true;

	}
	return false;

}

//A*�㷨
void Astar(Node& start, Node& end, Node* nodes[][width], int map[][width])
{
	vector<Node*> openList;
	vector<Node*> closeList;
	//��������OpenList
	AddToOpenList(nodes[start.i][start.j], openList);

	while (!CheckEnd(openList, end))
	{
		//OpenList��Ѱ����СF(n)�Ľڵ�
		int minFnIdx = FindMinF_n(openList);

		Node* curNode = openList[minFnIdx];

		//����closeList
		AddToCloseList(curNode, closeList);

		//����OpenList�Ľڵ�
		openList.erase(openList.begin() + minFnIdx);

		//�����ڵ�8����
		GetSurroundNode(curNode, nodes, openList,end);

	}
	//���յ�ڵ�һ·��ѭ����·��
	Node* path = nodes[end.i][end.j];
	while (path != NULL)
	{
		map[path->i][path->j] = PATH;
		path = path->pre;
	}

}

int main()
{

	int map[height][width];
	cout << "input start point: " << endl;
	Node *start = new Node();
	cin >> start->i >> start->j;
	cout << "input end point: " << endl;
	Node *end = new Node();
	cin >> end->i >> end->j;
	Node* nodes[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			nodes[i][j] = new Node(i, j);
			//H�ǲ�����ֱ�ӳ�ʼ������
			nodes[i][j]->H = GetH(*nodes[i][j], *end);
		}
	}
	//������ʼ�ڵ�����
	nodes[start->i][start->j]->G = 0;
	nodes[start->i][start->j]->H = GetH(*start, *end);
	nodes[start->i][start->j]->UpdateFn();


	cout << "init map:" << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == BLOCK)
			{
				nodes[i][j]->walkable = false;
			}
		}
	}
	map[start->i][start->j] = PATH;
	map[end->i][end->j] = PATH;

	ShowMap(map);

	Astar(*start, *end, nodes, map);

	ShowMap(map);
    return 0;
}


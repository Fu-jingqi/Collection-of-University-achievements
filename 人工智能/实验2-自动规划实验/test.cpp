#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int width = 10; //地图的大小
const int height = 10;
const int FAIL = -99;
const int BLOCK = 1; //障碍
const int WALK = 0; //可以走的路
const int PATH = 2; //最后得出的路径
const int offseti[8]{ -1,-1,-1,0,0,1,1,1 }; //8邻域偏移量
const int offsetj[8]{ -1,0,1,-1,1,-1,0,1 };

class Node
{
public:
	bool inOpenList = false; //是否在OpenList中
	bool inCloseList = false; //是否在CloseList中

	bool walkable = true;

	int i, j;

	Node *pre; //父节点 最后通过这个得到最终路径

	float G = 99; //G值：起点到当前节点的代价
	float H = 99; //H值：当前节点到终点的预估代价,忽略障碍物和斜边
	float fn = 99; //F(n) = G+H 用来选择下一个节点

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

//计算n1到n2的代价(8邻域)
float Cost(const Node& n1,const Node& n2)
{
	//直接相邻代价为10
	if ((abs(n1.i - n2.i) == 1 && n1.j == n2.j || n1.i == n2.i && abs(n1.j - n2.j)) == 1)
		return 10;
	//斜相邻代价为sqrt(10*10) = 14
	else if ((abs(n1.i - n2.i) == 1 && abs(n1.j - n2.j)) == 1)
		return 14;
	else
		return FAIL;
}

//通过n1得到n2的G
float GetG(const Node& n1, const Node& n2)
{
	return Cost(n1, n2) + n1.G;
}

//得到H值
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

//在OpenList中找最小F(n)返回索引
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

//对当前节点的8邻域节点进行操作
void GetSurroundNode(Node* node, Node* nodes[][width], vector<Node*>& openList,const Node& end)
{
	for (int k = 0; k < 8; k++)
	{
		if ((node->i + offseti[k]) >= 0 && (node->i + offseti[k]) < height && (node->j + offsetj[k]) >= 0 && (node->j + offsetj[k]) < width)
		{
			//检测合法性
		}
		else
		{
			continue;
		}
		Node* temp = nodes[node->i + offseti[k]][node->j + offsetj[k]];
		if (temp->inCloseList || temp->walkable == false)
			continue;
		//如果节点已经在OpenList中
		if (temp->inOpenList)
		{
			//通过当前节点重新计算G值,如果计算出的G更小,将节点的父节点设置为当前节点
			if (GetG(*node, *temp) < temp->G)
			{
				temp->G = GetG(*node, *temp);
				temp->pre = node;
				temp->UpdateFn();
			}
		}
		//如果节点不在OpenList中,节点的父节点设置为当前节点,计算G,H,F(n)值并加入OpenList
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

//检查是否终点已经加入OpenList,如果是表明寻路结束
bool CheckEnd(const vector<Node*>& openList, const Node& end)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->i == end.i&&openList[i]->j == end.j)
			return true;

	}
	return false;

}

//A*算法
void Astar(Node& start, Node& end, Node* nodes[][width], int map[][width])
{
	vector<Node*> openList;
	vector<Node*> closeList;
	//将起点加入OpenList
	AddToOpenList(nodes[start.i][start.j], openList);

	while (!CheckEnd(openList, end))
	{
		//OpenList中寻找最小F(n)的节点
		int minFnIdx = FindMinF_n(openList);

		Node* curNode = openList[minFnIdx];

		//存入closeList
		AddToCloseList(curNode, closeList);

		//擦除OpenList的节点
		openList.erase(openList.begin() + minFnIdx);

		//操作节点8邻域
		GetSurroundNode(curNode, nodes, openList,end);

	}
	//从终点节点一路上循生成路径
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
			//H是不会变的直接初始化即可
			nodes[i][j]->H = GetH(*nodes[i][j], *end);
		}
	}
	//设置起始节点数据
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


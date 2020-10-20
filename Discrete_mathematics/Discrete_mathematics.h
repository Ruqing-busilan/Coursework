#include <iostream>
#include "stdio.h"
#include "iomanip"
#include "string"
#include "algorithm"
//#include "graphics.h"
#include <conio.h>

using namespace std;

#define Maxsize 100
#define INF 999999
#define PI 2*3.1415926535

char Vertex[Maxsize];             //顶点数组
int Vertexnum = 0;               //顶点数目
int Edgenum = 0;          //边数目
char path[Maxsize][Maxsize];      //最短路径数组

struct Edge
{
	int begin;        //边前顶点下标
	int end;              //边后顶点下标
};

struct Point
{
	int x;        //横坐标
	int y;              //纵坐标
};

void Input(int matrix[][Maxsize]);                     //输入
void M_Output(int matrix[][Maxsize]);                      //矩阵形式输出
void R_Output(int matrix[][Maxsize]);                 //关系形式输出
void Reflexivity(int matrix[][Maxsize]);                  //自反性判断
void Symmetry(int matrix[][Maxsize]);                 //对称性判断
void Transitivity(int matrix[][Maxsize]);                 //传递性判断
void Reflexive_closure(int matrix[][Maxsize]);        //自反闭包
void Symmetrical_closure(int matrix[][Maxsize]);         //对称闭包
void Transitive_closure(int matrix[][Maxsize]);            //传递闭包
void Adjacency_matrix(int matrix[][Maxsize]);         //邻接矩阵
void Reachable_matrix(int matrix[][Maxsize]);                 //可达矩阵
void Correlation_matrix(int matrix[][Maxsize]);         //关联矩阵
void Distance_matrix(int matrix[][Maxsize]);                     //距离矩阵
void Road_num(int matrix[][Maxsize]);                    //任何两个节点（元素）之间特定长度的路的数量
void Warshall(int matrix[][Maxsize]);               //Warshall算法
int Ver_Search(char ch);                              //搜索顶点
void add_ver(char ch);                         // 在顶点数组添加顶点
void graph(int matrix[][Maxsize]);


void Input(int matrix[][Maxsize])
{
	for (int i = 0; i < Maxsize; i++)
		for (int j = 0; j < Maxsize; j++)
			matrix[i][j] = 0;
	cout << "请输入关系（以a,b形式,以*,*结束）：" << endl;
	char V1, V2, ch;
	while (cin >> V1 >> ch >> V2, V1 != '*'&&V2 != '*')
	{
		Edgenum++;
		int i, j;
		add_ver(V1);                   //添加V1是否在顶点数组
		add_ver(V2);
		i = Ver_Search(V1);            //搜索V1在顶点数组位置
		j = Ver_Search(V2);
		matrix[i][j] = 1;
		/*cout << "请输入下一个节点关系：" << endl;*/
	}
//	cout << "节点关系数目：" << Edgenum << endl;
//	cout << "顶点数目为：" << Vertexnum << endl;
//	cout << "是否需要转换为无向图？（Y/N）：" << endl;
//	cin >> ch;
//	if (ch == 'Y' || ch == 'y')
//	{
//		for (int i = 0; i < Vertexnum; i++)
//			for (int j = 0; j < Vertexnum; j++)
//				if (matrix[i][j] == 1)
//				{
//					matrix[j][i] = 1;
//				}
//	}
//	else
//		cout << "此图为有向图！" << endl;
//	getchar();
//	graph(matrix);
}

void graph(int matrix[][Maxsize])
{
//
//    Point *p;
//	p = new Point[Vertexnum];
//	initgraph(640, 480);    // 初始化图形模式
//	double a = -PI/4;
//	for (int i = 0; i < Vertexnum; i++)
//	{
//		p[i].x = int(280 + cos(a) * 100);
//		p[i].y = int(280 + sin(a) * 100);
//		fillcircle(p[i].x, p[i].y, 5);
//		outtextxy(p[i].x + 1, p[i].y + 1, Vertex[i]);
//		Sleep(150);
//		a += PI/ Vertexnum;
//	}
//	for (int i = 0; i < Vertexnum; i++)
//		for (int j = 0; j < Vertexnum; j++)
//		{
//			if (matrix[i][j] == 1)
//			{
//				line(p[i].x, p[i].y, p[j].x, p[j].y);
//				Sleep(150);
//			}
//		}
//	getchar();
//	getchar();
//	closegraph();          // 关闭图形模式
}
void Reflexivity(int matrix[][Maxsize])
{
	int flag = 0;
	for (int i = 0; i < Vertexnum; i++)
		if (matrix[i][i] == 1)
			flag++;                     //自反结点数目flag+1
	if (flag == Vertexnum)
		cout << "具有自反关系" << endl;
	else
		cout << "不具有自反关系" << endl;
}

void Symmetry(int matrix[][Maxsize])
{
	int flag = 1;
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == 1 && matrix[j][i] != 1)
			{
				flag--;                           //若存在节点关系不满足对称性关系flag-1
			}
		}
	if (flag == 1)
		cout << "具有对称关系" << endl;
	else
		cout << "不具有对称关系" << endl;
}

void Transitivity(int matrix[][Maxsize])
{
	int flag = 1;
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == 1)
			{
				for (int k = 0; k < Vertexnum; k++)
					if (matrix[j][k] == 1)
					{
						if (matrix[i][k] != 1)            //若节点关系不满足传递在flag-1
							flag--;
					}
			}
		}
	if (flag == 1)
		cout << "具有传递关系" << endl;
	else
		cout << "不具有传递关系" << endl;
}

void Reflexive_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                //创建一个新矩阵，不破坏原有矩阵
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			if (temp[i][j] == 1)              //若a,b有关系，创建a,a与b,b的关系
			{
				temp[i][i] = 1;
				temp[j][j] = 1;
			}
	cout << "自反闭包：";
	R_Output(temp);
}

void Symmetrical_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //创建一个新矩阵，不破坏原有矩阵
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			if (temp[i][j] == 1)
				temp[j][i] = 1;                      //若a,b有关系，创建b,a的关系
	cout << "对称闭包：";
	R_Output(temp);
}

void Transitive_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //创建一个新矩阵，不破坏原有矩阵
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	Warshall(temp);
	cout << "传递闭包：";
	R_Output(temp);
}

void Adjacency_matrix(int matrix[][Maxsize])
{
	cout << "邻接矩阵：" << endl;
	M_Output(matrix);
}

void Reachable_matrix(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //创建一个新矩阵，不破坏原有矩阵
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	Warshall(temp);
	cout << "可达矩阵：" << endl;
	M_Output(temp);
}

void Correlation_matrix(int matrix[][Maxsize])
{
	Edge *e;
	e = new Edge[Edgenum];
	int **cor_matrix;
	cor_matrix = new int*[Vertexnum];
	for (int i = 0; i < Vertexnum; i++)
		cor_matrix[i] = new int[Edgenum];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Edgenum; j++)
			cor_matrix[i][j] = 0;
	int k = 0;
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == 1)
			{
				e[k].begin = i;
				e[k].end = j;
				k++;
			}
		}
	for (int i = 0; i < Edgenum; i++)
	{
		cor_matrix[e[i].begin][i] = 1;
		cor_matrix[e[i].end][i] = 1;
	}
	cout << "关联矩阵（用两个顶点表示边）：" << endl;
	int flag;
	cout << "  " << Vertex[e[0].begin] << Vertex[e[0].end];
	for (int i = 1; i < Edgenum - 1; i++)
		cout << " " << Vertex[e[i].begin] << Vertex[e[i].end];
	cout << " " << Vertex[e[Edgenum - 1].begin] << Vertex[e[Edgenum - 1].end] << endl;
	for (int i = 0; i < Vertexnum; i++)
	{
		cout << Vertex[i] << " ";
		flag = 0;
		for (int j = 0; j < Edgenum; j++)
		{
			cout << cor_matrix[i][j] << "  ";
			flag++;
			if (flag == Edgenum)
				cout << endl;
		}
	}
}

void Distance_matrix(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == 0)
			{
				path[i][j] = ' ';
				if (i == j)
					temp[i][j] = 0;
				else
					temp[i][j] = INF;
			}
			else
			{
				temp[i][j] = matrix[i][j];
				path[i][j] = Vertex[i];         //如果图中存在路径，储存前一个顶点
			}
		}
	for (int k = 0; k < Vertexnum; k++)
		for (int i = 0; i < Vertexnum; i++)
			for (int j = 0; j < Vertexnum; j++)
			{
				if (temp[i][k] + temp[k][j] < temp[i][j])
				{
					temp[i][j] = temp[i][k] + temp[k][j];
					path[i][j] = path[k][j];                 //可用于输出最短路径
				}
			}
	cout << "距离矩阵：" << endl;
	M_Output(temp);
}

void Road_num(int matrix[][Maxsize])
{
    int temp[Maxsize][Maxsize];                       //创建一个新矩阵，不破坏原有矩阵
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];  
	int trans[Maxsize][Maxsize];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			trans[i][j] = 0;                   		
	int n, index1, index2, t = 0;
	char V1, V2;
	cout << "输入两个顶点(顶点之间用空格隔开，请勿使用其他字符)：" << endl;
	cin >> V1 >> V2;
	index1 = Ver_Search(V1);
	index2 = Ver_Search(V2);
	cout << "输入长度：" << endl;
	cin >> n;
	for (int m = 0; m < n - 1; m++)
	{
		for (int i = 0; i < Vertexnum; i++)
		{
			int flag=0; 
			for (int j = 0; j < Vertexnum; j++)
			{
				t=0;
				for (int k = 0; k < Vertexnum; k++)
				{
					t += matrix[i][k] * temp[k][j];
					cout<<t<<" ";
					flag++;
					 if(flag==Vertexnum) 
					 {
					 	flag=0;
					 	cout<<endl; 
					 }
				}
				trans[i][j]=t;
			}
		}
		for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = trans[i][j]; 
	}
	M_Output(trans); 
	cout << "顶点" << V1 << "与顶点" << V2 << "长度为" << n << "的数量为:  " << trans[index1][index2] << endl;
}

void Warshall(int matrix[][Maxsize])
{
	for (int j = 0; j < Vertexnum; j++)
		for (int i = 0; i < Vertexnum; i++)
			if (matrix[i][j] == 1)
			{
				for (int k = 0; k < Vertexnum; k++)
				{
					matrix[i][k] = matrix[i][k] | matrix[j][k];     //或运算
				}
			}
}

void M_Output(int matrix[][Maxsize])
{
	int flag;
	cout << "  " << Vertex[0];
	for (int i = 1; i < Vertexnum - 1; i++)
		cout << " " << Vertex[i];
	cout << " " << Vertex[Vertexnum - 1] << endl;
	for (int i = 0; i < Vertexnum; i++)
	{
		cout << Vertex[i] << " ";
		flag = 0;
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == INF)
				cout << "∞";
			else
				cout << matrix[i][j] << " ";
			flag++;
			if (flag == Vertexnum)
				cout << endl;
		}
	}
}

void R_Output(int matrix[][Maxsize])
{
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			if (matrix[i][j] == 1)
			{
				cout << '<' << Vertex[i] << ',' << Vertex[j] << '>' << " ";
			}
	cout << endl;
}

int Ver_Search(char ch)
{
	for (int i = 0; i < Vertexnum; i++)
	{
		if (Vertex[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

void add_ver(char ch)
{
	int k;
	for (k = 0; k < Vertexnum + 1; k++)
	{
		if (Vertex[k] == ch) break;
	}
	if (k == Vertexnum + 1)
	{
		Vertex[k - 1] = ch;
		Vertexnum++;
	}
}
/*
1,2
2,3
3,4
4,5
5,1
1,3
1,4
*,*
*/

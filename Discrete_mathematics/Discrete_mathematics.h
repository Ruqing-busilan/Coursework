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

char Vertex[Maxsize];             //��������
int Vertexnum = 0;               //������Ŀ
int Edgenum = 0;          //����Ŀ
char path[Maxsize][Maxsize];      //���·������

struct Edge
{
	int begin;        //��ǰ�����±�
	int end;              //�ߺ󶥵��±�
};

struct Point
{
	int x;        //������
	int y;              //������
};

void Input(int matrix[][Maxsize]);                     //����
void M_Output(int matrix[][Maxsize]);                      //������ʽ���
void R_Output(int matrix[][Maxsize]);                 //��ϵ��ʽ���
void Reflexivity(int matrix[][Maxsize]);                  //�Է����ж�
void Symmetry(int matrix[][Maxsize]);                 //�Գ����ж�
void Transitivity(int matrix[][Maxsize]);                 //�������ж�
void Reflexive_closure(int matrix[][Maxsize]);        //�Է��հ�
void Symmetrical_closure(int matrix[][Maxsize]);         //�ԳƱհ�
void Transitive_closure(int matrix[][Maxsize]);            //���ݱհ�
void Adjacency_matrix(int matrix[][Maxsize]);         //�ڽӾ���
void Reachable_matrix(int matrix[][Maxsize]);                 //�ɴ����
void Correlation_matrix(int matrix[][Maxsize]);         //��������
void Distance_matrix(int matrix[][Maxsize]);                     //�������
void Road_num(int matrix[][Maxsize]);                    //�κ������ڵ㣨Ԫ�أ�֮���ض����ȵ�·������
void Warshall(int matrix[][Maxsize]);               //Warshall�㷨
int Ver_Search(char ch);                              //��������
void add_ver(char ch);                         // �ڶ���������Ӷ���
void graph(int matrix[][Maxsize]);


void Input(int matrix[][Maxsize])
{
	for (int i = 0; i < Maxsize; i++)
		for (int j = 0; j < Maxsize; j++)
			matrix[i][j] = 0;
	cout << "�������ϵ����a,b��ʽ,��*,*��������" << endl;
	char V1, V2, ch;
	while (cin >> V1 >> ch >> V2, V1 != '*'&&V2 != '*')
	{
		Edgenum++;
		int i, j;
		add_ver(V1);                   //���V1�Ƿ��ڶ�������
		add_ver(V2);
		i = Ver_Search(V1);            //����V1�ڶ�������λ��
		j = Ver_Search(V2);
		matrix[i][j] = 1;
		/*cout << "��������һ���ڵ��ϵ��" << endl;*/
	}
//	cout << "�ڵ��ϵ��Ŀ��" << Edgenum << endl;
//	cout << "������ĿΪ��" << Vertexnum << endl;
//	cout << "�Ƿ���Ҫת��Ϊ����ͼ����Y/N����" << endl;
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
//		cout << "��ͼΪ����ͼ��" << endl;
//	getchar();
//	graph(matrix);
}

void graph(int matrix[][Maxsize])
{
//
//    Point *p;
//	p = new Point[Vertexnum];
//	initgraph(640, 480);    // ��ʼ��ͼ��ģʽ
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
//	closegraph();          // �ر�ͼ��ģʽ
}
void Reflexivity(int matrix[][Maxsize])
{
	int flag = 0;
	for (int i = 0; i < Vertexnum; i++)
		if (matrix[i][i] == 1)
			flag++;                     //�Է������Ŀflag+1
	if (flag == Vertexnum)
		cout << "�����Է���ϵ" << endl;
	else
		cout << "�������Է���ϵ" << endl;
}

void Symmetry(int matrix[][Maxsize])
{
	int flag = 1;
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
		{
			if (matrix[i][j] == 1 && matrix[j][i] != 1)
			{
				flag--;                           //�����ڽڵ��ϵ������Գ��Թ�ϵflag-1
			}
		}
	if (flag == 1)
		cout << "���жԳƹ�ϵ" << endl;
	else
		cout << "�����жԳƹ�ϵ" << endl;
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
						if (matrix[i][k] != 1)            //���ڵ��ϵ�����㴫����flag-1
							flag--;
					}
			}
		}
	if (flag == 1)
		cout << "���д��ݹ�ϵ" << endl;
	else
		cout << "�����д��ݹ�ϵ" << endl;
}

void Reflexive_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                //����һ���¾��󣬲��ƻ�ԭ�о���
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			if (temp[i][j] == 1)              //��a,b�й�ϵ������a,a��b,b�Ĺ�ϵ
			{
				temp[i][i] = 1;
				temp[j][j] = 1;
			}
	cout << "�Է��հ���";
	R_Output(temp);
}

void Symmetrical_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //����һ���¾��󣬲��ƻ�ԭ�о���
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			if (temp[i][j] == 1)
				temp[j][i] = 1;                      //��a,b�й�ϵ������b,a�Ĺ�ϵ
	cout << "�ԳƱհ���";
	R_Output(temp);
}

void Transitive_closure(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //����һ���¾��󣬲��ƻ�ԭ�о���
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	Warshall(temp);
	cout << "���ݱհ���";
	R_Output(temp);
}

void Adjacency_matrix(int matrix[][Maxsize])
{
	cout << "�ڽӾ���" << endl;
	M_Output(matrix);
}

void Reachable_matrix(int matrix[][Maxsize])
{
	int temp[Maxsize][Maxsize];                       //����һ���¾��󣬲��ƻ�ԭ�о���
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];
	Warshall(temp);
	cout << "�ɴ����" << endl;
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
	cout << "�������������������ʾ�ߣ���" << endl;
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
				path[i][j] = Vertex[i];         //���ͼ�д���·��������ǰһ������
			}
		}
	for (int k = 0; k < Vertexnum; k++)
		for (int i = 0; i < Vertexnum; i++)
			for (int j = 0; j < Vertexnum; j++)
			{
				if (temp[i][k] + temp[k][j] < temp[i][j])
				{
					temp[i][j] = temp[i][k] + temp[k][j];
					path[i][j] = path[k][j];                 //������������·��
				}
			}
	cout << "�������" << endl;
	M_Output(temp);
}

void Road_num(int matrix[][Maxsize])
{
    int temp[Maxsize][Maxsize];                       //����һ���¾��󣬲��ƻ�ԭ�о���
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			temp[i][j] = matrix[i][j];  
	int trans[Maxsize][Maxsize];
	for (int i = 0; i < Vertexnum; i++)
		for (int j = 0; j < Vertexnum; j++)
			trans[i][j] = 0;                   		
	int n, index1, index2, t = 0;
	char V1, V2;
	cout << "������������(����֮���ÿո����������ʹ�������ַ�)��" << endl;
	cin >> V1 >> V2;
	index1 = Ver_Search(V1);
	index2 = Ver_Search(V2);
	cout << "���볤�ȣ�" << endl;
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
	cout << "����" << V1 << "�붥��" << V2 << "����Ϊ" << n << "������Ϊ:  " << trans[index1][index2] << endl;
}

void Warshall(int matrix[][Maxsize])
{
	for (int j = 0; j < Vertexnum; j++)
		for (int i = 0; i < Vertexnum; i++)
			if (matrix[i][j] == 1)
			{
				for (int k = 0; k < Vertexnum; k++)
				{
					matrix[i][k] = matrix[i][k] | matrix[j][k];     //������
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
				cout << "��";
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

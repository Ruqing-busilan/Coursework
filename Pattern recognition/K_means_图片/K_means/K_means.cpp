// K_means.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>

using namespace cv;
using namespace std;

const int k = 2;

struct Data
{
	double *d;
	int type;
	int test_type;
};

int **Labels;
int M;
int N;
int T;

void K_means(Data data[]);
int classify(Data means[], Data a_data);
double getDist(Data x, Data y);
double getVar(Data data[], Data means[]);
void getMeans(Data data[], Data means[]);

int main()
{
	Mat origin = imread("1600.jpg");
	Mat data=origin;
	Data *k_data;
	N = data.cols;
	M = data.rows;
	T = data.channels();
	k_data = new Data[M*N];
	for (int i = 0; i < M*N; i++)
		k_data[i].d= new double[T];
	Labels = new int*[k];
	for (int i = 0; i < k; i++)
		Labels[i] = new int[M*N];
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int bgr = 0; bgr < T; bgr++)
				k_data[i*N+j].d[bgr] = data.at<Vec3b>(i, j)[bgr];
		}
	}
	K_means(k_data);
	for (int i = 0; i < M*N; i++)
	{
		for (int j = 0; j < T; j++)
		{
			if (Labels[1][i] == 1)
			{
				k_data[i].d[j] = 255;
			}
			else
				k_data[i].d[j] = 0;
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int bgr = 0; bgr < T; bgr++)
				data.at<Vec3b>(i, j)[bgr] = k_data[i * N + j].d[bgr];
		}
	}
	imshow("1600", data);
	waitKey();
	for (int i = 0; i < k; i++)
		delete[] Labels[i];
	delete[] Labels;
	for (int i = 0; i < M*N; i++)
		delete[] k_data[i].d;
	delete[] k_data;
	return 0;
}

void K_means(Data data[])
{
	int c_mean[k] = {100*N+50,190*N+150};
	Data means[k];
	for (int i = 0; i < k; i++)
	{
		means[i] = data[c_mean[i]];
		cout << means[i].d[0] << " " << means[i].d[1] << " " << means[i].d[2] << " ";
		for (int j = 0; j < M*N; j++)
			Labels[i][j] = 0;
		cout << endl;
	}
	int c;
	for (int i = 0; i < M*N; i++)
	{
		c = classify(means, data[i]);
		Labels[c][i] = 1;
	}
	for (int i = 0; i < k; i++)
	{
		int sum = 0;
		cout << "第" << i + 1 << "个簇：" << endl;
		for (int j = 0; j < M*N; j++)
		{
			if (Labels[i][j] == 1)
			{
				//cout << j << " ";
				sum++;
			}
		}
		cout << endl;
		cout << "共" << sum << "个。" << endl;
	}
	double oldVar = -1;
	double newVar = getVar(data, means);
	while (fabs(newVar - oldVar) >= 1)
	{
		//cout << fabs(newVar - oldVar) << endl;
		getMeans(data, means);
		oldVar = newVar;
		newVar = getVar(data, means); //计算新的准则函数值
		for (int i = 0; i < k; i++)
			for (int j = 0; j < M*N; j++)
				Labels[i][j] = 0;
		//根据新的质心获得新的簇
		for (int i = 0; i < M*N; i++)
		{
			c = classify(means, data[i]);
			Labels[c][i] = 1;
		}
		//输出当前的簇
		for (int i = 0; i < k; i++)
		{
			int sum = 0;
			cout << "第" << i + 1 << "个簇：" << endl;
			for (int j = 0; j < M*N; j++)
			{
				if (Labels[i][j] == 1)
				{
					//cout << j << " ";
					sum++;
				}
			}
			cout << endl;
			cout << "共" << sum << "个。" << endl;
		}
	}
}

int classify(Data means[], Data a_data)
{
	double dist = getDist(means[0], a_data);
	double tmp;
	int label = 0;//标示属于哪一个簇
	for (int i = 1; i < k; i++)
	{
		tmp = getDist(means[i], a_data);
		if (tmp < dist)
		{
			dist = tmp;
			label = i;
		}
	}
	return label;
}

double getDist(Data x, Data y)
{
	double dist=0;
	for (int i = 0; i < T; i++)
		dist = sqrt(dist + (x.d[i] - y.d[i])*(x.d[i] - y.d[i]));
	return dist;
}


double getVar(Data data[], Data means[])
{
	double var = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < M*N; j++)
		{
			if (Labels[i][j] == 1)
			{
				var += getDist(data[j], means[i]);
			}
		}
	}
	return var;
}

void getMeans(Data data[], Data means[])
{
	double *tmp;
	tmp = new double[T];
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < T; j++)
			tmp[j] = 0;
		int sum = 0;
		for (int j = 0; j < M*N; j++)
		{
			if (Labels[i][j] == 1)
			{
				for (int t = 0; t < T; t++)
					tmp[t] += data[j].d[t];
				sum++;
			}
		}
		//cout << sum << endl;
		for (int t = 0; t < T; t++)
		{
			means[i].d[t] = tmp[t] / sum;
			//cout << means[i].d[t] << " ";
		}
		cout << endl;
	}
}
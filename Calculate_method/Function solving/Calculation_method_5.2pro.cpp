#include <bits/stdc++.h>

using namespace std;

double A[100][100];
double b[100];
double U[100][100];
double L[100][100];
double y[100];
double x[100];

int main()
{
	int n;
	cout<<"输入自变量的个数："<<endl; 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"输入第"<<i<<"个方程(的系数)及结果："<<endl;
		for(int j=1;j<=n;j++)
			cin>>A[i][j];
		cin>>b[i]; 
	}
	for(int j=1;j<=n;j++)
	{
		U[1][j]=A[1][j];
	}
	for(int i=1;i<=n;i++)
	{
		L[i][1]=A[i][1]/U[1][1];
		L[i][i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=1;k<=i-1;k++)
				U[i][j]-=L[i][k]*U[k][j];
			U[i][j]+=A[i][j];
		}
		if(i!=n)
		{
			for(int j=i+1;j<=n;j++)
			{	
				for(int k=1;k<=i-1;k++)
					L[j][i]-=L[j][k]*U[k][i];
				L[j][i]+=A[j][i];
				L[j][i]/=U[i][i];
			}
		}
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n;j++)
//			cout<<L[i][j]<<" ";
//		cout<<endl;
//	}
//	cout<<endl;
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n;j++)
//			cout<<U[i][j]<<" ";
//		cout<<endl;
//	}
	y[1]=b[1];
	for(int i=2;i<=n;i++)
	{
		for(int k=1;k<=i-1;k++)
			y[i]-=L[i][k]*y[k];
		y[i]+=b[i];
	}
	x[n]=y[n]/U[n][n];
	cout<<"求解结果如下："<<endl; 
	cout<<"x"<<n<<"="<<x[n]<<endl;
	for(int i=n-1;i>0;i--)
	{
		for(int k=i+1;k<=n;k++)
			y[i]-=U[i][k]*x[k];
		x[i]+=y[i];
		x[i]/=U[i][i];
		cout<<"x"<<i<<"="<<x[i]<<endl;	
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

double A[100][100];
double f[100];
double beita[100];
double L[100][100];
double y[100];
double x[100];

int main()
{
	int n;
	cout<<"�����Ա����ĸ�����"<<endl; 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"�����"<<i<<"������(��ϵ��)�������"<<endl;
		for(int j=1;j<=n;j++)
			cin>>A[i][j];
		cin>>f[i]; 
	}
	beita[1]=A[1][2]/A[1][1];
	for(int i=2;i<=n-1;i++)
	{
		beita[i]=A[i][i+1]/(A[i][i]-A[i][i-1]*beita[i-1]);
	}
	y[1]=f[1]/A[1][1];
	for(int i=2;i<=n;i++)
	{
		y[i]=(f[i]-A[i][i-1]*y[i-1])/(A[i][i]-A[i][i-1]*beita[i-1]);
	}
	x[n]=y[n];
	cout<<"��������£�"<<endl; 
	cout<<"x"<<n<<"="<<x[n]<<endl;
	for(int i=n-1;i>0;i--)
	{
		x[i]=y[i]-beita[i]*x[i+1];
		cout<<"x"<<i<<"="<<x[i]<<endl;	
	}
	return 0;
}

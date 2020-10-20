#include <bits/stdc++.h>

using namespace std;

double equ[100][100];
double result[100];
int order[100];

int main()
{
	int n,index=-1;
	double xn;
	cout<<"输入自变量的个数："<<endl; 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"输入第"<<i<<"个方程(的系数)及结果："<<endl;
		for(int j=1;j<=n+1;j++)
			cin>>equ[i][j];
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n+1;j++)
//			cout<<equ[i][j]<<" ";
//		cout<<endl;
//	}
	for(int j=1;j<n;j++)
	{
		double judge=0;
		for(int i=1;i<=n;i++)
		{
			if(equ[i][j]>judge)
			{
				judge=equ[i][j];
				for(int k=1;k<=j;k++)//标记此方程的顺序，已排好无需改动 
				{
					if(order[k]==i)
						break;
					else
						order[j]=i;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			bool flag=false;
			for(int k=1;k<=j;k++)
			{
				if(order[k]==i)
					flag=true;
			}
			if(flag==false)//拒绝修改已构成三角矩阵的方程 
			{
				double l=equ[i][j]/equ[order[j]][j];
//				cout<<l<<endl;
				for(int k=1;k<=n+1;k++)
				{
					equ[i][k]=equ[i][k]-equ[order[j]][k]*l;
				}	
			}
		}
//			for(int i=1;i<=n;i++)
//			{
//				for(int k=1;k<=n+1;k++)
//					cout<<equ[i][k]<<" ";
//				cout<<endl;
//			} 
//			cout<<endl<<endl;	
	}
//	for(int i=1;i<=n;i++)
//		cout<<order[i]<<endl;
	for(int i=1;i<=n;i++)//寻找最后一个方程ann*x=bnn 
	{
		bool flag=false;
		for(int j=1;j<=n;j++)
		{
			if(i==order[j])
				flag=true;
		} 
		if(flag==false)
		 	index=i;//唯一	
	}
	order[n]=index;///次序加入最后一个方程 
	cout<<"求解结果如下："<<endl; 
	result[n]=equ[order[n]][n+1]/equ[order[n]][n];
	cout<<"x"<<n<<"="<<result[n]<<endl;
	for(int i=n-1;i>0;i--)
	{
		for(int j=i+1;j<=n;j++)
			result[i]+=equ[order[i]][j]*result[j];
		result[i]=(equ[order[i]][n+1]-result[i])/equ[order[i]][i];
		if(fabs(result[i])<0.00001)
			result[i]=0;
		cout<<"x"<<i<<"="<<result[i]<<endl;	
	}
	return 0;
} 

#include <bits/stdc++.h>

using namespace std;

double equ[100][100];
double result[100];
int order[100];

int main()
{
	int n,index=-1;
	double xn;
	cout<<"�����Ա����ĸ�����"<<endl; 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"�����"<<i<<"������(��ϵ��)�������"<<endl;
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
				for(int k=1;k<=j;k++)//��Ǵ˷��̵�˳�����ź�����Ķ� 
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
			if(flag==false)//�ܾ��޸��ѹ������Ǿ���ķ��� 
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
	for(int i=1;i<=n;i++)//Ѱ�����һ������ann*x=bnn 
	{
		bool flag=false;
		for(int j=1;j<=n;j++)
		{
			if(i==order[j])
				flag=true;
		} 
		if(flag==false)
		 	index=i;//Ψһ	
	}
	order[n]=index;///����������һ������ 
	cout<<"��������£�"<<endl; 
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

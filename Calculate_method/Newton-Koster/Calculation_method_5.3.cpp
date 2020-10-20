#include<bits/stdc++.h>

using namespace std;

double func(double x);
double Newton_Cotes(int a,int b,int n);

int main()
{
	int n,a,b;
	cout<<"输入积分区间[a,b]："<<endl;
	cin>>a>>b;
	cout<<"输入阶数n：" <<endl;
	cin>>n;
	cout<<"计算值： "<<Newton_Cotes(a,b,n)<<endl;
	return 0;
} 

double Newton_Cotes(int a,int b,int n)
{
	double sum=0;
	double up,down,*coef;
	char ch;
	coef=new double[n];
	if(n==1)
	{
		cout<<"f("<<a<<")="<<func(a)<<endl;
		cout<<"f("<<b<<")="<<func(b)<<endl;
		return (b-a)/2.0*(func(a)+func(b));
	}
	else
	{
		sum=0;
		cout<<n<<"阶牛顿-柯斯特系数(x/y形式)："<<endl;
		for(int i=0;i<=n;i++)
		{
			cin>>up>>ch>>down; 
			coef[i]=up/down;
		}
		cout<<"f("<<a<<")="<<func(a)<<endl;
		sum+=coef[0]*func(a);
		for(int i=1;i<n;i++)
		{
			cout<<"f("<<i<<"/"<<n<<")="<<func(i*1.0/n)<<endl;
			sum+=coef[i]*func(i*1.0/n);
		}
		cout<<"f("<<b<<")="<<func(b)<<endl;
		sum+=coef[n]*func(b);
		return (b-a)*sum;
	}
}

double func(double x)
{
	if(x==0)
		return 1;
	else 
		return sin(x)/x;
}


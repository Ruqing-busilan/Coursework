#include<bits/stdc++.h>

using namespace std;

double func(double x);
double Guass(double a,double b,int n);

int main()
{
	int k,n;
	double a,b;
	cout<<"输入积分区间[a,b]："<<endl;
	cin>>a>>b;//b=3.1415926/2=1.5707963
	cout<<"输入点数n：" <<endl;
	cin>>n;
	cout<<"计算值： "<<Guass(a,b,n)<<endl;
	return 0;
} 

double func(double x)
{
	return x*x*cos(x);
}

double Guass(double a,double b,int n)
{
	double A,t; 
	double sum=0;
	for(int i=0;i<n;i++)
	{
		cout<<"输入第"<<i+1<<"个节点和系数："<<endl;
		cin>>t>>A;
		sum+=A*func((b-a)/2.0*t+(b+a)/2.0);
	}
	return sum*(b-a)/2.0;
}

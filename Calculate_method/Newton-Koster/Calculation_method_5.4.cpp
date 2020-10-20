#include<bits/stdc++.h>

using namespace std;

double func(double x);
double Combine_NewtonCotes(int a,int b,int k,int n);

int main()
{
	int k,a,b,n;
	cout<<"输入积分区间[a,b]："<<endl;
	cin>>a>>b;
	cout<<"输入等份k：" <<endl;
	cin>>k;
	cout<<"输入阶数n：" <<endl;
	cin>>n;
	cout<<"计算值： "<<Combine_NewtonCotes(a,b,k,n)<<endl;
	return 0;
} 

double Combine_NewtonCotes(int a,int b,int k,int n)
{
	double h,temp1=0,temp2=0;
	h=(b-a)*1.0/k;
	if(n==1)
	{
		cout<<"f("<<a<<")="<<func(a)<<endl;
		for(int i=1;i<k;i++)
		{
			cout<<"f("<<i<<"/"<<k<<")="<<func(i*1.0/k)<<endl;
			temp1+=func(i*1.0/k);
		}
		cout<<"f("<<b<<")="<<func(b)<<endl;
		return h/2.0*(func(a)+2.0*temp1+func(b));
	}
	if(n==2)
	{
		cout<<"f("<<a<<")="<<func(a)<<endl;
		for(int i=0;i<k;i++)
		{
			cout<<"f("<<2*i+1<<"/"<<k*2<<")="<<func((2*i+1)*1.0/(k*2.0))<<endl;
			temp1+=func((2*i+1)*1.0/(k*2.0));
		}
		for(int i=1;i<k;i++)
		{
			cout<<"f("<<i<<"/"<<k<<")="<<func(i*1.0/k)<<endl;
			temp2+=func(i*1.0/k);
		}
		cout<<"f("<<b<<")="<<func(b)<<endl;
		return h/6.0*(func(a)+4.0*temp1+2*temp2+func(b));
	}
}

double func(double x)
{
	if(x==0)
		return 1;
	else 
		return sin(x)/x;
}


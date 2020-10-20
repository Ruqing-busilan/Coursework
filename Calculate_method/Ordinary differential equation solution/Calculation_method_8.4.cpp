#include <bits/stdc++.h>

using namespace std;

double x[100];
double y[100];

double fun(double x,double y)
{
	return 2.0*x*y;
}

int main()
{
	double h,a,b,k1,k2,k3,k4;
	x[0]=0;
	y[0]=1;
	cout<<"输入x的范围和步长h:" <<endl;
	cin>>a>>b>>h;
	cout<<"x0"<<" = "<<x[0]<<":";
	cout<<" y"<<0<<" = "<<y[0]<<endl;
	for(int i=a;i<b/h;i++)
	{
		x[i+1]=x[0]+(i+1)*h;
		k1=fun(x[i],y[i]);
		k2=fun(x[i]+h/2.0,y[i]+h*k1/2.0);
		k3=fun(x[i]+h/2.0,y[i]+h*k2/2.0);
		k4=fun(x[i]+h,y[i]+h*k3);
		y[i+1]=y[i]+h*(k1+2.0*k2+2.0*k3+k4)/6.0;
		cout<<"x"<<i+1<<" = "<<x[i+1]<<":";
		cout<<" y"<<i+1<<" = "<<y[i+1]<<endl;
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

double x[100];
double y[100];

double fun(double x,double y)
{
	return -y-x*y*y;
}

int main()
{
	double h,a,b;
	x[0]=0;
	y[0]=1;
	cout<<"输入x的范围和步长h:" <<endl;
	cin>>a>>b>>h;
	cout<<"x0"<<" = "<<x[0]<<":";
	cout<<setprecision(4)<<" y"<<0<<" = "<<y[0]<<endl;
	for(int i=a;i<b/h;i++)
	{
		x[i+1]=x[0]+(i+1)*h;
		y[i+1]=y[i]+h*fun(x[i],y[i]);
		cout<<"x"<<i+1<<" = "<<x[i+1]<<":";
		cout<<setprecision(4)<<" y"<<i+1<<" = "<<y[i+1]<<endl;
	}
	return 0;
}

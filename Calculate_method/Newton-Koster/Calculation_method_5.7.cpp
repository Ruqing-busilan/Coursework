#include<bits/stdc++.h>

using namespace std;

double func(double x);
double Guass(double a,double b,int n);

int main()
{
	int k,n;
	double a,b;
	cout<<"�����������[a,b]��"<<endl;
	cin>>a>>b;//b=3.1415926/2=1.5707963
	cout<<"�������n��" <<endl;
	cin>>n;
	cout<<"����ֵ�� "<<Guass(a,b,n)<<endl;
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
		cout<<"�����"<<i+1<<"���ڵ��ϵ����"<<endl;
		cin>>t>>A;
		sum+=A*func((b-a)/2.0*t+(b+a)/2.0);
	}
	return sum*(b-a)/2.0;
}

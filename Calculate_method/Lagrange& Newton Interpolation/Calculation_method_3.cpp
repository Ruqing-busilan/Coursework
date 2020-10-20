#include "bits/stdc++.h"

using namespace std;

double x[100],y[100],dif[100][100];

double Lagrange(double xt)
{
    int n;
    double value=0,w1=1.0,w2=1.0;
    cout<<"���뺯���������"<<endl;
    cin>>n;
    cout<<"���뺯��ֵ��"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>x[i]>>y[i];
        w1=w1*(xt-x[i]);
    }
    for(int i=0;i<n;i++)
    {
        w2=1.0;
        for(int j=0;j<n;j++)
        {
            if(i!=j)
                w2=w2*(x[i]-x[j]);
        }
        value=value+y[i]*(w1/((xt-x[i])*w2));
    }
    return value;
}

double Newton(double xt)
{
    int n,d=1;
    double value=0;
    cout<<"���뺯���������"<<endl;
    cin>>n;
    cout<<"���뺯��ֵ��"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+2;j++)
        {
            dif[i][j]=0;
        }
    }
    for(int i=0;i<n;i++)
    {
        cin>>dif[i][0]>>dif[i][1];
    }
    for(int j=2;j<n+2;j++)
    {
        for(int i=j-1;i<n;i++)
        {
            dif[i][j]=(dif[i][j-1]-dif[i-1][j-1])/((dif[i][0]-dif[i-j+1][0])); 
        }
    }
    value=value+dif[0][1];
    double tmp=1;
    for(int i=1;i<n;i++)
    {
    	tmp*=(xt-dif[i-1][0]);
    	value=value+dif[i][i+1]*tmp;
    }
    return value; 
}

int main()
{
    double xt;
    cout<<"���������Xֵ��"<<endl;
    cin>>xt;
//    cout<<"�������շ���ֵ�����"<<Lagrange(xt)<<endl;
    cout<<"ţ�ٷ���ֵ�����"<<Newton(xt)<<endl;
}

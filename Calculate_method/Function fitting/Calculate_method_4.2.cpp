#include<bits/stdc++.h>

using namespace std;

const int N=100;

double ax[N];
double a[N];
double p[N][N];
double fp[N];
double ort[N];//正交  ort[n][m] ort[n]=ort[n][n]

int fact(int n);

int main()
{
	int n;
	double step=0.00001;
	cout<<"输入最佳平方逼近多项式的次数："<<endl; 
	cin>>n;
	n=n+1;
	for(int i=0;i<n;i++)
    {
        fp[i]=0;
        ort[i]=2.0/(2.0*i+1);
        ax[i]=0;
    }
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<=i/2;j++)
    	{
    		p[i][i-2*j]=(pow(-1,j)*fact(2*i-2*j))/(pow(2,i)*fact(j)*fact(i-j)*fact(i-2*j));//ppt有误 
    	}
    }
    for(int i=0;i<n;i++)
    {
    	for(double x=-1.0;x<=1.0;x+=step)
    	{
    		for(int j=0;j<n;j++)
//    			fp[i]+=p[i][j]*pow(x,j)*step*exp(x);
				fp[i]+=p[i][j]*pow(x,j)*step*pow(x,3);
		}
    	ax[i]=fp[i]/ort[i];
    }   
    for(int i=0;i<n;i++)
    {
		for(int j=0;j<n;j++)
			a[i]+=ax[j]*p[j][i];
//    	cout<<a[i]<<endl;
    } 
	cout<<"最佳平方逼近多项式如下："<<endl;  
    cout<<a[0]<<"+"<<a[1]<<"x";
	for(int i=2;i<n;i++)
    {
            cout<<"+"<<a[i]<<"x^"<<i;
    }
    cout<<endl;
    return 0;
//    for(int i=0;i<n;i++)
//    {
//  		cout<<ax[i]<<endl;
//    }
//    for(int i=0;i<n;i++)
//    {
//    	for(int j=0;j<n;j++)
//    	{
//    		cout<<p[i][j]<<" ";
//		}
//		cout<<endl;
//    }
} 

int fact(int n)  
{  
    int i,tmp[N];  
  	tmp[0]=1;  
    for(i=1;i<=n;i++) 
	tmp[i]=i*tmp[i-1];
    return tmp[i-1];
}

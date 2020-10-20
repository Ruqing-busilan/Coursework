#include<bits/stdc++.h>
#include<math.h>

using namespace std;

double A[100][100];
double X[100];
double b[100];
double temp[100];

int main()
{
    int n,time=1,select;
    double err=1;
    cout<<"输入方程个数n："<<endl;
    cin>>n;
    for(int i=1;i<=n;i++)
	{
		cout<<"输入第"<<i<<"个方程(的系数)及结果："<<endl;
		for(int j=1;j<=n;j++)
			cin>>A[i][j];
		cin>>b[i];
	}
    cout<<"输入初始解："<<endl;
    for(int i=1;i<=n;i++)
	{
        cin>>X[i];
	}
	cout<<"迭代方法："<<endl;
	cout<<"1、Jacobi"<<endl;
	cout<<"2、Gauss-Seidel"<<endl;
	cout<<"输入选择方法："<<endl;
	cin>>select;
	while(err>0.00001)
    {
        err=0;
        for(int i=1;i<=n;i++)
        {
            temp[i]=0;
        }
        switch(select)
        {
            case 1:
                {
                    for(int i=1;i<=n;i++)
                    {
                        for(int j=1;j<=n;j++)
                        {
                            if(j!=i)
                            {
                                temp[i]-=A[i][j]*X[j];
                            }
                        }
                        temp[i]+=b[i];
                        temp[i]/=A[i][i];
                    }
                    for(int i=1;i<=n;i++)
                    {
                        err+=sqrt(pow(X[i]-temp[i],2));
                    }
                    for(int i=1;i<=n;i++)
                    {
                        X[i]=temp[i];
                    }
                    break;
                }
            case 2:
                {
                    for(int i=1;i<=n;i++)
                    {
                        for(int j=1;j<=i-1;j++)
                        {
                            temp[i]-=A[i][j]*temp[j];
                        }
                        for(int j=i+1;j<=n;j++)
                        {
                            temp[i]-=A[i][j]*X[j];
                        }
                        temp[i]+=b[i];
                        temp[i]/=A[i][i];
                    }
                    for(int i=1;i<=n;i++)
                    {
                        err+=sqrt(pow(X[i]-temp[i],2));
                    }
                    for(int i=1;i<=n;i++)
                    {
                        X[i]=temp[i];
                    }
                    break;
                }
                default:cout<<"选择错误！"<<endl;
                        exit(0);
        }
        cout<<"迭代次数"<<time<<"："<<endl;
        cout<<"X"<<time<<" = ";
        for(int i=1;i<=n;i++)
        {
            cout<<" "<<X[i];
        }
        cout<<endl;
        time++;
    }
    return 0;
}

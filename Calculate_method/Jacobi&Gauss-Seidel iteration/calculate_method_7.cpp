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
    cout<<"���뷽�̸���n��"<<endl;
    cin>>n;
    for(int i=1;i<=n;i++)
	{
		cout<<"�����"<<i<<"������(��ϵ��)�������"<<endl;
		for(int j=1;j<=n;j++)
			cin>>A[i][j];
		cin>>b[i];
	}
    cout<<"�����ʼ�⣺"<<endl;
    for(int i=1;i<=n;i++)
	{
        cin>>X[i];
	}
	cout<<"����������"<<endl;
	cout<<"1��Jacobi"<<endl;
	cout<<"2��Gauss-Seidel"<<endl;
	cout<<"����ѡ�񷽷���"<<endl;
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
                default:cout<<"ѡ�����"<<endl;
                        exit(0);
        }
        cout<<"��������"<<time<<"��"<<endl;
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

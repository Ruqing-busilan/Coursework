#include<bits/stdc++.h>

using namespace std;

const int N=100;

double a[N];
double x[N];
double y[N];
double result[N];
double fa[N][N];
double fa_des[N][N];

bool GetMatrixInverse(double src[N][N],int n,double des[N][N]);
double getA(double arcs[N][N],int n);
void  getAStart(double arcs[N][N],int n,double ans[N][N]);

int main()
{
    int n,m;
    double value;
    cout<<"输入数据组数及拟合多项式系数："<<endl;
    cin>>n>>m;
    cout<<"输入数据："<<endl;
    for(int i=0;i<n;i++)
       cin>>x[i]>>y[i];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=m;j++)
        {
            fa[i][j]=0;
        }
    }
    for(int i=0;i<n;i++)
    {
        result[i]=0;
        a[i]=0;
    }
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=m;j++)
        {
            for(int k=0;k<n;k++)
                fa[i][j]=fa[i][j]+pow(x[k],i+j);
        }
    }
    for(int i=0;i<=m;i++)
    {
        for(int k=0;k<n;k++)
            result[i]=result[i]+pow(x[k],i)*y[k];
    }
    if(GetMatrixInverse(fa,m+1,fa_des))
    {
        for(int i=0;i<=m;i++)
        {
            for(int j=0;j<=m;j++)
            {
                a[i]=a[i]+fa_des[i][j]*result[j];
            }
        }
    }
//    for(int i=0;i<=m;i++)
//    {
//        for(int j=0;j<=m;j++)
//        {
//                cout<<fa[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    cout<<"结果如下："<<endl; 
    for(int i=0;i<=m;i++)
    {
            cout<<"a"<<i<<" = "<<a[i]<<endl;
    }
    return 0;
}

//得到给定矩阵src的逆矩阵保存到des中。
bool GetMatrixInverse(double src[N][N],int n,double des[N][N])
{
    double flag=getA(src,n);
    double t[N][N];
    if(flag==0)
    {
        return false;
    }
    else
    {
        getAStart(src,n,t);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                des[i][j]=t[i][j]/flag;
            }

        }
    }
    return true;
}

//按第一行展开计算|A|
double getA(double arcs[N][N],int n)
{
    if(n==1)
    {
        return arcs[0][0];
    }
    double ans = 0;
    double temp[N][N]={0.0};
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            for(k=0;k<n-1;k++)
            {
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];

            }
        }
        double t = getA(temp,n-1);
        if(i%2==0)
        {
            ans += arcs[0][i]*t;
        }
        else
        {
            ans -=  arcs[0][i]*t;
        }
    }
    return ans;
}

//计算每一行每一列的每个元素所对应的余子式，组成A*
void  getAStart(double arcs[N][N],int n,double ans[N][N])
{
    if(n==1)
    {
        ans[0][0] = 1;
        return;
    }
    int i,j,k,t;
    double temp[N][N];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n-1;k++)
            {
                for(t=0;t<n-1;t++)
                {
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];
                }
            }


            ans[j][i]  =  getA(temp,n-1);
            if((i+j)%2 == 1)
            {
                ans[j][i] = - ans[j][i];
            }
        }
    }
}

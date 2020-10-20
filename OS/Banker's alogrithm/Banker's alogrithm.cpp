#include <bits/stdc++.h>

using namespace std;

#define W 10
#define R 20
int M ;                     //总进程数
int N ;                    //资源种类
int ALL_RESOURCE[W];       //各种资源的数目总和
int MAX[W][R];            //M个进程对N类资源最大资源需求量
int AVAILABLE[R];         //系统可用资源数
int ALLOCATION[W][R];     //M个进程已经得到N类资源的资源量
int NEED[W][R];           //M个进程还需要N类资源的资源量
int Request[R];           //请求资源个数

void Matixoutput(int tmp[][R]);
bool Lequal(int a[],int b[],int n);
bool CHECK();
int Security[W];

int main()
{
    int tmp[R];
    cout<<"输入进程数和资源类数："<<endl;
    cin>>M>>N;
    cout<<"输入各类资源数量："<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"第"<<i+1<<"类资源数量："<<endl;
        cin>>ALL_RESOURCE[i];
        AVAILABLE[i]=ALL_RESOURCE[i];
    }
    cout<<"输入最大需求矩阵："<<endl;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>MAX[i][j];
        }
    }
    cout<<"输入分配矩阵："<<endl;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>ALLOCATION[i][j];
            NEED[i][j]=MAX[i][j]-ALLOCATION[i][j];
            AVAILABLE[j]=AVAILABLE[j]-ALLOCATION[i][j];
        }
    }
    while(1)
    {
        int pnum;
        cout<<"输入进程及请求"<<N<<"类资源数量："<<endl;
        cin>>pnum;
        for(int i=0;i<N;i++)
        {
            cin>>Request[i];
            tmp[i]=NEED[pnum][i];
        }
        
        if(Lequal(Request,tmp,N))
        {
            if(Lequal(Request,AVAILABLE,N))
            {
                for(int i=0;i<N;i++)
                {
                    AVAILABLE[i]=AVAILABLE[i]-Request[i];
                    ALLOCATION[pnum][i]=ALLOCATION[pnum][i]+Request[i];
                    NEED[pnum][i]=NEED[pnum][i]-Request[i];
                }
                if(!CHECK())
                {
                    cout<<"不能分配！系统处于不安全状态！"<<endl;
                    for(int i=0;i<N;i++)
                    {
                        AVAILABLE[i]=AVAILABLE[i]+Request[i];
                        ALLOCATION[pnum][i]=ALLOCATION[pnum][i]-Request[i];
                        NEED[pnum][i]=NEED[pnum][i]+Request[i];
                    }
                }
                else
                {
                    cout<<"请求分配成功！安全序列如下："<<endl;
                    for(int i=0;i<M;i++)
                    	cout<<Security[i]<<" ";
                    cout<<endl; 
                    cout<<"需求矩阵如下："<<endl;
                    Matixoutput(NEED);
                    cout<<endl;
                }
            }
            else
                cout<<"请求分配失败！请求资源超过可利用资源数！"<<endl;
        }
        else
            cout<<"请求分配失败！请求资源超过需求资源数！"<<endl;
    }
    return 0;
}

void Matixoutput(int tmp[][R])
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<tmp[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool CHECK()
{
    int WORK[R],FINSH[W],flag,index=0,lastflag=0;
    for(int i=0;i<M;i++)
        FINSH[i]=false;
    for(int j=0;j<N;j++)
        WORK[j]=AVAILABLE[j];
    while(1)
    {
         for(int i=0;i<M;i++)
        {
            flag=0;
            for(int j=0;j<N;j++)
            {
                if(NEED[i][j]<=WORK[j])
                    flag++;
            }
            if(FINSH[i]==false&&flag==N)
            {
                for(int j=0;j<N;j++)
                {
                    WORK[j]=ALLOCATION[i][j]+WORK[j];
                }
                FINSH[i]=true;
                Security[index]=i;
                index++;
            }
        }
//        for(int j=0;j<N;j++)
//        {
//               cout<<WORK[j]<<" ";
//        }
//        cout<<endl;
        flag=1;
        for(int i=0;i<M;i++)
        {
            if(FINSH[i]==true)
                flag++;
        }
        if(flag==M+1)
            return true;
        if(flag==lastflag)
            return false;
        lastflag=flag;
    }
}

bool Lequal(int a[],int b[],int n)
{
    for(int i=0;i<n;i++)
    {
        if(a[i]>b[i])
            return false;
    }
    return true;
}

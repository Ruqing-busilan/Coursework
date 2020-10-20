#include <bits/stdc++.h>

using namespace std;

#define W 10
#define R 20
int M ;                     //�ܽ�����
int N ;                    //��Դ����
int ALL_RESOURCE[W];       //������Դ����Ŀ�ܺ�
int MAX[W][R];            //M�����̶�N����Դ�����Դ������
int AVAILABLE[R];         //ϵͳ������Դ��
int ALLOCATION[W][R];     //M�������Ѿ��õ�N����Դ����Դ��
int NEED[W][R];           //M�����̻���ҪN����Դ����Դ��
int Request[R];           //������Դ����

void Matixoutput(int tmp[][R]);
bool Lequal(int a[],int b[],int n);
bool CHECK();
int Security[W];

int main()
{
    int tmp[R];
    cout<<"�������������Դ������"<<endl;
    cin>>M>>N;
    cout<<"���������Դ������"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"��"<<i+1<<"����Դ������"<<endl;
        cin>>ALL_RESOURCE[i];
        AVAILABLE[i]=ALL_RESOURCE[i];
    }
    cout<<"��������������"<<endl;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>MAX[i][j];
        }
    }
    cout<<"����������"<<endl;
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
        cout<<"������̼�����"<<N<<"����Դ������"<<endl;
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
                    cout<<"���ܷ��䣡ϵͳ���ڲ���ȫ״̬��"<<endl;
                    for(int i=0;i<N;i++)
                    {
                        AVAILABLE[i]=AVAILABLE[i]+Request[i];
                        ALLOCATION[pnum][i]=ALLOCATION[pnum][i]-Request[i];
                        NEED[pnum][i]=NEED[pnum][i]+Request[i];
                    }
                }
                else
                {
                    cout<<"�������ɹ�����ȫ�������£�"<<endl;
                    for(int i=0;i<M;i++)
                    	cout<<Security[i]<<" ";
                    cout<<endl; 
                    cout<<"����������£�"<<endl;
                    Matixoutput(NEED);
                    cout<<endl;
                }
            }
            else
                cout<<"�������ʧ�ܣ�������Դ������������Դ����"<<endl;
        }
        else
            cout<<"�������ʧ�ܣ�������Դ����������Դ����"<<endl;
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

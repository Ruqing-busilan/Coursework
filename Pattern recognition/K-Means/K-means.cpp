#include<bits/stdc++.h>

using namespace std;

const int k=4;
const int M=400;
const int N=2;

struct Data
{
	double d[N];
	int type;
	int test_type;	
};

int Labels[k][M];

void K_means(Data data[]);
int classify(Data means[],Data a_data);
double getDist(Data x,Data y);
double getVar(Data data[],Data means[]);
void getMeans(Data data[],Data means[]);

int main()
{
	freopen("4k2_far.txt","r",stdin);
	Data data[M];
	for(int i=0;i<M;i++)
	{
		cin>>data[i].type;
		for(int j=0;j<N;j++)
			cin>>data[i].d[j];
	}
//	for(int i=0;i<M;i++)
//	{
//		for(int j=0;j<N;j++)
//			cout<<data[i].d[j]<<" ";
//		cout<<endl;
//	}
	K_means(data);	
	return 0;
} 

void K_means(Data data[])
{
	int c_mean[k]={1,200,330,380}; 
	Data means[k];
	for(int i=0;i<k;i++)
	{
		means[i]=data[c_mean[i]];
		for(int j=0;j<M;j++)
			Labels[i][j]=0;
	}
	int c;
	for(int i=0;i<M;i++)
	{
		c=classify(means,data[i]);
		Labels[c][i]=1;
	}
	for(int i=0;i<k;i++)
	{
		int sum=0;
		cout<<"第"<<i+1<<"个簇："<<endl;
		for (int j=0;j<M;j++)
		{
			if(Labels[i][j]==1)
			{
				cout<<j<<" ";
				sum++;
			} 
		}	
		cout<<endl;
		cout<<"共"<<sum<<"个。"<<endl;
	}
	double oldVar=-1;
	double newVar=getVar(data,means);
	while(fabs(newVar - oldVar)>=1)
	{
		getMeans(data,means);
		oldVar = newVar;
		newVar=getVar(data,means); //计算新的准则函数值
		for(int i=0;i<k;i++)
			for(int j=0;j<M;j++)
				Labels[i][j]=0;
		//根据新的质心获得新的簇
		for(int i=0;i<M;i++)
		{
			c=classify(means,data[i]);
			Labels[c][i]=1;
		}
		//输出当前的簇
		for(int i=0;i<k;i++)
		{
			int sum=0;
			cout<<"第"<<i+1<<"个簇："<<endl;
			for (int j=0;j<M;j++)
			{
				if(Labels[i][j]==1)
				{
					cout<<j<<" ";
					sum++;
				} 
			}	
			cout<<endl;
			cout<<"共"<<sum<<"个。"<<endl;
		}
	}
}

int classify(Data means[],Data a_data)
{
	double dist=getDist(means[0],a_data);
	double tmp;
	int label=0;//标示属于哪一个簇
	for(int i=1;i<k;i++)
	{
		tmp=getDist(means[i],a_data);
		if(tmp<dist) 
		{
			dist=tmp;
			label=i;	
		}
	}
	return label;	
}

double getDist(Data x,Data y) 
{
	double dist;
	for(int i=0;i<N;i++)
		dist=sqrt(dist+(x.d[i]-y.d[i])*(x.d[i]-y.d[i]));
	return dist;
}


double getVar(Data data[],Data means[])
{
	double var=0;
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<M;j++)
		{
			if(Labels[i][j]==1)
			{
				var+=getDist(data[j],means[i]);
			} 
		}
	}
	return var;
}

void getMeans(Data data[],Data means[])
{
	double tmp[N];
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<N;j++)
			tmp[j]=0;
		int sum=0;
		for (int j=0;j<M;j++)
		{
			if(Labels[i][j]==1)
			{
				for (int t=0;t<N;t++)
					tmp[t]+=data[j].d[t];
				sum++;
			}	
		}
		cout<<sum<<endl;
		for (int t=0;t<N;t++)
		{
			means[i].d[t]=tmp[t]/sum;
			cout<<means[i].d[t]<<" ";
		}	
		cout<<endl;	
	}
}

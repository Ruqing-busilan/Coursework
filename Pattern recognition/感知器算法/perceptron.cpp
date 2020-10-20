#include<bits/stdc++.h>

using namespace std;

const int Train=148;
const int Test=30;
const int N=13;
const int C=3;

struct Data
{
	double d[N+1];//+1增广 
	int type;
};
double w[C][N+1]; 
double dx[C][Train];

void maxminnorm(Data tmp[],int t);

int main()
{
	//训练 
	double p=0.01;	
	freopen("wine_modify.txt","r",stdin);
	Data wine[Train+Test];
	char ch;
//	srand(time(0));
	for(int i=0;i<Train+Test;i++)
	{
		cin>>wine[i].type>>ch;
		for(int j=0;j<N-1;j++)
		{
			cin>>wine[i].d[j]>>ch;
		}
		cin>>wine[i].d[N-1];
		wine[i].d[N]=rand()%100/(double)101;
	}
	maxminnorm(wine,Train+Test);//归一化 
	for(int i=0;i<C;i++)
	{
		for(int j=0;j<N+1;j++)
		{
			w[i][j]=rand()%100/(double)101;
		}
	}
	int flag=Train;
	int k=3000;
	Data new_wt[Train];
	for(int i=0;i<C;i++)
	{
		k=3000;
		for(int j=0;j<Train;j++)
		{
			for(int l=0;l<N+1;l++)
			{
				if(wine[j].type==i+1)
					new_wt[j].d[l]=wine[j].d[l];
				else
					new_wt[j].d[l]=(-1)*wine[j].d[l];
			}
		}
		while(k--)
		{
			flag=Train;
			for(int j=0;j<Train;j++)
			{
				dx[i][j]=0;
				for(int l=0;l<N+1;l++)
					dx[i][j]+=new_wt[j].d[l]*w[i][l];
				if(dx[i][j]>0)
					flag--;
				else
				{
					for(int l=0;l<N+1;l++)
						w[i][l]+=p*new_wt[j].d[l];
				}
			}
//			cout<<flag<<endl;
			if(flag==0)
			{
				cout<<"感知器 "<<i+1<<" 迭代次数K="<<3000-k+1<<"  Bingo!"<<endl;
				break;
			}
		}	
	}
	for(int i=0;i<C;i++)
	{
		cout<<"w"<<i+1<<":"<<endl;
		for(int j=0;j<N+1;j++)
		{
			cout<<w[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	//测试 
	int test_type[Test];
	for(int i=0;i<Test;i++)
		test_type[i]=0;
	for(int i=0;i<C;i++)
	{
		for(int j=Train;j<Train+Test;j++)
		{
			dx[i][j]=0;
			for(int l=0;l<N+1;l++)
				dx[i][j]+=wine[j].d[l]*w[i][l];
//			cout<<i<<" "<<dx[i][j]<<endl;
			if(dx[i][j]>0)
			{
				if(test_type[j-Train]==0)
					test_type[j-Train]=i+1;
				else
					test_type[j-Train]=-1;
			}	
//			cout<<i<<" "<<test_type[j-Train]<<endl;
		}
	}
	int correct=0;
	for(int i=0;i<Test;i++)	
		if(wine[i+Train].type==test_type[i])
			correct++;
	cout<<"正确率："<<(double)correct/Test<<endl;
	freopen("CON","r",stdin);;
    getchar(); 
	return 0;
} 

void maxminnorm(Data tmp[],int t)
{
	double max[N],min[N];
	for(int i=0;i<N;i++)
	{
		max[i]=0;
		min[i]=tmp[0].d[i];
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<t;j++)
		{
			if(max[i]<tmp[j].d[i])
        		max[i]=tmp[j].d[i];
    		if(min[i]>tmp[j].d[i])
        		min[i]=tmp[j].d[i];
		}
//		cout<<max[i]<<" "<<min[i]<<endl;
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<t;j++)
		{
			tmp[j].d[i]=(tmp[j].d[i]-min[i]+1)/(max[i]-min[i]+1);
		}
	}
}

//	for(int i=0;i<Train+Test;i++)
//	{
//		for(int j=0;j<N+1;j++)
//		{
//			cout<<wine[i].d[j]<<" ";
//		}
//		cout<<endl;
//	} 


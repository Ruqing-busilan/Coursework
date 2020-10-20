#include<bits/stdc++.h>

using namespace std;

const int M=150;
const int N=4;

struct Data
{
	double d[N];
	int type;
	int test_type;	
};

int main()
{
	freopen("Iris.txt","r",stdin);
	Data data[M];
	char ch;
	string s;
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			cin>>data[i].d[j]>>ch;
		}
		cin>>s;
		if(s=="Iris-setosa")
			data[i].type=1;
		if(s=="Iris-versicolor")
			data[i].type=2;
		if(s=="Iris-virginica")
			data[i].type=3;
	}
	int center[M],minindex[M];
	int k=0,index=0;
	center[k]=0;
	double distance[M][M],min[M];
	double D12=0,newdistance,theta=0.35;
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			distance[k][i]=sqrt(distance[k][i]+(data[center[k]].d[j]-data[i].d[j])*(data[center[k]].d[j]-data[i].d[j]));
			if(distance[k][i]>D12)
			{
				D12=distance[k][i];
				index=i;
			}
		}
	}
//	for(int i=0;i<M;i++)
//	{
//		cout<<distance[k][i]<<" ";
//	}
//	cout<<endl<<index<<endl;
//	cout<<D12<<endl;
	k=1;
	center[k]=index;
	index=0;
	newdistance=D12;
	while(newdistance>theta*D12)
	{
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				distance[k][i]=sqrt(distance[k][i]+(data[center[k]].d[j]-data[i].d[j])*(data[center[k]].d[j]-data[i].d[j]));
			}
		}
		for(int i=0;i<M;i++)
		{
			double tmp=D12;
			for(int j=0;j<=k;j++)
				if (distance[j][i]<tmp)
				{
					tmp=distance[j][i];
					index=j;
				}
			min[i]=tmp;
			data[i].test_type=data[center[index]].type;
//			cout<<min[i]<<" "<<minindex[i]<<endl;	
		}
	 	double max=0,index=0;
       	for(int i=0;i<M;i++)
         	if(min[i]>max)
			{
				max=min[i];
				index=i;
			}
	   	if (max>theta*D12)
		{
			k++;
			center[k]=index;
		}
		newdistance=max;
//		cout<<theta*D12<<" "<<max<<endl;
	}
   	cout<<"k="<<k+1<<" ";
   	cout<<"center(s):";
   	for(int i=0;i<k;i++) 
	   cout<<center[i]+1<<"¡¢";cout<<center[k]+1;
   	cout<<endl;
   	double accurcy=0;
   	for(int i=0;i<M;i++)
   	{
//  		cout<<setw(3)<<i<<" "<<data[i].type<<" "<<data[i].test_type<<endl;
		if(data[i].type==data[i].test_type)
			accurcy++;
	}
	cout<<"ÕýÈ·ÂÊ£º"<<accurcy/M<<endl;
	freopen("CON","r",stdin);;
    getchar(); 
	return 0;
}


#include<bits/stdc++.h>

using namespace std;

int track[200];
int n;

void input();
void fcfs();
void ssft();
void scan();
void cscan();

int main()
{
	int select;
	while(1)
	{
		cout<<"---------------------*MENU*---------------------------"<<endl;
		cout<<"*               1.先来先服务算法(FCFS)               *"<<endl;
		cout<<"*               2.最短寻道时间优先(SSFT)             *"<<endl;
		cout<<"*               3.扫描算法(SCAN)                     *"<<endl;
		cout<<"*               4.循环扫描算法(CSCAN)                *"<<endl;
		cout<<"------------------------------------------------------"<<endl;
		cout<<"算法序号："<<endl;
		cin>>select;
		switch(select)
		{
			case 1:	fcfs();
					break;
			case 2:	ssft();
					break;
			case 3:	scan();
					break;
			case 4:	cscan();
					break;
			default:cout<<"输入错误！重新输入："<<endl; 
		}
	}
	return 0;
}
 
void input()
{
	cout<<"输入访问磁道个数："<<endl; 
	cin>>n;
	cout<<"输入访问磁道："<<endl; 
	for(int i=0;i<n;i++)
	{
		cin>>track[i];
	}
}

void fcfs()
{
	input();
	int begin,run;
	double dis=0,avgdis=0;
	cout<<"磁头初始磁道："<<endl;
	cin>>begin;
	run=begin;
	cout<<"被访问的下一磁道号及移动距离:"<<endl;
	for(int i=0;i<n;i++)
	{
		dis+=abs(run-track[i]);
		cout<<track[i]<<" "<<abs(run-track[i])<<endl;
		run=track[i];
	} 
	avgdis=dis/n;
	cout<<"平均寻道长度为："<<endl;
	cout<<avgdis<<endl;
}

void ssft()
{
	input();
	int begin,run,temp,index;
	double dis=0,avgdis=0;
	bool *state;
	state=new bool[n];
	for(int i=0;i<n;i++)
		state[i]=true;
	cout<<"磁头初始磁道："<<endl;
	cin>>begin;
	run=begin;
	cout<<"被访问的下一磁道号及移动距离:"<<endl;
	while(1)
	{
		temp=999;
		index=-1;
		for(int j=0;j<n;j++)
		{
			if(state[j]==true)
			{ 
				if(abs(run-track[j])<temp)
				{
					temp=abs(run-track[j]);
					index=j;
				}
			}
		} 
		if(index!=-1)
		{
			dis+=abs(run-track[index]);
			cout<<track[index]<<" "<<abs(run-track[index])<<endl;
			run=track[index];
			state[index]=false;
		}
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(state[i]!=false)
				flag++;
		}
		if(flag==0)
			break;
	}
	avgdis=dis/n;
	cout<<"平均寻道长度为："<<endl;
	cout<<avgdis<<endl;
	delete[] state;
}

void scan()
{
	input();
	int begin,run,temp,index=-1,origin_index=-1,back=0;
	double dis=0,avgdis=0;
	bool *state;
	state=new bool[n];
	for(int i=0;i<n;i++)
		state[i]=true;
	cout<<"磁头初始磁道："<<endl;
	cin>>begin;
	run=begin;
	sort(track,track+n);
	for(int i=0;i<n;i++)
	{
		if(track[i]>run)
		{
			index=i;
			break;
		}
	}
	origin_index=index;
	cout<<"被访问的下一磁道号及移动距离:"<<endl;
	while(1)
	{
		dis+=abs(run-track[index]);
		cout<<track[index]<<" "<<abs(run-track[index])<<endl;
		run=track[index];
		state[index]=false;
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(state[i]!=false)
				flag++;
		}
		if(flag==0)
			break;
		if((index+1)%n==0)
		{
			back=1;
			index=origin_index;
		}
		if(back==1)
			index--;
		else
			index++;
	}
	avgdis=dis/n;
	cout<<"平均寻道长度为："<<endl;
	cout<<avgdis<<endl;
	delete[] state;
}

void cscan()
{
	input();
	int begin,run,temp,index=-1;
	double dis=0,avgdis=0;
	bool *state;
	state=new bool[n];
	for(int i=0;i<n;i++)
		state[i]=true;
	cout<<"磁头初始磁道："<<endl;
	cin>>begin;
	run=begin;
	sort(track,track+n);
	for(int i=0;i<n;i++)
	{
		if(track[i]>run)
		{
			index=i;
			break;
		}
	}
	cout<<"被访问的下一磁道号及移动距离:"<<endl;
	while(1)
	{
		dis+=abs(run-track[index]);
		cout<<track[index]<<" "<<abs(run-track[index])<<endl;
		run=track[index];
		state[index]=false;
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(state[i]!=false)
				flag++;
		}
		if(flag==0)
			break;
		index++;
		index%=n;
	}
	avgdis=dis/n;
	cout<<"平均寻道长度为："<<endl;
	cout<<avgdis<<endl;
	delete[] state;
}


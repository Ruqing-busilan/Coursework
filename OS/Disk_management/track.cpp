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
		cout<<"*               1.�����ȷ����㷨(FCFS)               *"<<endl;
		cout<<"*               2.���Ѱ��ʱ������(SSFT)             *"<<endl;
		cout<<"*               3.ɨ���㷨(SCAN)                     *"<<endl;
		cout<<"*               4.ѭ��ɨ���㷨(CSCAN)                *"<<endl;
		cout<<"------------------------------------------------------"<<endl;
		cout<<"�㷨��ţ�"<<endl;
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
			default:cout<<"��������������룺"<<endl; 
		}
	}
	return 0;
}
 
void input()
{
	cout<<"������ʴŵ�������"<<endl; 
	cin>>n;
	cout<<"������ʴŵ���"<<endl; 
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
	cout<<"��ͷ��ʼ�ŵ���"<<endl;
	cin>>begin;
	run=begin;
	cout<<"�����ʵ���һ�ŵ��ż��ƶ�����:"<<endl;
	for(int i=0;i<n;i++)
	{
		dis+=abs(run-track[i]);
		cout<<track[i]<<" "<<abs(run-track[i])<<endl;
		run=track[i];
	} 
	avgdis=dis/n;
	cout<<"ƽ��Ѱ������Ϊ��"<<endl;
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
	cout<<"��ͷ��ʼ�ŵ���"<<endl;
	cin>>begin;
	run=begin;
	cout<<"�����ʵ���һ�ŵ��ż��ƶ�����:"<<endl;
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
	cout<<"ƽ��Ѱ������Ϊ��"<<endl;
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
	cout<<"��ͷ��ʼ�ŵ���"<<endl;
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
	cout<<"�����ʵ���һ�ŵ��ż��ƶ�����:"<<endl;
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
	cout<<"ƽ��Ѱ������Ϊ��"<<endl;
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
	cout<<"��ͷ��ʼ�ŵ���"<<endl;
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
	cout<<"�����ʵ���һ�ŵ��ż��ƶ�����:"<<endl;
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
	cout<<"ƽ��Ѱ������Ϊ��"<<endl;
	cout<<avgdis<<endl;
	delete[] state;
}


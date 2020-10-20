#include "bits/stdc++.h"

using namespace std;

enum Status {Ready,Run,Block,Finsh};

struct PCB
{
	int ID;
	int Priority;
	int Arrival_time;
	int Alltime;
	int CPUtime;
	int Starttime;
	int Blocktime;
	Status State;	
};
struct PCBnode
{
	PCB module;
	PCBnode *Next;
};

void InReady(PCBnode* head,PCBnode *x);
void Inqueue(PCBnode* head,PCBnode *x);
void Printqueue(PCBnode* head);

int main()
{
	int n,flag=0;
	PCB *pcb_a;
	PCBnode *Rhead=NULL,*Bhead=NULL,*Fhead=NULL,*tmp,*current;
	Rhead=new PCBnode;
	Rhead->Next=NULL;
	Fhead=new PCBnode;
	Fhead->Next=NULL;
	Bhead=new PCBnode;
	Bhead->Next=NULL;
	int time=0;
	cout<<"输入进程数："<<endl;
	cin>>n;
	pcb_a=new PCB[n];
	for(int i=0;i<n;i++)
	{
		cout<<"输入"<<i+1<<"号进程的到达时间、优先数、运行时间、开始阻塞时间和阻塞时间："<<endl;
		pcb_a[i].ID=i+1; 
		pcb_a[i].CPUtime=0;
		cin>>pcb_a[i].Arrival_time>>pcb_a[i].Priority>>pcb_a[i].Alltime>>pcb_a[i].Starttime>>pcb_a[i].Blocktime;
		pcb_a[i].State=Ready;
	}
//	for(int i=0;i<n;i++)
//	{
//		cout<<pcb_a[i].ID<<" "<<pcb_a[i].Arrival_time<<" "<<pcb_a[i].Priority<<" "<<pcb_a[i].CPUtime<<" "<<pcb_a[i].Alltime<<" "<<pcb_a[i].Starttime<<" "<<pcb_a[i].Blocktime;
//		cout<<" "<<pcb_a[i].State<<endl;
//	}
	while(1)
	{
		flag=0;
		cout<<"Time:"<<time<<endl;
		for(int i=0;i<n;i++)
		{
			if(pcb_a[i].Arrival_time==time)
			{
				tmp=new PCBnode;
				tmp->module=pcb_a[i];
				tmp->Next=NULL;
				InReady(Rhead,tmp);
			}
		}	
		if(Rhead->Next!=NULL)
		{
			current=Rhead->Next;
			Rhead->Next=Rhead->Next->Next;
			current->Next=NULL;
			PCBnode *traverse;//遍历指针
			PCBnode *Ftraverse;//遍历指针前一个  
			traverse=Rhead->Next;
  			while(traverse!=NULL)//遍历就绪队列 
			{
				traverse->module.Priority=traverse->module.Priority+1;
				traverse=traverse->Next;
			}
			Ftraverse=Bhead;
			traverse=Ftraverse->Next;
  			while(traverse!=NULL)
			{
				traverse->module.Blocktime=traverse->module.Blocktime-1;
				if(traverse->module.Blocktime==0)
				{
					tmp=traverse;
					Ftraverse->Next=traverse->Next;
					traverse=traverse->Next;
					tmp->Next=NULL;
					InReady(Rhead,tmp);
				}
				else
				{
					Ftraverse=traverse;
					traverse=Ftraverse->Next;
				}
			}
			current->module.CPUtime=current->module.CPUtime+1;//run time +1
			current->module.Priority=current->module.Priority-3;
			if(current->module.CPUtime==current->module.Alltime)
			{
				current->module.State=Finsh;
				pcb_a[current->module.ID-1].State=Finsh;        //finsh
				Inqueue(Fhead,current);
			}
			else if(current->module.CPUtime==current->module.Starttime)
			{
				current->module.State=Block;        //block
				Inqueue(Bhead,current);
			}
			else
			{
				InReady(Rhead,current);
			}
			cout<<"RUN:"<<current->module.ID<<endl;
			cout<<"READY:"<<endl;
			Printqueue(Rhead); 
			cout<<"BLOCK:"<<endl;
			Printqueue(Bhead);
			cout<<"FINSH:"<<endl;
			Printqueue(Fhead);  
		}
		else
		{
			cout<<"RUN:"<<"NULL"<<endl;
			cout<<"READY:"<<"NULL"<<endl<<endl<<endl;
		}
		for(int i=0;i<n;i++)
		{
			if(pcb_a[i].State!=Finsh)
			{
				flag++;
			}
		}
		if(flag==0)
			break;
		time++;
	}
	return 0;
}

void InReady(PCBnode* head,PCBnode *x)
{
		if(head->Next==NULL)
		{
			head->Next=x;
		}
		else
		{
			PCBnode *before=NULL,*after=NULL;
			before=head;
			after=before->Next;
			while(after!=NULL)
			{
				if(after->module.Priority<x->module.Priority)
				{
					before->Next=x;
					x->Next=after;				
					break;
				}
				before=after;
				after=before->Next;
			}
			if(after==NULL)
			{
				before->Next=x;
			}
		}
}

void Inqueue(PCBnode* head,PCBnode *x)
{
		if(head->Next==NULL)
		{
			head->Next=x;
		}
		else
		{
			PCBnode *check=head;
			while(check->Next!=NULL)
			{
				check=check->Next;
			}
			check->Next=x;
		}
}

void Printqueue(PCBnode* head)
{
	PCBnode *traverse; 
	traverse=head->Next;
	if(traverse==NULL)
	{
		cout<<"NULL!!!"<<endl<<endl;
	}
	else
	{
		cout<<"       "<<"ID"<<" "<<"Priority"<<" "<<"Arrivaltime"<<" "<<"RESTtime"<<" "<<"RESTBLOCKtime"<<endl;
		while(traverse!=NULL)  //遍历就绪队列 
		{
			cout<<"       "<<traverse->module.ID<<"      "<<traverse->module.Priority<<"      "<<traverse->module.Arrival_time;
			cout<<"          "<<traverse->module.Alltime-traverse->module.CPUtime<<" "<<"          "<<traverse->module.Blocktime<<endl;
			traverse=traverse->Next;
		}
		cout<<endl<<endl;
	}
}

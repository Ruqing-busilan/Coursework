#include <bits/stdc++.h>

using namespace std;

const int BLOCK_NUM=3;

struct page
{
	int pnum;
	bool state;
}p[100];

struct block
{
	int pnum;
	bool state;
}b[BLOCK_NUM];

int page_size;
int LRU[100]; 
queue<int> fifo;

int main()
{
	int n,process_size,page_num,addr,tmp_num,select;
	cout<<"输入页面大小（以K为单位）："<<endl;
	cin>>n;
	page_size=n*1024;
	cout<<"输入进程大小："<<endl;
	cin>>process_size;
	page_num=ceil((double)process_size/page_size);
	for(int i=0;i<page_num;i++)
    {
        p[i].pnum=-1;
        p[i].state=false;
        LRU[i]=0;
    }
	for(int i=0;i<BLOCK_NUM;i++)
        b[i].state=true;
    cout<<"页号 物理块号 状态："<<endl;
    for(int i=0;i<page_num;i++)
        cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
    cout<<"选择淘汰算法："<<endl;
    cout<<"1、FIFO算法"<<endl;
    cout<<"2、LRU算法"<<endl;
    cin>>select; 
    cout<<"输入访问的地址："<<endl;
    while(cin>>addr,addr>=0)
    {
    	for(int i=0;i<page_num;i++)
			if(p[i].state==true)
				LRU[i]--;
        if(addr>=0&&addr<=process_size)
        {
            tmp_num=(double)addr/page_size;
//            p[tmp_num].time=time;
            if(p[tmp_num].state==true)
            {
            	LRU[tmp_num]=1;//最近使用一次 
                cout<<"该页在内存中已存在！"<<endl;
                cout<<"页号 物理块号 状态："<<endl;
                for(int i=0;i<page_num;i++)
                    cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
            }
            else
            {
                int flag=0;
                cout<<"该页不在内存！正在调入内存！"<<endl;
                for(int i=0;i<BLOCK_NUM;i++)
                {
                    if(b[i].state==true)
                    {
                        p[tmp_num].pnum=i;
                        p[tmp_num].state=true;
                        fifo.push(tmp_num);
                        b[i].state=false;
                        LRU[tmp_num]=1;//最近使用一次 
                        flag++;
                        break;
                    }
                }
                if(flag==0)
                {
                    cout<<"页框已满！选择淘汰算法！"<<endl;
					switch(select)
					{
						case 1:	{
								int tmp=fifo.front();
                    			p[tmp_num].pnum=p[tmp].pnum;
                    			p[tmp].pnum=-1;
                    			p[tmp_num].state=true;
                   				p[tmp].state=false;
                    			fifo.pop();
								break;
								}
						case 2:	{
								int Lessuse=999,index; 
								for(int i=0;i<page_num;i++)
								{
									if(p[i].state==true)
									{
										if(LRU[i]<Lessuse)
										{
											Lessuse=LRU[i];
											index=i;
										}
									}
								} 
								p[tmp_num].pnum=p[index].pnum;
                    			p[index].pnum=-1;
                    			p[tmp_num].state=true;
                   				p[index].state=false;
                   				LRU[index]=0;
								break;
								}
						default:cout<<"输入淘汰算法序号错误！"<<endl;
								exit(0);	
					}
                }
                cout<<"页号 物理块号 状态："<<endl;
                for(int i=0;i<page_num;i++)
                    cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
            }
        }
        else
            cout<<"输入地址有误："<<endl;
        cout<<"输入访问的地址："<<endl;
    }
	return 0;
}

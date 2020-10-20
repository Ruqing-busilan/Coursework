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
	cout<<"����ҳ���С����KΪ��λ����"<<endl;
	cin>>n;
	page_size=n*1024;
	cout<<"������̴�С��"<<endl;
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
    cout<<"ҳ�� ������ ״̬��"<<endl;
    for(int i=0;i<page_num;i++)
        cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
    cout<<"ѡ����̭�㷨��"<<endl;
    cout<<"1��FIFO�㷨"<<endl;
    cout<<"2��LRU�㷨"<<endl;
    cin>>select; 
    cout<<"������ʵĵ�ַ��"<<endl;
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
            	LRU[tmp_num]=1;//���ʹ��һ�� 
                cout<<"��ҳ���ڴ����Ѵ��ڣ�"<<endl;
                cout<<"ҳ�� ������ ״̬��"<<endl;
                for(int i=0;i<page_num;i++)
                    cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
            }
            else
            {
                int flag=0;
                cout<<"��ҳ�����ڴ棡���ڵ����ڴ棡"<<endl;
                for(int i=0;i<BLOCK_NUM;i++)
                {
                    if(b[i].state==true)
                    {
                        p[tmp_num].pnum=i;
                        p[tmp_num].state=true;
                        fifo.push(tmp_num);
                        b[i].state=false;
                        LRU[tmp_num]=1;//���ʹ��һ�� 
                        flag++;
                        break;
                    }
                }
                if(flag==0)
                {
                    cout<<"ҳ��������ѡ����̭�㷨��"<<endl;
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
						default:cout<<"������̭�㷨��Ŵ���"<<endl;
								exit(0);	
					}
                }
                cout<<"ҳ�� ������ ״̬��"<<endl;
                for(int i=0;i<page_num;i++)
                    cout<<setw(3)<<i<<setw(5)<<p[i].pnum<<setw(7)<<p[i].state<<endl;
            }
        }
        else
            cout<<"�����ַ����"<<endl;
        cout<<"������ʵĵ�ַ��"<<endl;
    }
	return 0;
}

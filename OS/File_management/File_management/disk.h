#pragma once

using namespace std;

enum FileType{NORMAL,DIR};

struct INode{
	int fileType;//0表示普通文件，1表示目录文件
	short iaddr[13];
	int fileLength;
	int linkCount;//联结计数
};

struct DirChild
{
	char filename[14];
	short i_num;
};

struct DirNode
{
	DirChild childItem[64];
	short DirCount;//联结计数
};

char FileName[] = "Disk.txt";
short SuperBlock[51];
DirNode *currDir;
INode *iNode;
short freeDirNode[29];                     //可用索引节点栈
short freeDirCount = 30;                     //索引节点栈指针
short currDirNum;                   //当前目录所在的磁盘号
short currINum;
short freeTotalB = 20450;
short freeBlockNum = 0;            //当前可用盘块所在组记录的盘块号

void Format();//格式化
void Linkdisk();//成组链接
void ArrayEqual(short arr[51], short begin, short end);
void DiskWrite(short arr[], short diskNum,short n);
void DiskRead(short arr[], short diskNum, short n);
void INodeInit();
void DirInit(DirNode *currDir, FileType fileType, char filename[14], INode *iNode, short diskNum);
void InitCreate(DirNode *currDir, FileType fielType, char filename[14], INode *iNode, short diskNum);
short FindFreeDir();//寻找一个空闲目录块
short FindAnEmpty();//寻找一个空闲数据块
void DiskDirWrite(DirNode *currDir, short diskNum);
void DiskINodeRead(INode *currDir, short diskNum);
void DiskINodeWrite(INode *iNode, short diskNum);
void RecoverOne(short diskNum);
void RecoverDisk(INode *iNode);

void ArrayEqual(short arr[51], short begin, short end)
{
	for (short i = 0; i < end - begin + 1; i++)
		arr[50 - i] = begin + i;
}

void Format()
{
	cout << "Simulate Unix File System" << endl;
	cout << "System is initializing......"<<endl;
	// 打开文件
	FILE *fp = fopen(FileName, "w+");
	if (fp == NULL)
	{
		cout << "System Error！Initialize Failed！" << endl;
		return;
	}
	for (int i = 0; i < 20971520; i++)//20971520=20Mb,暂时2mb
		fprintf(fp, "%c", '0');
	// 关闭文件
	fclose(fp);
}

void Linkdisk()
{
	//临时空闲栈
	SuperBlock[0] = 50;
	ArrayEqual(SuperBlock, 31, 80);
	DiskWrite(SuperBlock, 0, 51);

	for (short i = 1; i < 408; i++)
	{
		SuperBlock[0] = 50;
		ArrayEqual(SuperBlock, i * 50 + 31, i * 50 + 80);
		DiskWrite(SuperBlock, i * 50 + 30, 51);
		DiskRead(SuperBlock, 0, 51);
	}
	ArrayEqual(SuperBlock, 408 * 50 + 31, 408 * 50 + 79);
	SuperBlock[1] = 0;//49
	DiskWrite(SuperBlock, 408 * 50 + 30, 51);

	cout << "Disk 'Disk.txt' is Created ,Size:20MB" << endl;
}

void DiskWrite(short arr[], short diskNum,short n)
{
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL)
	{
		cout << "写文件处错误!请重新输入!" << endl;
		return;
	}
	//设置文件指针
	if (fseek(fp, 1024 * diskNum, 0))//从0处偏移1024 * diskNum
		cout << "文件指针错误!" << endl;
	fwrite(arr, sizeof(short), n, fp);
	//	fwrite(buffer, sizeof(short), count, fp);
	//	返回值：返回实际写入的数据块数目
	//	（1）buffer：是一个指针，对fwrite来说，是要获取数据的地址；
	//	（2）size：要写入内容的单字节数；
	//	（3）count : 要进行写入size字节的数据项的个数；
	//	（4）stream : 目标文件指针；
	//	（5）返回实际写入的数据项个数count。
	fclose(fp);
}

void DiskRead(short arr[], short diskNum, short n)
{
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL)
	{
		cout << "读文件处错误！请重新输入！" << endl;
		return;
	}
	//设置文件指针
	if (fseek(fp, 1024 * diskNum, 0))
		cout << "文件指针错误" << endl;
	fread(arr, sizeof(short), n, fp);
	fclose(fp);
}

void INodeInit()
{
	for (int i = 0; i < 30; i++)
		freeDirNode[i] = 30 - i;	//可用索引节点栈
	freeDirCount = 30;		//索引节点栈指针
}

void DirInit(DirNode *currDir, FileType fileType, char filename[14], INode *iNode, short diskNum)
{
	InitCreate(currDir, fileType, filename, iNode, diskNum);
	DiskRead(SuperBlock, 0, 51);
}

void InitCreate(DirNode *currDir, FileType fileType, char filename[14], INode *iNode, short diskNum)
{
		if (fileType == DIR) 
		{
			int blockNum = FindFreeDir();
			currDirNum = blockNum;
			for (int i = 0; i < 64; i++) {
				strcpy(currDir->childItem[i].filename, "*************");
				currDir->childItem[i].i_num = -1;
			}
			DiskDirWrite(currDir, blockNum);
		}
}

short FindFreeDir() 
{
	if (freeDirCount == 0) 
	{
		cout << "无空余目录节点!" << endl;
		return -1;
	}
	else 
	{
		freeDirCount--;
		short s = freeDirNode[freeDirCount];
		freeDirNode[freeDirCount] = -1;
		return s;       //可用索引节点栈
	}
}

void DiskDirWrite(DirNode *currDir, short diskNum) 
{
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL)
	{
		cout << "写文件处错误，请重新输入" << endl;
		return;
	}
	//设置文件指针
	if (fseek(fp, long(1024 * diskNum), 0))
		cout << "文件指针错误!" << endl;
	for (int i = 0; i < 64; i++)
	{
		fprintf(fp, "%hd", currDir->childItem[i].i_num);
		fputs(currDir->childItem[i].filename, fp);

	}
	fclose(fp);
}

void DiskINodeRead(INode *iNode, short diskNum)
{
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL)
	{
		cout << "读文件处错误！请重新输入！" << endl;
		return;
	}
	//设置文件指针
	if (fseek(fp, 1024 * diskNum, 0))
		cout << "文件指针错误!" << endl;
	fread(iNode->iaddr, 2, 13, fp);
	fscanf(fp, "%d %d", &iNode->fileLength, &iNode->linkCount);
	int temp = int(fgetc(fp));
	switch (temp)
	{
	case 0:iNode->fileType = NORMAL;
		break;
	case 1:iNode->fileType = DIR;
		break;
	}
	fclose(fp);
}

short FindAnEmpty()
{
	short temp;
	if (SuperBlock[0] > 1)
	{
		SuperBlock[0]--;
		temp = SuperBlock[SuperBlock[0] + 1];
		freeTotalB--;//总剩余数-1
		return temp;
	}
	else
	{
		if (SuperBlock[1] == 0) 
		{
			cout << "盘片用尽!" << endl;
			return -1;
		}
		temp = freeBlockNum;
		freeBlockNum = SuperBlock[1];
		DiskRead(SuperBlock, SuperBlock[1], 51);
		if (temp == 0) 
		{
			SuperBlock[0]--;
			temp = SuperBlock[SuperBlock[0] + 1];
		}
		freeTotalB--;
		return temp;
	}
}

void DiskINodeWrite(INode *iNode, short diskNum) 
{
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL)
	{
		cout << "写文件处错误，请重新输入" << endl;
		return;
	}
	//设置文件指针
	if (fseek(fp, 1024 * diskNum, 0))
		cout << "文件指针错误" << endl;
	fwrite(iNode->iaddr, 2, 13, fp);
	fprintf(fp, "%d %d", iNode->fileLength, iNode->linkCount);
	fputc(iNode->fileType, fp);
	fclose(fp);
}

void RecoverOne(short diskNum)
{
	freeTotalB++;
	if (SuperBlock[0] <= 49)
	{
		SuperBlock[0]++;
		SuperBlock[SuperBlock[0]] = diskNum;
	}
	else
	{//SS[0]==50
		DiskWrite(SuperBlock, freeBlockNum, 51);  //将空白的一组回写到上一组记录空闲盘块号的磁盘
		freeBlockNum = SuperBlock[1];            //将当前空白的一组第一个盘块作为下一个盘组的记录盘
		//修改超级栈
		SuperBlock[1] = diskNum;
		SuperBlock[0] = 1;
	}
}

void RecoverDisk(INode *iNode)
{
	short i;
	i = 10;
	short left = iNode->fileLength;
	while (left&&i)
	{//直接索引回收
		RecoverOne(iNode->iaddr[10 - i]);
		left--;
		i--;
	}
	if (left > 0)
	{   //一级索引回收
		i = 512;
		short dir1[512];
		DiskRead(dir1, iNode->iaddr[10], 512);
		while (left&&i)
		{
			RecoverOne(dir1[512 - i]);
			i--;
			left--;
		}
		RecoverOne(iNode->iaddr[10]);
	}
	if (left > 0)
	{                                                                                //二级索引
		short k = 512;
		short dir[512];
		short dirChild[512];
		DiskRead(dir, iNode->iaddr[11], 512);//二级索引1次寻址
		while (left&&k)
		{                                              //二级索引1次寻址
			DiskRead(dirChild, dir[512 - k], 512);
			short j = 512;
			while (left&&j)
			{                                    //二级索引二次回收
				RecoverOne(dirChild[512 - j]);
				left--;
				j--;

			}
			RecoverOne(dir[512 - k]);//二级索引一次寻址
			k--;
		}
		RecoverOne(iNode->iaddr[11]);
	}
}
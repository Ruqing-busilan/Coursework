#pragma once

using namespace std;

void help();
void create(DirNode *currDir, char fileName[14], INode *iNode, short length);
void open(DirNode *currDir, char fileName[14], INode *iNode);
void dele(DirNode *currDir, char fileName[14], INode *iNode);
void makedir(DirNode *currDir, char fileName[14], INode *iNode, short length);
void removedir(DirNode *currDir, char fileName[14], INode *iNode);
void dir(DirNode *currDir, INode *iNode);
void info(DirNode *currDir, INode *iNode);
short IsFileExist(DirNode *currDir, char fileName[14]);
bool IsFile(INode *iNode, short diskNum);
bool IsDir(INode *iNode, short diskNum);
void createfile(DirNode *currDir, char fileName[14], INode *iNode, short length, FileType fileType);
void CreateINode(INode *iNode, FileType fileType, short linkCount, short length);
void InsertDir(DirNode *currDir, char fileName[14], short blockNum);
void DelDirItem(DirNode *currDir, char fileName[14]);
void CleanINode(INode *iNode);
void ShowFileInfo(INode *iNode, char fileName[14]);
void ShowBlockInfo(INode *iNode);

void help()
{
	cout << endl;
	cout << "\t--------------------------------------------------" << endl;
	cout << "\t\tSimulate Unix File System" << endl;
	cout << "\t--------------------------------------------------" << endl;
	cout << "\t\tExit system: exit"<< endl;
	cout << "\t\tCreate file: create filename size"<< endl;
	cout << "\t\tMake Subdirectory：mkdir dirname"<< endl;
	cout << "\t\tOpen File:open filename"<< endl;
	cout << "\t\tDelete File：delete filename"<< endl;
	cout << "\t\tRemove Subdirectory：rmdir dirname"<< endl;
	cout << "\t\tDisplay Directory：dir" << endl;
	cout << "\t\tDisplay System Infomation：info"<< endl;
	cout<<"\t\tClear screen:clear"<<endl;
	cout << "\t--------------------------------------------------" << endl << endl;
}

void create(DirNode *currDir, char fileName[14], INode *iNode, short length)
{
	int blockNum = IsFileExist(currDir, fileName);
	if (blockNum != -1) 
	{
		//有重名名，进一步判断
		if (IsFile(iNode, blockNum))
			cout << "File Exists.Create Failed." << endl;
	}
	else 
	{
		//存在文件，为索引文件，或者无重名现象,创建文件，并分配iNOde节点和磁盘空间
		createfile(currDir, fileName, iNode, length, NORMAL);
	}
}

short IsFileExist(DirNode *currDir, char fileName[14]) 
{
	for (int i = 0; i < 64; i++) 
	{
		if (strcmp(fileName, currDir->childItem[i].filename) == 0)
			return currDir->childItem[i].i_num;
	}
	return -1;
}

bool IsFile(INode *iNode, short diskNum) 
{
	DiskINodeRead(iNode, diskNum);
	if (iNode->fileType == NORMAL)
		return true;
	else
		return false;
}

bool IsDir(INode *iNode, short diskNum)
{
	DiskINodeRead(iNode, diskNum);
	if (iNode->fileType == DIR)
		return true;
	else
		return false;
}

void createfile(DirNode *currDir, char fileName[14], INode *iNode, short length, FileType fileType)
{
	int blockNum;
	if (length > freeTotalB) 
	{
		cout << "当前文件超出长度!" << endl;
		return;
	}
	CreateINode(iNode, fileType, 0, length);
	blockNum = FindAnEmpty();//分配一个空余磁盘存储iNode
	InsertDir(currDir, fileName, blockNum);//在当前目录树上增加子树
	DiskINodeWrite(iNode, blockNum);//INode写入
	CleanINode(iNode);
	DiskDirWrite(currDir, currDirNum);//写目录
	cout << "Complete!" << endl;
}

void CreateINode(INode *iNode, FileType fileType, short linkCount, short length)
{
	iNode->fileType = fileType;
	iNode->linkCount = linkCount;
	iNode->fileLength = length;
	//为目录磁盘，分配目录节点
	if (fileType == DIR) 
	{
		iNode->iaddr[0] = FindFreeDir();
		return;
	}
	//根据文件长度分配文件磁盘节点
	//直接寻址
	short i=10;
	short left = length;
	while (left&&i) 
	{
		iNode->iaddr[10 - i] = FindAnEmpty();
		left--;
		i--;
	}
	if (left > 0) 
	{   //一级索引
		i = 512;
		short dir[512];
		iNode->iaddr[10] = FindAnEmpty();
		while (left&&i) 
		{
			dir[512 - i] = FindAnEmpty();
			i--;
			left--;
		}
		if (i != 0)
			dir[512 - i + 1] = -1;//标志文件结束
		DiskWrite(dir, iNode->iaddr[10],512);
		if (left > 0) 
		{                                                                                //二级索引
			short k = 512;
			short dirChild[512];
			iNode->iaddr[11] = FindAnEmpty();
			while (left&&k) 
			{                                              //二级索引1次寻址
				dir[512 - k] = FindAnEmpty();
				short j = 512;
				while (left&&j) 
				{                                    //二级索引二次寻址
					dirChild[512 - j] = FindAnEmpty();
					left--;
					j--;
				}
				if (j != 0)
					dir[512 - j + 1] = -1;                       //标志二级索引二次寻址结束
				DiskWrite(dirChild, dir[512 - k],512);
				k--;
			}
			if (k != 0)
				dir[512 - k + 1] = -1;//标志文件结束
			DiskWrite(dir, iNode->iaddr[11], 512);//写二级索引一次寻址中盘块记录的一次寻的盘块号
		}
	}
	//for (short i = 0; i < 13; i++)
	//	cout << endl << iNode->iaddr[i] << endl;
}

void InsertDir(DirNode *currDir, char fileName[14], short blockNum) 
{
	strcpy(currDir->childItem[currDir->DirCount].filename, fileName);
	currDir->childItem[currDir->DirCount].i_num = blockNum;
	currDir->DirCount++;
	return;
}

void DelDirItem(DirNode *currDir, char fileName[14]) 
{
	for (int i = 0; i < 64; i++) 
	{
		if (strcmp(fileName, currDir->childItem[i].filename) == 0) 
		{
			strcpy(currDir->childItem[i].filename, "************");
			currDir->childItem[i].i_num = -1;
			return;
		}
	}
	cout << "Delete Failed" << endl;
}

void CleanINode(INode *iNode) 
{
	iNode->fileType = 0;
	iNode->linkCount = -1;
	iNode->fileLength = -1;
	//根据文件长度非配文件磁盘节点
	//直接寻址
	for (short i = 0; i < 13; i++)
		iNode->iaddr[i] = -1;
}

void open(DirNode *currDir, char fileName[14], INode *iNode) 
{
	int blockNum = IsFileExist(currDir, fileName);
	if (blockNum == -1) 
	{
		//不存在该文件，退出
		cout << "File not Exists!" << endl;
		return;
	}
	else 
	{
		if (IsFile(iNode, blockNum))
		{
			ShowFileInfo(iNode, fileName);
			ShowBlockInfo(iNode);
		}
		if (IsDir(iNode, blockNum))
		{
			cout << "Sorry, System does't Support Access to Direction Currently."<<endl;
			CleanINode(iNode);
		}
	}	
}

void ShowFileInfo(INode *iNode, char fileName[14]) 
{

	cout << "文件名        " << fileName;

	cout << "      文件类型  ";

	switch (iNode->fileType) 
	{
		case NORMAL:cout << "< 文件 > ";
					break;
		case DIR:cout << "< 目录 > ";
				break;
	}
	cout << "         " << iNode->fileLength << "KB" << endl;
}

void ShowBlockInfo(INode *iNode) 
{
	short dir[512];
	short i;
	i = 10;
	short left = iNode->fileLength;
	while (left&&i) 
	{
		cout << (iNode->fileLength - left) << "-" << iNode->iaddr[10 - i] << "  ";
		left--;
		i--;
	}
	if (left > 0) 
	{
		i = 512;
		short dir1[512];
		/*for (short i = 0; i < 13; i++)
			cout << endl << iNode->iaddr[i] << endl;*/
		DiskRead(dir1, iNode->iaddr[10],512);
		while (left&&i) 
		{
			cout << (iNode->fileLength - left) << "-" << dir1[512 - i] << "  ";
			i--;
			left--;
		}
	}
	if (left > 0) 
	{                    //二级索引
		short k = 512;
		short dirChild[512];
		DiskRead(dir, iNode->iaddr[11],512);
		while (left&&k) 
		{                                              //二级索引1次寻址
			DiskRead(dirChild, dir[512 - k],512);
			short j = 512;
			while (left&&j) 
			{                                    //二级索引二次寻址
				cout << (iNode->fileLength - left) << "-" << dirChild[512 - j] << "  ";
				left--;
				j--;
			}
			k--;
		}
	}
	cout << endl;
}

void makedir(DirNode *currDir, char fileName[14], INode *iNode, short length) 
{
	int blockNum = IsFileExist(currDir, fileName);
	if (blockNum != -1) 
	{//有重名名，进一步判断
		if (IsDir(iNode, blockNum))
			cout << "Direction Exists!Create Failed!" << endl;
	}
	else 
	{//存在文件但为普通文件，或者无重名现象。创建文件，并分配iNode节点和磁盘空间
		createfile(currDir, fileName, iNode, length, DIR);
		CleanINode(iNode);
	}
}

void dir(DirNode *currDir, INode *iNode) 
{
	int flag = 0;
	for (int i = 0; i < currDir->DirCount; i++) 
	{
		if (currDir->childItem[i].i_num != -1) 
		{
			DiskINodeRead(iNode, currDir->childItem[i].i_num);
			ShowFileInfo(iNode, currDir->childItem[i].filename);
			flag = 1;
		}
		CleanINode(iNode);
	}
	if (flag == 0)
		cout << "Empty Item!" << endl;
}

void dele(DirNode *currDir, char fileName[14], INode *iNode) 
{
	short blockNum = IsFileExist(currDir, fileName);
	if (blockNum == -1) 
	{//不存在该文件，退出
		cout << "File Not Exists!Delete Failed!" << endl;
	}
	else 
	{
		if (IsFile(iNode, blockNum)) 
		{
			RecoverDisk(iNode);
			DelDirItem(currDir, fileName);
			CleanINode(iNode);
		}
		else 
		{
			cout << "File Not Exists!Delete Failed!" << endl;
		}
	}
	cout << "Complete!" << endl;
}

void removedir(DirNode *currDir, char fileName[14], INode *iNode) 
{
	short blockNum = IsFileExist(currDir, fileName);
	if (blockNum == -1) 
	{//不存在该文件，退出
		cout << "Direction Not Exists!Delete Failed!" << endl;
	}
	else 
	{
		if (IsDir(iNode, blockNum)) 
		{
			RecoverDisk(iNode);
			DelDirItem(currDir, fileName);
			CleanINode(iNode);
		}
		else 
		{
			cout << "Direction Not Exists!Delete Failed!" << endl;
		}
	}
	cout << "Complete!" << endl;
}

void info(DirNode *currDir, INode *iNode)
{
	cout <<"Rest:"<<freeTotalB << endl;
}
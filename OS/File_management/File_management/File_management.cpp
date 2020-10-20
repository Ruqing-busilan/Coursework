// File_management.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <fstream>
#include "disk.h"
#include "function.h"
#include "command.h"

using namespace std;

int main()
{
	char path[] = "root\\a:\\";
	char com[10];
	char FileName[14];
	char dirName[14];
	int FileLen = 1024;
	DirNode *rootNode;              //根节点
	currDir = new DirNode;
	currDir->DirCount = 0;
	rootNode = currDir;
	iNode = new INode;
	Format();				//格式化
	Linkdisk();				//成组链接
	INodeInit();
	DirInit(currDir, DIR, path, iNode, 0);
	InitCommand();
	cout << endl << "help:View Help Command." << endl;
	while (1)
	{
		int p = -1;
		cout << "Adiministrator/root/";
		cin >> com;       // 输入命令并且查找命令的相关操作 
		for (int i = 0; i < 10; i++)
		{
			if (strcmp(com, cmd[i].com) == 0)
			{
				p = i;
				break;
			}
		}
		switch (p)
		{
			case 0: system(0);
					return 0;
			case 1: help();
					break;
			case 2: //cout << "Input Filename:" << endl;	//新建文件
					cin >> FileName;
					fflush(stdin);
					//cout << "Input File Length:" << endl;
					cin >> FileLen;
					fflush(stdin);
					if (FileLen<0 || FileLen>freeTotalB) 
					{
						cout << "File Length is Illegal!" << endl;
						break;
					}
					create(currDir, FileName, iNode, FileLen);
					break;
			case 3: //cout << "Input Direction Name:" << endl;
					cin >> dirName;
					fflush(stdin);
					makedir(currDir, dirName, iNode, 1);
					break;
			case 4: //cout << "Input FileName:" << endl;      //打开文件
					cin >> FileName;
					open(currDir, FileName, iNode);
					break;
			case 5: cin >> FileName;
					dele(currDir, FileName, iNode);
					break;
			case 6: cin >> dirName;
					removedir(currDir, dirName, iNode);
					break;
			case 7: dir(currDir, iNode);		 //显示当前目录下的信息
					break;
			case 8:	info(currDir, iNode);
					break;
			case 9: system("cls");
					break;
			default: printf("Instruction Error！\n");
					break;
		}
	}
	system("pause");
	return 0;
}
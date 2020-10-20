#pragma once

struct command		//命令行
{
	char com[10];
}cmd[10];

void InitCommand()			//初始化命令参数
{
	strcpy(cmd[0].com, "exit");			//退出系统
	strcpy(cmd[1].com, "help");			//帮助提示
	strcpy(cmd[2].com, "create");		//创建文件
	strcpy(cmd[3].com, "mkdir");		//创建目录
	strcpy(cmd[4].com, "open");			//打开文件
	strcpy(cmd[5].com, "delete");		//删除文件
	strcpy(cmd[6].com, "rmdir");		//删除目录
	strcpy(cmd[7].com, "dir");			//显示目录
	strcpy(cmd[8].com, "info");			//显示系统信息
	strcpy(cmd[9].com, "clear");		//清屏
}
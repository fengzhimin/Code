/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-07 00:32
* Last modified: 2016-11-07 23:35
* Email        : 374648064@qq.com
* Filename     : dirOper.c
* Description  : 
******************************************************/

#include "common/dirOper.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int Is_Dir(const char *path)
{
	struct stat st;
	if(lstat(path, &st) == -1)
		return errno;

	if(S_ISDIR(st.st_mode))
		return -1;
	else
		return -2;
}

int JudgeConfFile(char *path, const char type[][20], char configfilepath[][FILE_PATH_MAX_LENGTH], int point)
{

	char *temp_type = strrchr(path, '.');
	if(temp_type != NULL)   //是一个有后缀的文件
	{
		int _config_type_size = GetConfig_TypeNum();
		for(int i = 0; i < _config_type_size; i++)
		{
			if(strcasecmp(temp_type, type[i]) == 0)
			{
				strcpy(configfilepath[point], path);
				return 1;
			}
		}
	}

	return 0;
}

int FindFileByType(char *path, const char type[][20], char configfilepath[][FILE_PATH_MAX_LENGTH], int point)
{
	if(point >= CONFIG_FILE_MAX_NUM)   //判断是否配置文件个数超过预定设置的最大个数
		return -1;      
	char temp[FILE_PATH_MAX_LENGTH], temp1[FILE_PATH_MAX_LENGTH];
	strcpy(temp1, path);   //临时复制一份
	int _size = strlen(temp1);
	while(temp1[_size - 1] == '/')   //删除结尾的斜杠
	{
		temp1[_size - 1] = '\0';
		_size--;
	}
	if(Is_Dir(temp1) == -2)   //判断输入的是否为文件夹
		return -2;

	DIR *pdir;
	struct dirent *pdirent;
	pdir = opendir(temp1);
	while((pdirent = readdir(pdir)) != NULL)
	{
		if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)   //跳过.和..两个目录
			continue;
		sprintf(temp, "%s/%s", temp1, pdirent->d_name);
		if(Is_Dir(temp) == -1)
			point = FindFileByType(temp, type, configfilepath, point);   //是子目录则进行继续查找
		else
		{	
			if(JudgeConfFile(temp, type, configfilepath, point) == 1)
				point++;
		}
	}

	return point;
}

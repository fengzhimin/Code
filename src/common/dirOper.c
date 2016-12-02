/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-07 00:32
* Last modified: 2016-11-12 00:53
* Email        : 374648064@qq.com
* Filename     : dirOper.c
* Description  : 
******************************************************/

#include "common/dirOper.h"
#include "log/logOper.h"
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
	{
		char error_info[200];
		sprintf(error_info, "%s%s%s%s%s", "判断: ", path, " 是否为文件夹时错误！错误信息： ", strerror(errno), "\n");
		RecordLog(error_info);
		return errno;
	}

	if(S_ISDIR(st.st_mode))
		return -1;
	else if(S_ISREG(st.st_mode))
		return -2;
	else
		return -3;
}

int JudgeConfFile(char *path, const char type[][20], char configfilepath[][FILE_PATH_MAX_LENGTH], int point)
{
	int _config_type_num = GetConfig_TypeNum();
	int _config_type_length;
	int _path_length = strlen(path);
	char temp_type[20];
	for(int i = 0; i < _config_type_num; i++)
	{
		_config_type_length = strlen(type[i]);
		if(_path_length < _config_type_length)         //如果文件的长度小于配置文件类型的长度，则可以断定该文件不是配置文件:
			continue;
		memset(temp_type, 0, 20);
		strcpy(temp_type, &(path[_path_length - _config_type_length]));    //截取path最后_config_type_length个字符
		if(strcasecmp(temp_type, type[i]) == 0)                                //这样做的目的是为了更好的添加配置文件类型例如: .conf.in
		{
			strcpy(configfilepath[point], path);
			return 1;
		}
	}

	return 0;
}

int FindFileByType(char *path, const char type[][20], char configfilepath[][FILE_PATH_MAX_LENGTH], int point)
{
	char temp[FILE_PATH_MAX_LENGTH], temp1[FILE_PATH_MAX_LENGTH];
	strcpy(temp1, path);   //临时复制一份
	int _size = strlen(temp1);
	while(temp1[_size - 1] == '/')   //删除结尾的斜杠
	{
		temp1[_size - 1] = '\0';
		_size--;
	}
	if(Is_Dir(temp1) >= 0)   //判断是否出错
		return -3;
	else if(Is_Dir(temp1) == -2)   //判断用户输入的是否为一个配置文件的绝对路径
	{
		strcpy(configfilepath[point++], path);   
		return point;
	}

	DIR *pdir;
	struct dirent *pdirent;
	pdir = opendir(temp1);
	if(pdir == NULL)       //打开文件夹失败
	{
		char error_info[200];
		sprintf(error_info, "%s%s%s%s%s", "打开文件夹: ", temp1, " 失败！ 错误信息： ", strerror(errno), "\n");
		RecordLog(error_info);
		return -3;
	}
	while((pdirent = readdir(pdir)) != NULL)
	{
		if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)   //跳过.和..两个目录
			continue;
		sprintf(temp, "%s/%s", temp1, pdirent->d_name);
		if(Is_Dir(temp) == -1)
		{
			int _temp = 0;
			_temp = FindFileByType(temp, type, configfilepath, point);   //是子目录则进行继续查找
			if(_temp >= 0)   //通过返回值判断是否出错
				point = _temp;         //更新point索引
		}
		else
		{	
			if(point >= CONFIG_FILE_MAX_NUM)   //判断是否配置文件个数超过预定设置的最大个数
			{
				RecordLog("配置文件个数超过预设的最大值!\n");
				closedir(pdir);
				return -1;
			}
			if(JudgeConfFile(temp, type, configfilepath, point) == 1)
				point++;
		}
	}

	closedir(pdir);

	return point;
}

/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-13 13:54
* Last modified: 2016-11-26 16:34
* Email        : 374648064@qq.com
* Filename     : conflictCheck.c
* Description  : 
******************************************************/

#include "resource/network/conflictCheck.h"
#include "common/fileOper.h"
#include "common/dirOper.h"
#include "common/dateOper.h"
#include "resource/network/port.h"
#include "log/logOper.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int CheckPort(char *_portFileName)
{
	char *dirCatalog = "resource/network";
	struct dirent *pdirent;
	DIR *pdir;
	if(Is_Dir(dirCatalog) == -2)
	{
		char error_info[200];
		sprintf(error_info, "%s%s", dirCatalog, " 不是一个文件夹!\n");
		RecordLog(error_info);
		return 0;
	}
	pdir = opendir(dirCatalog);
	if(pdir == NULL)       //打开文件夹失败
	{
		char error_info[200];
		sprintf(error_info, "%s%s%s%s%s", "打开文件夹: ", dirCatalog, " 失败！ 错误信息： ", strerror(errno), "\n");
		RecordLog(error_info);
		return 0;
	}

	int _ret_checkResult = 1;
	char _portFilePath[100];
	sprintf(_portFilePath, "%s/%s", dirCatalog, _portFileName);
	int _portValue[50];
	if(!GetPortValue(_portFilePath, _portValue, 50))   //获取要检查软件的端口值
		return 0;
	char temp[FILE_PATH_MAX_LENGTH];
	while((pdirent = readdir(pdir)) != NULL)
	{
		if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)   //跳过.和..两个目录
			continue;
		if(strcmp(pdirent->d_name, _portFileName) == 0)   //跳过自身文件
			continue; 
		sprintf(temp, "%s/%s", dirCatalog, pdirent->d_name);
		int temp_portValue[50];
		if(!GetPortValue(temp, temp_portValue, 50))   //获取要比较软件的端口的值
			continue;
		for(int i = 0; i < 50; i++)
		{
			if(_portValue[i] == -1)
				break;
			for(int j = 0; j < 50; j++)
			{
				if(temp_portValue[j] == -1)
					break;
				if(_portValue[i] == temp_portValue[j])
				{
					int temp_length = strlen(_portFileName) - strlen(strrchr(_portFileName, '.'));
					char _softwareName1[50] = { 0 };
					strncpy(_softwareName1, _portFileName, temp_length);    //提取被检查软件名
					temp_length = strlen(pdirent->d_name) - strlen(strrchr(pdirent->d_name, '.'));
					char _softwareName2[50] = { 0 };
					strncpy(_softwareName2, pdirent->d_name, temp_length);	//提取对比软件名
					char _date[100];
					GetLocalTime(_date, 0);  //获取当前系统时间
					char _result[200];
					sprintf(_result, "[%s]\t%s%s%s%s%s%d\n", _date, "软件: ", _softwareName1, " 与软件: ", _softwareName2, " 端口冲突，冲突端口号为：", _portValue[i]);
					//冲突信息显示方式
					if(1 == SHOWINFO || 3 == SHOWINFO)
					{
						FILE *fd = OpenFile("result.out", "a+");
						WriteFile(fd, _result);
						CloseFile(fd);
					}

					if(2 == SHOWINFO || 3 == SHOWINFO)
						printf("%s", _result);

					_ret_checkResult = -1;
				}
			}
		}
	}

	closedir(pdir);

	return _ret_checkResult;
}

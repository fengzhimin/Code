/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-04 12:47
* Last modified: 2016-11-06 00:58
* Email        : 374648064@qq.com
* Filename     : logOper.c
* Description  : 
******************************************************/

#include "log/logOper.h"
#include "common/fileOper.h"
#include "common/dateOper.h"
#include "config.h"
#include <stdlib.h>

char *CreateLogInfo(const char *logInfo, const char *file, const char* function, const int line)
{
	char _date[100];
	GetLocalTime(_date, 0);  //获取当前系统时间
	char _function[50] = "function: ";
	strcat(_function, function);   //获取正在执行的函数名
	char _file[50] = "file: ";
	strcat(_file, file);           //获取正在执行的文件名
	char _line[50] = "line: ";
	char _strLine[10];
	sprintf(_strLine, "%d", line);   
	strcat(_line, _strLine);     //获取正在执行的行数
	
	int _size = strlen(logInfo) + strlen(_date) + strlen(_function) + strlen(_file) + strlen(_line) + 20;
	char *mergeInfo = malloc(_size);
	memset(mergeInfo, 0, _size);
	strcat(mergeInfo, "[");
	strcat(mergeInfo, _date);
	strcat(mergeInfo, "]  ");
	strcat(mergeInfo, _file);
	strcat(mergeInfo, "  ");
	strcat(mergeInfo,  _function);
	strcat(mergeInfo, "  ");
	strcat(mergeInfo, _line);
	strcat(mergeInfo, "  操作：");
	strcat(mergeInfo, logInfo);

	return mergeInfo;
}

int WriteLog(const char* logName, const char* logInfo, const char *file, const char* function, const int line)
{
#if OPENLOG
	FILE * _fd = OpenFile(logName, "a");
	if(NULL == _fd)
		return -1;
	
	char *_mergeInfo = CreateLogInfo(logInfo, file, function, line);

	int _ret_write = WriteFile(_fd, _mergeInfo);

	free(_mergeInfo);
	CloseFile(_fd);

	if(_ret_write != -1)
		return 0;
#endif

	return -1;
}

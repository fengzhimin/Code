/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-11 09:04
* Last modified: 2016-11-11 09:06
* Email        : 374648064@qq.com
* Filename     : port.c
* Description  : 
******************************************************/

#include "resource/network/port.h"
#include "common/strOper.h"
#include "common/fileOper.h"
#include "log/logOper.h"
#include <errno.h>

char port_symbol[][CONFIG_KEY_MAX_NUM] = {"Listen", "port"};

int GetPort_SymbolNum()
{
	return sizeof(port_symbol)/sizeof(port_symbol[0]);
}

bool GetPortInfoFromConfigFile(ConfigInfo _portInfo[], int _portInfo_num, char *portFileName)
{
	FILE *fd = OpenFile(portFileName, "w+");
	if(fd == NULL)
	{
		char error_info[200];
		sprintf(error_info, "%s%s%s%s%s", "文件: ", portFileName, " 创建失败！ 错误信息： ", strerror(errno), "\n");
		RecordLog(error_info);
		return false;
	}
	for(int i = 0; i < _portInfo_num; i++)
	{
		if(isNum(_portInfo[i].value))
		{
			char _portConfigInfo[CONFIG_KEY_MAX_NUM+CONFIG_VALUE_MAX_NUM+5] = { 0 };
			sprintf(_portConfigInfo, "%s%s%s", _portInfo[i].key, " = ", _portInfo[i].value);
			if(-1 != WriteFile(fd, _portConfigInfo))
			{
				char error_info[200];
				sprintf(error_info, "%s%s%s%s%s", "写入: ", _portConfigInfo, " 失败！ 错误信息： ", strerror(errno), "\n");
				RecordLog(error_info);
				return false;
			}
			WriteFile(fd, "\n");
		}
	}

	CloseFile(fd);

	return true;
}

bool GetPortValue(char *_portFilePath, int *_portValue, int _portValueNum)
{
	for(int i = 0; i < _portValueNum; i++)    //初始化_portValue数组
		_portValue[i] = -1;
	FILE *fd = OpenFile(_portFilePath, "r+");
	if(fd == NULL)
	{
		char error_info[200];
		sprintf(error_info, "%s%s%s%s%s", "打开文件: ", _portFilePath, " 失败！ 错误信息： ", strerror(errno), "\n");
		RecordLog(error_info);
		return false;
	}
	char _dataLine[LINE_CHAR_MAX_NUM] = { 0 };
	int _index = 0;
	while(ReadLine(fd, _dataLine))
	{
		if(_index > _portValueNum)
		{
			RecordLog("端口配置文件中的端口条数大于预设的最大值\n");
			return true;
		}
		_portValue[_index++] = ExtractNumFromStr(_dataLine);
	}

	CloseFile(fd);
	return true;
}

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
			if(-1 != WriteFile(fd, _portInfo[i].value))
			{
				char error_info[200];
				sprintf(error_info, "%s%s%s%s%s", "写入: ", _portInfo[i].value, " 失败！ 错误信息： ", strerror(errno), "\n");
				RecordLog(error_info);
				return false;
			}
			WriteFile(fd, "\n");
		}
	}

	CloseFile(fd);

	return true;
}

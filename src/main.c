/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-30 10:48
* Last modified: 2016-11-30 10:48
* Email        : 374648064@qq.com
* Filename     : main.c
* Description  : 参数说明：argv[1]: 是要检查软件的配置文件目录
*						   argv[2]: 软件的名称
******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log/logOper.h"
#include "common/fileOper.h"
#include "common/dirOper.h"
#include "common/strOper.h"
#include "config.h"
#include "resource/network/port.h"
#include "resource/network/conflictCheck.h"

int main(int argc, char* argv[])
{
	char configfilepath[CONFIG_FILE_MAX_NUM][FILE_PATH_MAX_LENGTH];
	for(int i = 0; i < CONFIG_FILE_MAX_NUM; i++)
		memset(configfilepath[i], 0, FILE_PATH_MAX_LENGTH);

	int _ret = AutoFindConfigFile(argv[1], config_type, configfilepath);

	ConfigInfo _configInfo[100];
	int configInfo_Num = GetConfigInfoFromConfigFile(_configInfo, port_symbol, GetPort_SymbolNum(), configfilepath, _ret);
	char _portConfigPath[100];
	sprintf(_portConfigPath, "%s/%s%s", "resource/network", argv[2], ".port");  //端口文件后缀名
	GetPortInfoFromConfigFile(_configInfo, configInfo_Num, _portConfigPath);
	if(1 == CheckPort(strrchr(_portConfigPath, '/')+sizeof(char)))   //传递存放端口的文件名
	{
		printf("软件: %s 可以正确运行！\n", argv[2]);
	}

	return 0;
}

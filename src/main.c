/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-30 10:48
* Last modified: 2017-02-14 13:35
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
#include "running/monitor.h"
#include "running/resource.h"
#include "funcOper.h"

int main(int argc, char *argv[])
{
	printf("start\n");

	return 0;
}

/**对文件中的函数进行打分操作
int main(int argc, char *argv[])
{
	printf("start\n");
	FuncScore funcScore[100];
	int ret = GetFuncScore(argv[1], funcScore, 100);
	printf("ret = %d\n", ret);
	for(int i = 0; i < ret; i++)
		printf("funcName = %20s  memScore = %d  devScore = %d  netScore = %d  procScore = %d\n", funcScore[i].funcName, \
				funcScore[i].memScore, funcScore[i].devScore, funcScore[i].netScore, funcScore[i].procScore);
	
	return 0;
}
*/

/**动态监视进程的资源使用情况
int main(int argc, char* argv[])
{
	char * str = "si tr:s tr:str:  str";
	char substr[5][MAX_SUBSTR];
	int ret = cutStrByLabel(str, ':', substr, 5);
	for(int i = 0; i < ret; i++)
	{
		removeChar(substr[i], ' ');
		printf("%s\n", substr[i]);
	}

	char path[200];
	char *name = "compiz";
	int ret1 = getStatusPathByName(name, path);
	if(ret1 == 1)
		printf("apache2 Path Is: %s\n", path);
	else
		printf("ret1 = %d\n", ret1);
	sleep(1);
	while(1)
	{
		system("clear");
		printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "Name", "Pid", "PPid", "CPU(%)", "MEM(%)", "VM", "PV", "State");
		char info[8][MAX_INFOLENGTH];
		ret1 = getProgressInfo(path, info);
		if(ret == 1)
			printf("getProgressInfo ret = %d\n", ret1);
		for(int i = 0; i < 8; i++)
		{
			printf("%10s\t", info[i]);
		}
		printf("\n");
		sleep(1);
	}

	return 0;
}
*/

/*
 * 检查端口冲突的案例
int main(int argc, char *argv[])
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
*/

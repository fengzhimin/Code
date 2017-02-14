/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-07 12:27
* Last modified: 2017-02-14 13:20
* Email        : 374648064@qq.com
* Filename     : config.c
* Description  : 用于定义全局变量
******************************************************/

#include "config.h"

char config_type[][20] = {".conf", ".config", ".cnf", ".config.in", ".conf.in"};   //判断配置文件的类型,每个类型字符个数不超过20


int GetConfig_TypeNum()
{
	return sizeof(config_type)/sizeof(config_type[0]);
}

//注释符号
char note_symbol[][10] = {"#", "%", "\""};

int GetNote_SymbolNum()
{
	return sizeof(note_symbol)/sizeof(note_symbol[0]);
}

//关于操作内存的函数
char mem_func[][20] = {"malloc"};

int GetMemFunc_Num()
{
	return sizeof(mem_func)/sizeof(mem_func[0]);
}

//关于操作进程的函数
char proc_func[][20] = {"fork", "execl", "execv"};

int GetProcFunc_Num()
{
	return sizeof(proc_func)/sizeof(proc_func[0]);
}

//关于操作网络的函数
char net_func[][20] = {"socket"};

int GetNetFunc_Num()
{
	return sizeof(net_func)/sizeof(net_func[0]);
}

//关于操作设备的函数
char dev_func[][20] = {"open", "fopen"};

int GetDevFunc_Num()
{
	return sizeof(dev_func)/sizeof(dev_func[0]);
}

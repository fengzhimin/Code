/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-06 00:44
* Last modified: 2016-11-26 16:29
* Email        : 374648064@qq.com
* Filename     : config.h
* Descrip:q
* function  : 全局的宏定义
******************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>

#define OPENLOG 1    //1: 表示打开日志功能　　　0: 表示关闭日志功能
#define SHOWINFO 3    //1：表示冲突信息存在result.out文件中　　２：打印冲突信息　　３：打印并且存储冲突信息

#define CONFIG_FILE_MAX_NUM   100   //一个软件的最大配置文件个数由程序自动寻找配置文件

#define FILE_PATH_MAX_LENGTH   256    //一个文件的路径最大长度

#define LINE_CHAR_MAX_NUM      256   //一行最大字符个数

extern char config_type[][20];    //配置文件的类型

/*****************************
 * function: 获取config_type的个数
 * return: 个数
******************************/
int GetConfig_TypeNum();

extern char note_symbol[][10];    //注释符号

/*****************************
 * function: 获取note_symbol的个数
 * return:　个数
******************************/
int GetNote_SymbolNum();


#define CONFIG_KEY_MAX_NUM       50     //配置项key的最大值
#define CONFIG_VALUE_MAX_NUM     30    //配置项value的最大值

/***************************
 * function: 定义配置项结构体
***************************/
typedef struct ConfigInfo
{
	char key[CONFIG_KEY_MAX_NUM];
	char value[CONFIG_VALUE_MAX_NUM];
} ConfigInfo;

#endif


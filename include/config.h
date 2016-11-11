/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-06 00:44
* Last modified: 2016-11-09 11:36
* Email        : 374648064@qq.com
* Filename     : config.h
* Descrip:q
* function  : 全局的宏定义
******************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define OPENLOG 1    //1: 表示打开日志功能　　　0: 表示关闭日志功能

#define CONFIG_FILE_MAX_NUM   100   //一个软件的最大配置文件个数由程序自动寻找配置文件

#define FILE_PATH_MAX_LENGTH   256    //一个文件的路径最大长度

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

#endif


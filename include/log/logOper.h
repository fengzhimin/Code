/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-04 08:52
* Last modified: 2016-11-05 01:44
* Email        : 374648064@qq.com
* Filename     : logOper.h
* Description  : 日志的记录函数头文件，包含所有的日志操作
******************************************************/

#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include <stdio.h>

/**********************************
 *function: 合成需要记录的日志信息
 *return: 生成的日志信息
 *@para logInfo:　需要写入的日志信息
 *@para function: 为当前函数名称(__FUNCTION__)
 *@para file: 为当前文件名称(__FILE)
 *@para line: 为当前执行的行数(__LINE__)
**********************************/
char *CreateLogInfo(const char* logInfo, const char *file, const char *function, const int line);


/**********************************
 *function: 插入日志
 *return: ０＝成功　　-1 = 失败
 *@para logName：日志的文件名
 *@para logInfo: 日志的信息
 *@para function: 为当前函数名称(__FUNCTION__)
 *@para file: 为当前文件名称(__FILE)
 *@para line: 为当前执行的行数(__LINE__)
**********************************/
int WriteLog(const char* logName, const char* logInfo, const char *file, const char *function, const int line);

#endif


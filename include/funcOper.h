/******************************************************
* Author       : fengzhimin
* Create       : 2017-02-09 20:05
* Last modified: 2017-02-09 20:05
* Email        : 374648064@qq.com
* Filename     : funcOper.h
* Description  : 对函数进行操作的头文件
******************************************************/

#ifndef __FUNCOPER_H__
#define __FUNCOPER_H__

#include <stdio.h>
#include <stdbool.h>

/*****************************************
 * func: 判断一个字符串是否为函数的开始部分
 * return: bool   true = 是   false = 不是
 * @para str: 判断的字符串
 * example: int fun(para1, para2) 是函数的开头部分
******************************************/
bool IsStartFunc(char *str);

/*****************************************
 * func: 获取函数名
 * return: true = 提取成功   false = 提取失败
 * @para str: 被提取的字符串
 * @para funcName: 函数名
 * example: str = int func1(para) ---->  funcName = func1
******************************************/
bool GetFuncName(char *str, char *funcName);

#endif

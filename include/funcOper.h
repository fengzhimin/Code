/******************************************************
* Author       : fengzhimin
* Create       : 2017-02-09 20:05
* Last modified: 2017-02-13 16:07
* Email        : 374648064@qq.com
* Filename     : funcOper.h
* Description  : 对函数进行操作的头文件
******************************************************/

#ifndef __FUNCOPER_H__
#define __FUNCOPER_H__

#include <stdio.h>
#include <stdbool.h>
#include "config.h"

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

/*****************************************
 * func: 对一个文件中的所有函数进行打分
 * return: 返回实际文件中函数的个数  -1 = 失败
 * @para filePath: 文件的路径
 * @para funcScore: 存放获取后的FuncScore结构体数据
 * @para size: funcScore数组的大小
*****************************************/
int GetFuncScore(char *filePath, FuncScore *funcScore, int size);

#endif

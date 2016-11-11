/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-09 11:40
* Last modified: 2016-11-11 09:21
* Email        : 374648064@qq.com
* Filename     : strOper.h
* Description  : 字符串处理函数
******************************************************/

#ifndef __STROPER_H__
#define __STROPER_H__

#include <stdio.h>
#include <stdbool.h>

/**************************
 * function: 判断一个字符串是否为数字
 * return: true = 是数字　false = 不是一个数字
 * @para _ch: 要判断的字符串
**************************/
bool isNum(char *_ch);


/**************************
 * function: 判断一行是否为注释行
 * return: true = 是注释行　　false = 不是注释行
 * @para _str: 要判断的行字符串
***************************/
bool JudgeNote(char *_str);

#endif

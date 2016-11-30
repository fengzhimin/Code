/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-09 11:40
* Last modified: 2016-11-30 11:53
* Email        : 374648064@qq.com
* Filename     : strOper.h
* Description  : 字符串处理函数
******************************************************/

#ifndef __STROPER_H__
#define __STROPER_H__

#include <stdio.h>
#include <stdbool.h>
#include "config.h"

/**************************
 * function: 判断一个字符串是否为数字
 * return: true = 是数字　false = 不是一个数字
 * @para _ch: 要判断的字符串
**************************/
bool isNum(char *_ch);


/*************************
 * function: 获取字符串中第一个非空字符的下标
 * return: 返回下标值
 * @para _str: 要判断的字符串
*************************/
int GetFirstCharIndex(char *_str);

/**************************
 * function: 判断一行是否为注释行
 * return: true = 是注释行　　false = 不是注释行
 * @para _str: 要判断的行字符串
***************************/
bool JudgeNote(char *_str);


/**************************
 * function: 获取字符串中第一个单词
 * return: -1 = 提取失败　>0 = 第一个单词的下一个index
 * @para _str: 要截取的字符串
 * @para _first_word: 存储截取后的第一次单词
***************************/
int GetFirstWordFromStr(char *_str, char *_first_word);


/**************************
 * function: 判断一个字符串是否为配置项　　这里的配置项只针对 key = value 和　key  value型两种
 * return: true = 是符合要求的配置项    false = 不是符合要求的配置项
 * @para _str: 要判断的字符串
 * @para _type: 配置项类型
 * @para _type_num: 配置项类型个数
 * @para _configInfo: 存储配置项信息的指针(key, value)
***************************/
bool GetConfigInfo(char *_str, char _type[][CONFIG_KEY_MAX_NUM], int _type_num, ConfigInfo *_configInfo);


/*********************************
 * function: 获取配置文件中的配置项个数
 * return: -1 = 获取失败　　>0 = 配置项个数
 * @para _configInfo: 配置项的信息
 * @para _type: 配置项的类型
 * @para _type_num: 存储配置项类型数组的大小
 * @para _configfilepath: 配置文件数组
 * @para _configfilepathNum: 配置文件个数
**********************************/
int GetConfigInfoFromConfigFile(ConfigInfo _configInfo[], char _type[][CONFIG_KEY_MAX_NUM], int _type_num, char _configfilepath[][FILE_PATH_MAX_LENGTH], int _configfilepathNum);


/**********************************
 * function: 提取字符串中的数字(只提取正整数)
 * return: -1 = 没有数字  >=0 = 返回提取的数字
 * @para _str: 要被提取的字符串
***********************************/
int ExtractNumFromStr(char *_str);
#endif

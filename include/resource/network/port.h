/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-06 01:22
* Last modified: 2016-11-06 01:22
* Email        : 374648064@qq.com
* Filename     : port.h
* Description  : 针对网络端口的语义提取
******************************************************/

#ifndef __PORT_H__
#define __PORT_H__

#include "config.h"
#include <stdbool.h>

extern char port_symbol[][CONFIG_KEY_MAX_NUM];    //配置文件中用于标示端口的字段

/******************************
 * function: 获取port_symbol的个数
 * return: 个数
******************************/
int GetPort_SymbolNum();

/*********************************
 * function: 获取配置文件中的端口项
 * return: true = 是端口项　　false = 不是端口项
 * @para _portInfo: 端口配置信息数组
 * @para _portInfo_num: _portInfo_num的大小
 * @para portFileName: 存放端口的文件名称
**********************************/
bool GetPortInfoFromConfigFile(ConfigInfo _portInfoi[], int _portInfo_num, char *portFileName);

/********************************
 * function: 从端口的配置文件中获取端口的value
 * return: true = 获取成功　　　false = 失败
 * @para _portFilePath: 端口文件的路径
 * @para _portValue: 存放获取后的Value值
 * @para _portValueNum: _portValue数组的大小
********************************/
bool GetPortValue(char *_portFilePath, int *_portValue, int _portValueNum);

#endif

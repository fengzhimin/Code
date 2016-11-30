/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-13 13:33
* Last modified: 2016-11-13 13:33
* Email        : 374648064@qq.com
* Filename     : conflictCheck.h
* Description  : 关于网络的冲突检查
******************************************************/

#ifndef __CONFLICTCHECK_H__
#define __CONFLICTCHECK_H__

#include <stdbool.h>

/**************************************
 * function: 检查端口冲突
 * return: true = 检查成功   false = 检查失败
 * @para _portFileName: 需要检查的软件端口存放的文件名(softwareName.port)
***************************************/
bool CheckPort(char *_portFileName);


#endif

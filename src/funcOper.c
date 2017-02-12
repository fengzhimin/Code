/******************************************************
* Author       : fengzhimin
* Create       : 2017-02-09 20:06
* Last modified: 2017-02-12 23:27
* Email        : 374648064@qq.com
* Filename     : funcOper.c
* Description  : 对函数操作的源文件
******************************************************/

#include "funcOper.h"
#include "config.h"
#include "common/strOper.h"
#include <string.h>

bool IsStartFunc(char *str)
{
	removeBeginSpace(str);
	char temp[2][MAX_SUBSTR];

	int ret = cutStrByLabel(str, ' ', temp, 2);     //将str用空格分为两个子字符串
	if(ret != 2)
		return false;    //不是函数
	else
	{
		char temp1[2][MAX_SUBSTR];
		ret = cutStrByLabel(temp[1], '(', temp1, 2);  //将temp[1]用(分为两个子字符串
		if(ret != 2)
			return false;    //不是函数
		else
		{
			char temp2[2][MAX_SUBSTR];
			ret = cutStrByLabel(temp1[1], ')', temp2, 2);   //将函数的参数提取出来
			if(ret != 2)
				return false;   //不是函数
			else
			{
				char temp3[2][MAX_SUBSTR];
				ret = cutStrByLabel(temp2[0], ',', temp3, 2);   //如果是大于1个参数的时候，将第一个参数提取出来
				if(ret != 2)
				{
					//只有一个参数
					char temp4[2][MAX_SUBSTR];
					ret = cutStrByLabel(temp3[0], ' ', temp4, 2);   //判断是否为一个数据类型和形参(int argc)
					if(ret != 2)
					{
						if(strcasecmp(temp4[0], "void") != 0)    //判断是否为int func(void)类型函数
							return false;
					}
					else
					{
						char temp5[2][MAX_SUBSTR];
						ret = cutStrByLabel(temp4[1], ' ', temp5, 2);   //判断参数的数据类型是否为unsigned int或者const char等等
						if(ret == 2)
						{
							if(strcasecmp(temp4[0], "unsigned") != 0 && strcasecmp(temp4[0], "signed") != 0 \
									&& strcasecmp(temp4[0], "const") != 0)
								return false;
						}
					}
				}
				else
				{
					//对第一个参数进行分析
					char temp4[2][MAX_SUBSTR];
					ret = cutStrByLabel(temp3[0], ' ', temp4, 2);   //判断是否为一个数据类型和形参(int argc)
					if(ret != 2)
							return false;
					else
					{
						char temp5[2][MAX_SUBSTR];
						ret = cutStrByLabel(temp4[1], ' ', temp5, 2);   //判断参数的数据类型是否为unsigned int等等
						if(ret == 2)
						{
							if(strcasecmp(temp4[0], "unsigned") != 0 && strcasecmp(temp4[0], "signed") != 0 \
									&& strcasecmp(temp4[0], "const") != 0)
								return false;
						}
					}
				}
			}
		}
	}

	return true;
}

bool GetFuncName(char *str, char *funcName)
{
	char temp[2][MAX_SUBSTR];
	char temp_funcName[MAX_FUNCNAME];
	memset(temp_funcName, 0, MAX_FUNCNAME);

	int ret = cutStrByLabel(str, ' ', temp, 2);   //将返回返回值和函数名分开
	if(ret != 2)
		return false;   //提取失败
	else
	{
		char temp1[2][MAX_SUBSTR];
		ret = cutStrByLabel(temp[1], '(', temp1, 2);  //将函数名和参数分开
		if(ret != 2)
			return false;
		else
		{
			char temp2[2][MAX_SUBSTR];
			ret = cutStrByLabel(temp1[0], ' ', temp2, 2);   //处理unsigned int func1()类型的函数
			if(ret != 2)
				strcpy(temp_funcName, temp1[0]);
			else
			{
				char temp3[2][MAX_SUBSTR];
				ret = cutStrByLabel(temp2[1], ' ', temp3, 2);   //处理const unsigned char func()类型的函数
				if(ret != 2)
					strcpy(temp_funcName, temp2[1]);
				else
					strcpy(temp_funcName, temp3[1]);
			}

			//处理函数返回值为指针类型
			if(temp_funcName[0] == '*')
				strcpy(funcName, &temp_funcName[1]);
			else
				strcpy(funcName, temp_funcName);

			return true;
		}
	}
}

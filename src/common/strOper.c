/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-11 09:02
* Last modified: 2016-11-12 15:57
* Email        : 374648064@qq.com
* Filename     : strOper.c
* Description  : 
******************************************************/

#define _GNU_SOURCE   //避免编译strcasestr时出现警告

#include "common/strOper.h"
#include "common/fileOper.h"
#include "log/logOper.h"
#include <string.h>
#include <errno.h>

bool isNum(char *_ch)
{
	int _length = strlen(_ch);
	for(int i = 0; i < _length; i++)
	{
		if(_ch[i] < '0' || _ch[i] > '9')
			return false;
	}

	return true;
}

int GetFirstCharIndex(char *_str)
{
	int _first_char_index = 0;
	int _str_length = strlen(_str);
	for(int i = 0; i < _str_length; i++)
		if(_str[i] == ' ' || _str[i] == '\t')    //空白字符和制表符
			_first_char_index++;
		else
			break;

	return _first_char_index;
}

bool JudgeNote(char *_str)
{
	int _first_char_index = GetFirstCharIndex(_str);

	int _note_num = GetNote_SymbolNum();
	for(int i = 0; i < _note_num; i++)
	{
		int note_size = strlen(note_symbol[i]);
		char temp[20];
		memset(temp, 0, 20);
		strncpy(temp, &(_str[_first_char_index]), note_size);
		if(strcasecmp(temp, note_symbol[i]) == 0)
			return true;
	}

	return false;
}

int GetFirstWordFromStr(char *_str, char *_first_word)
{
	int _str_length = strlen(_str);
	int _first_char_begin_index = GetFirstCharIndex(_str);
	int _first_char_end_index;
	for(_first_char_end_index = _first_char_begin_index; _first_char_end_index < _str_length; _first_char_end_index++)
	{
		if(_str[_first_char_end_index] == ' ' || _str[_first_char_end_index] == '\t' \
				|| _str[_first_char_end_index] == '=' || _str[_first_char_end_index] == '\n')
			break;
	}

	int word_size = _first_char_end_index - _first_char_begin_index;
	if(word_size == 0)
		return -1;

	if(word_size > CONFIG_KEY_MAX_NUM)
	{
		RecordLog("配置文件中第一行的首个单词的长度大于配置项key的最大长度!\n");
		return -1;
	}
	strncpy(_first_word, &_str[_first_char_begin_index], word_size);

	return _first_char_end_index;
}

bool GetConfigInfo(char *_str, char _type[][CONFIG_KEY_MAX_NUM], int _type_num, ConfigInfo *_configInfo)
{
	char _first_word[CONFIG_KEY_MAX_NUM];
	memset(_first_word, 0, CONFIG_KEY_MAX_NUM);
	int _next_char_begin_index = GetFirstWordFromStr(_str, _first_word);
	int _str_length = strlen(_str);
	if(_next_char_begin_index == -1)
		return false;
	for(int i = 0; i < _type_num; i++)
	{
		if(strcasestr(_first_word, _type[i]) != NULL)
		{
			int _temp_index = 0;
			bool temp_point = false;
			strcpy(_configInfo->key, _first_word);
			for(int j = _next_char_begin_index; j < _str_length; j++)
			{
				if(_str[j] == ' ' || _str[j] == '\t' || _str[j] == '=' || _str[j] == '\n')
				{
					if(temp_point)
						return true;
					else
						continue;
				}
				else
				{
					_configInfo->value[_temp_index++] = _str[j];
					temp_point = true;
				}
			}
			return true;
		}
	}

	return false;
}

int GetConfigInfoFromConfigFile(ConfigInfo _configInfo[], int _configInfo_num, char _type[][CONFIG_KEY_MAX_NUM], int _type_num, char _configfilepath[][FILE_PATH_MAX_LENGTH], int _configfilepathNum)
{
	int _real_configInfoNum = 0;
	for(int i = 0; i < _configfilepathNum; i++)
	{
		FILE *fd = OpenFile(_configfilepath[i], "r");	
		if(fd == NULL)
		{
			char error_info[200];
			sprintf(error_info, "%s%s%s%s%s", "文件: ", _configfilepath[i], " 打开失败！ 错误信息： ", strerror(errno), "\n");
			RecordLog(error_info);
			return -1;
		}
		char lineInfo[LINE_CHAR_MAX_NUM];
		while(!feof(fd))
		{
			memset(lineInfo, 0, LINE_CHAR_MAX_NUM);
			ReadLine(fd, lineInfo);
			if(!JudgeNote(lineInfo))
			{
				if(GetConfigInfo(lineInfo, _type, _type_num, &_configInfo[_real_configInfoNum]))
					_real_configInfoNum++;
			}
		}

		CloseFile(fd);
	}

	return _real_configInfoNum;
}


int ExtractNumFromStr(char *_str)
{
	int _str_length = strlen(_str);
	int _ret = 0;
	for(int i = 0; i < _str_length; i++)
		if(_str[i] >= '0' && _str[i] <= '9')
			_ret = _ret*10 + _str[i] - '0';

	if(_ret > 0)
		return _ret;
	else
		return -1;
}

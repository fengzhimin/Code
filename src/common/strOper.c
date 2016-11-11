/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-11 09:02
* Last modified: 2016-11-12 00:58
* Email        : 374648064@qq.com
* Filename     : strOper.c
* Description  : 
******************************************************/

#include "common/strOper.h"
#include "config.h"
#include <string.h>

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

bool JudgeNote(char *_str)
{
	int _first_char_index = 0;
	for(int i = 0; i < strlen(_str); i++)
		if(_str[i] == ' ')
			_first_char_index++;     //剔除一行开头的空格
		else
			break;

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

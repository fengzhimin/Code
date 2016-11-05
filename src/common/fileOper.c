/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-04 12:35
* Last modified: 2016-11-05 16:13
* Email        : 374648064@qq.com
* Filename     : fileOper.c
* Description  : 
******************************************************/

#include "common/fileOper.h"
#include <errno.h>

FILE *OpenFile(const char* fileName, const char* mode)
{
	FILE *fd;
	fd = fopen(fileName, mode);

	return fd;
}

int WriteFile(FILE *fd, char *data)
{
	int _ret_value;
	size_t _data_size;
	_data_size = strlen(data);
	_ret_value = fwrite(data, _data_size, 1, fd);
	if(_ret_value != 1)
		return errno;
	else
		return -1;
}

int ReadFile(FILE *fd, char *data, size_t size)
{
	int _ret_value;
	_ret_value = fread(data, 1, size, fd);
	printf("%d\n", _ret_value);
	if(_ret_value < 1)
		return errno;
	else
		return -1;
}

int ReadLine(FILE *fd, char *data)
{
	char _ch;
	int n = 0;
	while((_ch = getc(fd)) != EOF)
	{
		if(_ch == '\n')
			return -1;
		data[n++] = _ch;
	}

	return errno;
}

int CloseFile(FILE *fd)
{
	return fclose(fd);
}

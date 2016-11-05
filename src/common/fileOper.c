/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-04 12:35
* Last modified: 2016-11-04 13:08
* Email        : 374648064@qq.com
* Filename     : fileOper.c
* Description  : 
******************************************************/

#include "common/fileOper.h"

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
		return -1;
	else
		return 1;
}

int ReadFile(FILE *fd, char *data, size_t size)
{
	if(feof(fd))
		return 0;
	else
	{
		int _ret_value;
		_ret_value = fread(data, size, 1, fd);
		if(_ret_value != 1)
			return -1;
		else
			return 1;
	}
}

int CloseFile(FILE *fd)
{
	return fclose(fd);
}

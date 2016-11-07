#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log/logOper.h"
#include "common/fileOper.h"
#include "common/dirOper.h"
#include "config.h"

bool isNum(char *_ch)
{
    int _length = strlen(_ch);
    printf("%d\n", _length);
    for(int i = 0; i < _length - 1; i++)
    {
        if(_ch[i] < '0' || _ch[i] > '9')
            return false;
    }

    return true;
}


int main(int argc, char* argv[])
{
	/*
    FILE *_fd = NULL;
    if(argc != 2)
    {
        printf("请输入一个文件名作为参数！\n");
        return 0;
    }
    
    if((_fd = fopen(argv[1], "r")) == NULL)
    {
        printf("打开文件<%s>错误!\n", argv[1]);

        return 0;
    }

    char _string[100];
    int _line = 1;
    while(fgets(_string, 100, _fd) != NULL)
    {
        printf("第<%d>的内容为：%s", _line, _string);
        if(isNum(_string))
            printf("是数字");
        else
            printf("不是数字");

        printf("\n");
        _line++;
    }

    fclose(_fd);
	*/

	WriteLog("logInfo.log", "test\n", __FILE__, __FUNCTION__, __LINE__);
	/*
	FILE* _fd = OpenFile("log.log", "r");
	if(NULL == _fd)
		perror("打开文件失败!");
	char strline[100];
	int _ret  = ReadFile(_fd, strline, 100);
	if(-1 != _ret)
		printf("Errno: %s\n", strerror(_ret));
	else
		printf("%s\n", strline);

    return 0;
	*/
	char configfilepath[CONFIG_FILE_MAX_NUM][FILE_PATH_MAX_LENGTH];
	for(int i = 0; i < CONFIG_FILE_MAX_NUM; i++)
		memset(configfilepath[i], 0, FILE_PATH_MAX_LENGTH);

	int _ret = AutoFindConfigFile("/home/fzm/Code", config_type, configfilepath);
	for(int i = 0; i < CONFIG_FILE_MAX_NUM; i++)
		printf("%s\n", configfilepath[i]);
	//printf("%d\n", GetConfig_TypeNum());
}

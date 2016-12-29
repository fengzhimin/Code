/******************************************************
* Author       : fengzhimin
* Create       : 2016-12-19 11:03
* Last modified: 2016-12-19 11:03
* Email        : 374648064@qq.com
* Filename     : monitor.c
* Description  : 
******************************************************/

#include "running/monitor.h"
#include "common/dirOper.h"
#include "log/logOper.h"
#include "config.h"

int init_monitor()
{
	return inotify_init();
}

int add_monitor(int fd, char *path, uint32_t mask)
{
	char temp_path[FILE_PATH_MAX_LENGTH];
	memset(temp_path, 0, FILE_PATH_MAX_LENGTH);
	strcpy(temp_path, path);   //拷贝path
	int _size = strlen(temp_path);
	while(temp_path[_size - 1] == '/')  //删除结尾的斜杠
	{
		temp_path[_size - 1] = '\0';
		_size--;
	}
	int _type = Is_Dir(temp_path);
	//处理普通文件
	if(_type == -2)
	{
		return inotify_add_watch(fd, temp_path, mask);
	}
	//处理文件夹
	else if(_type == -1)
	{
		DIR *pdir = NULL;
		struct dirent *pdirent;
		pdir = opendir(temp_path);
		if(pdir == NULL)
		{
			char error_info[200];
			sprintf(error_info, "%s%s%s%s%s", "打开文件夹：", temp_path, "失败！ 错误信息： ", strerror(errno), "\n");
			RecordLog(error_info);
			return -1;
		}
		while((pdirent = readdir(pdir)) != NULL)
		{
			if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
				continue;
			char temp[FILE_PATH_MAX_LENGTH];
			memset(temp, 0, FILE_PATH_MAX_LENGTH);
			sprintf(temp, "%s/%s", temp_path, pdirent->d_name);
			int _temp_type = Is_Dir(temp);
			if(_temp_type == -1)
				add_monitor(fd, temp, mask);
			else if(_temp_type >= 0)
			{
				char error_info[200];
				sprintf(error_info, "%s%s%s%s%s", "打开文件夹：", temp, "失败！ 错误信息： ", strerror(errno), "\n");
				RecordLog(error_info);
				closedir(pdir);
				return -1;
			}
		}

		closedir(pdir);

		return inotify_add_watch(fd, temp_path, mask);
	}
	else
		return -1;
}

int remove_monitor(int fd, int wd)
{
	return inotify_rm_watch(fd, wd);
}

int readMonitor(int fd, char *path, uint32_t mask)
{
	char buf[BUFSIZ] = {0};
	int _ret = read(fd, buf, sizeof(buf)-1);
	if(_ret > 0)
	{
		struct inotify_event *pevent = (struct inotify_event *)&buf[0];
		printf("pevent->mask=%d\tmask=%d\n", pevent->mask, mask);
		printf("filename=%s\n", pevent->name);
		if(pevent->mask & mask)
		{
			strcpy(path, pevent->name);
			return 1;
		}
		else
			return 0;
	}
	else if(_ret == 0)
		return 0;
	else
		return -1;
}


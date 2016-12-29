/******************************************************
* Author       : fengzhimin
* Create       : 2016-12-19 11:04
* Last modified: 2016-12-19 11:04
* Email        : 374648064@qq.com
* Filename     : monitor.h
* Description  : 
******************************************************/

#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE (sizeof(struct inotify_event) + FILE_PATH_MAX_LENGTH)

/******************************
 * func: 定义add_monitor函数别名
******************************/
#define add_monitor_allEvent(fd, path)   add_monitor(fd, path, IN_ALL_EVENTS)

/**********************************************
 * func: 初始化文件监听
 * return：-1 = error 并且设置errno   fd = 成功
**********************************************/
int init_monitor();

/**********************************************
 * func: 添加一个路径(包括子路径)到监听队列中
 * return：-1 = error 并且设置errno   wd = 成功(对于path为单个文件来说返回文件的wd，如果path为文件夹则返回文件夹的wd)
 * @para fd：监听事件的fd
 * @para path：需要监听的路径(可以是文件也可以是文件夹)
 * @para mask：监听掩码
**********************************************/
int add_monitor(int fd, char *path, uint32_t mask);

/**********************************************
 * func: 从监听队列中删除一个监听
 * return：-1 = error 并且设置errno   0 = 成功
 * @para fd：监听事件的fd
 * @para wd：监听事件的wd
**********************************************/
int remove_monitor(int fd, int wd);

/**********************************************
 * func: 读取监听到的文件变化信息
 * return: -1 = error   0 = 无文件发生变化   1 = 成功
 * @para fd: 监听事件的fd
 * @para path: 存储监听文件的路径
 * @para mask: 监听mask属性是否发生
 *			   IN_ACCESS = File was accessed
 *			   IN_MODIFY = File was modified
 *			   IN_ATTRIB = Metadata changed
 *			   IN_CLOSE_WRITE = Writtable file was closed
 *			   IN_CLOSE_NOWRITE = Unwrittable file closed
 *			   IN_CLOSE = Close
 *			   IN_OPEN = File was opened
 *			   IN_MOVED_FROM = File was moved from X
 *			   IN_MOVED_TO = File was moved to Y
 *			   IN_MOVE = Moves
 *			   IN_CREATE = Subfile was create
 *			   IN_DELETE = Subfile was deleted
 *			   IN_DELETE_SELF = Self was deleted
 *			   IN_MOVE_SELF = Self was moved
***********************************************/
int readMonitor(int fd, char *path, uint32_t mask);

#endif

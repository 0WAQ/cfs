/**
 * 
 * 任务相关头文件
 * 
 */
#ifndef TASK_H
#define TASK_H

#include "task_t.h"

/**
 * @brief 初始化一个任务
 */
void task_init(struct task_struct* task, struct cfs_rq* rq, char* name, uint32_t pid, int prio);

#endif // TASK_H
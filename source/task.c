/**
 * 
 * 任务相关c文件
 * 
 */

#include "task.h"

void task_init(struct task_struct* task, uint32_t pid) {
    task->pid = pid;
    task->se.on_rq = 0;
    task->se.vruntime = 0;
    task->state = OTHER;
}
/**
 * 
 * 任务相关c文件
 * 
 */

#include <string.h>
#include "task.h"
#include "cfs.h"

extern int sched_nice_to_weight[40];

void task_init(struct task_struct* task, struct cfs_rq* rq, char* name, uint32_t pid, int prio) {
    struct sched_entity* se = &task->se;
    task->pid = pid;
    memcpy(task->name, name, strlen(name));
    task->state = OTHER;
    task->prio = prio;

    se->on_rq = 0;
    se->load.weight = sched_nice_to_weight[prio + 20];  // 根据优先级设置权重
    
     // TODO: 实际不应该这样, 因为若有很多任务不断加入, 那么其余任务会被一直抢占
    se->vruntime = rq->min_vruntime;
}
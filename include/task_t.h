/**
 * 
 * 任务相关基本类型
 * 
 */
#ifndef TASK_T_H
#define TASK_T_H

#include "common/types.h"
#include "tools/rbtree_t.h"
#include "cfs_t.h"

#define TASK_NAME_SIZE          (64)

typedef enum {
    RUNNING = 0,
    OTHER = 1,
}task_state;

struct task_struct {    
    
    uint32_t pid;               // 进程ID

    char name[TASK_NAME_SIZE];  // 任务名

    uint32_t state;             // 任务的状态
    int prio;                   // 任务优先级, 从 -20 ~ 19, 用以索引sched_nice_to_weight表

    // cfs调度相关
    struct sched_entity se;     // 挂载至调度队列上

};

#endif // TASK_T_H

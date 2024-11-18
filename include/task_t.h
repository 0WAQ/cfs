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

typedef enum {
    RUNNING = 0,
    OTHER = 1,
}task_state;

struct task_struct {    
    
    uint32_t pid;
    uint32_t state;

    // cfs调度相关
    struct sched_entity se;

};

#endif // TASK_T_H

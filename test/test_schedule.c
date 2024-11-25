#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "task.h"
#include "cfs.h"
#include "common/macros.h"

#define TASK_NR 10
#define EXEC    100

// 方便调试查看信息
struct pii {
    uint32_t weight;
    uint32_t* vruntime;
};

struct cfs_rq rq;
struct pii debug[TASK_NR];

void schedule();

int main() {
    cfs_init(&rq);

    struct task_struct task_table[TASK_NR];
    for(int i = 0; i < TASK_NR; i++) {
        char name = i + '0';
        task_init(task_table + i, &rq, &name, i, i);
        enqueue_task(&rq, task_table + i);
    }
    
    for(int i = 0; i < TASK_NR; i++) {
        debug[i].weight = task_table[i].se.load.weight;
        debug[i].vruntime = &task_table[i].se.vruntime;
    }

    // 开始模拟
    schedule();
}

void schedule() {

    // 开始模拟
    struct task_struct* now;
    while(1)
    {
        now = dequeue_task(&rq);
        uint32_t delta_exec = EXEC;  // 模拟执行了100个时间单位
        update_vruntime(&now->se, delta_exec);
        enqueue_task(&rq, now);
    }
}
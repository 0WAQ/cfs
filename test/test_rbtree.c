#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "cfs.h"
#include "task.h"
#include "tools/rbtree.h"

#define TASK_NR         (10000)

static struct cfs_rq rq;
static struct task_struct task_table[TASK_NR];
static unsigned int seed;
static int no_warn = 1, is_ok = 1;

void rbt_test()
{
    cfs_init(&rq);

    seed = time(NULL);
    srand(seed);

    struct task_struct* task = NULL;

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        task_init(task, &rq, "0", i, 0);
        task->se.vruntime = rand()%1000 + 1;
    }

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        no_warn = check(&rq.rb_root, i);
        if(!no_warn) {
            is_ok = 0;
        }
        enqueue_task(&rq, task);
    }

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        no_warn = check(&rq.rb_root, TASK_NR - i);
        if(!no_warn) {
            is_ok = 0;
        }
        dequeue_task(&rq);
    }

    if(is_ok) {
        printf("test_rbtree complete! no warn.\n");
    }
}

int main(int argc, char* argv[])
{
    // 测试红黑树功能
    rbt_test();
    return 0;
}

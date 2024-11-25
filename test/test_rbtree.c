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

void rbt_test()
{
    cfs_init(&rq);

    seed = time(NULL);
    srand(seed);

    struct task_struct* task = NULL;

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        task_init(task, i);
        task->se.vruntime = rand()%1000 + 1;
    }

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        check(&rq.rb_root, i);
        enquque_task(&rq, &task->se);
    }

    for(int i = 0; i < TASK_NR; i++) {
        task = task_table + i;
        check(&rq.rb_root, TASK_NR - i);
        dequque_task(&rq, &task->se);
    }
}

int main(int argc, char* argv[])
{
    // 测试红黑树功能
    rbt_test(); // TODO: 待删除
    return 0;
}

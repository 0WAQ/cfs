/**
 * 
 * cfs实现c文件
 * 
 */

#include "cfs.h"
#include "task.h"
#include "tools/rbtree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 权重表
 */
const int NICE_OFFSET = 40;
const int NICE_0_LOAD = 1024;       // 优先级为0的任务的权重

// 每个权重的比值大约为1.25, 优先级为0的进程权重为1024
const int sched_nice_to_weight[40] = {
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
};

void cfs_init(struct cfs_rq* rq) {
    rq->rb_root = RB_ROOT;
    rq->rb_leftmost = NULL;
    rq->min_vruntime = 0;
    rq->nr = 0;

    rq->total_weight = 0;
}

uint32_t calc_delta_fair(uint32_t delta_exec, uint32_t load_weight) {
    /**
     * 举个例子, 若任务A的权重为2048, 即2倍与标准任务(1024)
     *          并且该任务的执行时间(delta_exec)为100
     *          
     * 那么 delta_vruntime = 100 * 2048 / 1024 = 200
     */
    return delta_exec * load_weight / NICE_0_LOAD;
}

void enqueue_task(struct cfs_rq* rq, struct task_struct* p) {

    struct sched_entity* se = &p->se;
    struct rb_node** link = &rq->rb_root.rb_node;
    struct rb_node*  parent = NULL;
    struct sched_entity* entry = NULL;
    int leftmost = 1;   // 标记当前se是否在最左端

    uint32_t key = se->vruntime;
    while(*link) {
        parent = *link;
        entry = rb_entry(parent, struct sched_entity, cfs_node);

        // 若key小于当前节点的vruntime, 那么向左插, 否则向右插
        if(key < entry->vruntime) {
            link = &parent->rb_left;    // 让link表示左孩子
        }
        else {
            link = &parent->rb_right;   // 让link表示右孩子
            leftmost = 0;   // 向右拐, 说明不是最左端
        }
    }

    if(leftmost) {
        rq->rb_leftmost = &se->cfs_node;
    }

    // 插入节点
    rb_link_node(&se->cfs_node, parent, link);

    // 平衡树
    rb_insert_color(&se->cfs_node, &rq->rb_root);

    rq->nr++;
    se->on_rq = 1;
    p->state = RUNNING;
}

struct task_struct* dequeue_task(struct cfs_rq* rq) {
    if(rq->nr == 0) {
        return NULL;
    }

    // 获取最左节点
    struct rb_node* node = rq->rb_leftmost;
    struct sched_entity* se = container_of(node, struct sched_entity, cfs_node);
    struct task_struct* p = container_of(se, struct task_struct, se);

    // 若树中还有节点, 那么新的最左节点是node的下一个
    if(rq->nr > 1) {
        rq->rb_leftmost = rb_next(node);
    }

    // 删除最左节点
    rb_erase(node, &rq->rb_root);

    rq->nr--;
    se->on_rq = 0;
    p->state = OTHER;

    return p;
}

void task_dispatch(struct cfs_rq* rq) {

}

void update_vruntime(struct sched_entity* se, uint32_t delta_exec) {

    // 计算vruntime的变化
    uint32_t delta_vruntime = calc_delta_fair(delta_exec, se->load.weight);

    // 更新vruntime
    se->vruntime += delta_vruntime;
}

void update_load_set(struct load_weight* lw, unsigned long w) {
    lw->weight = w;
    lw->inv_weight = 0;
}

void update_load_add(struct load_weight* lw, unsigned long inc) {
    lw->weight += inc;
    lw->inv_weight = 0;
}

void update_load_sub(struct load_weight* lw, unsigned long inc) {
    lw->weight -= inc;
    lw->inv_weight = 0;
}

void check(struct rb_root* rb_root, uint32_t nr_nodes) {
    
    int cnt = 0, blacks = 0;
    
    struct rb_node* node; uint32_t prev_key = 0;
    for(node = rb_first(rb_root); node != NULL; node = rb_next(node)) {
        struct sched_entity* se = rb_entry(node, struct sched_entity, cfs_node);

        if(se->vruntime < prev_key) {
            printf("[WARN] key(%d) < prev_key(%d).\n", se->vruntime, prev_key);
        }

        if(rb_is_red(node) && (!rb_parent(node) || rb_is_red(rb_parent(node)))) {
            printf("[WARN] two red ndoes.\n");
        }

        if(cnt == 0) {
            blacks = black_path_count(node);
        }
        else if((!node->rb_left || !node->rb_right) && (blacks != black_path_count(node))) {
            printf("[WARN] black count wrongs.\n");
        }

        prev_key = se->vruntime;
        cnt++;
    }
}

int black_path_count(struct rb_node* node) {
    int blacks;
    for(blacks = 0; node; node = rb_parent(node)) {
        blacks += !rb_is_red(node);
    }
    return blacks;
}
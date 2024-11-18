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

void cfs_init(struct cfs_rq* rq) {
    rq->rb_root = RB_ROOT;
    rq->rb_leftmost = NULL;
    rq->min_vruntime = 0;
    rq->nr = 0;
}

// TODO:
void enquque_task(struct cfs_rq* rq, struct sched_entity* se) {

    // 
    se->vruntime += rq->min_vruntime;

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

    // 更新vruntime
    update_load_add();

    rq->nr++;
    se->on_rq = 1;

    container_of(se, struct task_struct, se)->state = RUNNING;
}

void dequque_task(struct cfs_rq* rq, struct sched_entity* se) {
    if(rq->rb_leftmost == &se->cfs_node) {
        rq->rb_leftmost = rb_next(&se->cfs_node);
    }

    rb_erase(&se->cfs_node, &rq->rb_root);
    update_load_sub();

    rq->nr--;
    se->on_rq = 0;

    container_of(se, struct task_struct, se)->state = OTHER;
}

void update_load_add() {
    // TODO:
}

void update_load_sub() {
    // TODO:
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
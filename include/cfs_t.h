/**
 * 
 * cfs基本类型
 * 
 */
#ifndef CFS_T_H
#define CFS_T_H

#include "common/types.h"
#include "tools/rbtree_t.h"

/**
 * @brief cfs运行队列
 */
struct cfs_rq {
    struct rb_root rb_root;      // 每个运行队列上有一棵红黑树
    struct rb_node* rb_leftmost;   // 指向树中最左边的节点
    uint32_t min_vruntime;       // 所有任务的vruntime中的最小值
    uint32_t nr;                 // 树中元素的个数
};

/**
 * @brief 调度实体, 包含cfs所需调度信息
 */
struct sched_entity {
    
    // TODO: load

    uint32_t vruntime;          // 任务运行的vruntime, 也是红黑树的key

    // 调度实体在cfs队列中的节点
    struct rb_node cfs_node;

    // 是否在cfs队列上
    int on_rq;
};

#endif // CFS_T_H
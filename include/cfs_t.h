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
 * @brief 权重相关信息
 */
struct load_weight {
    uint32_t weight;                    // 任务的权重
    uint32_t inv_weight;                // 权重的倒数, 用以优化相关计算. 该项目不使用
};

/**
 * @brief cfs运行队列
 */
struct cfs_rq {
    struct rb_root rb_root;             // 每个运行队列上有一棵红黑树
    struct rb_node* rb_leftmost;        // 指向树中最左边的节点, 因为在cfs中要频繁获取vruntime最小的任务
    uint32_t min_vruntime;              // 所有任务的vruntime中的最小值
    uint32_t nr;                        // 树中元素的个数

    int total_weight;                   // 所有进程权重之和
};

/**
 * @brief 调度实体, 包含cfs所需调度信息
 */
struct sched_entity {
    
    struct load_weight load;            // 权重相关信息

    uint32_t vruntime;                  // 任务运行的vruntime, 也是红黑树的key

    struct rb_node cfs_node;            // 调度实体在cfs队列中的节点

    int on_rq;                          // 是否在cfs队列上
};

#endif // CFS_T_H
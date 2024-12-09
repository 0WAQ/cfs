/**
 * 
 * cfs相关操作
 * 
 */
#ifndef CFS_H
#define CFS_H

#include "cfs_t.h"
#include "task_t.h"

/**
 * @brief 初始化cfs队列
 */
void cfs_init(struct cfs_rq* rq);

/**
 * @brief 将调度实体插入红黑树
 */
void enqueue_task(struct cfs_rq* rq, struct task_struct* p);

/**
 * @brief 将调度实体从红黑树中删除
 */
struct task_struct* dequeue_task(struct cfs_rq* rq);

/**
 * @brief 开始调度
 */
void task_dispatch(struct cfs_rq* rq);

/**
 * @brief 更新vruntime
 */
void update_vruntime(struct sched_entity* se, uint32_t delta_exec);

/**
 * @brief 设置load
 */
void update_load_set(struct load_weight* lw, unsigned long w);

/**
 * @brief 增加load
 */
void update_load_add(struct load_weight* lw, unsigned long inc);

/**
 * @brief 减少load
 */
void update_load_sub(struct load_weight* lw, unsigned long dec);

/**
 * @brief 检查红黑树是否合法
 */
int check(struct rb_root* rb_root, uint32_t nr_nodes);

/**
 * @brief node向上有多少个黑色节点
 */
int black_path_count(struct rb_node* node);

/**
 * @brief 根据任务的实际执行时间和权重, 更新其vruntime
 * @param delta_exec 任务的实际执行时间
 * @param load_weight 任务的权重
 */
uint32_t calc_delta_fair(uint32_t delta_exec, uint32_t load_weight);

#endif // CFS_H

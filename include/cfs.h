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
 * @brief 将任务加入cfs_rq
 */
void enquque_task(struct cfs_rq* rq, struct sched_entity* se);

/**
 * @brief 将任务从cfs_rq移除
 */
void dequque_task(struct cfs_rq* rq, struct sched_entity* se);

/**
 * @brief 根据权重与实际运行时间更新vruntime
 */
void update_load_add();

/**
 * @brief
 */
void update_load_sub();

/**
 * @brief 检查红黑树是否合法
 */
void check(struct rb_root* rb_root, uint32_t nr_nodes);

/**
 * @brief node向上有多少个黑色节点
 */
int black_path_count(struct rb_node* node);

#endif // CFS_H

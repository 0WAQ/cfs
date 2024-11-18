/**
 * 
 * rbtree头文件
 * 
 */
#ifndef RBTREE_H
#define RBTREE_H

#include "common/macros.h"
#include "rbtree_t.h"

/**
 * @brief 初始化新节点
 */
static inline void rb_link_node(struct rb_node* node, struct rb_node* parent, struct rb_node** rb_link)
{
    // 新节点的颜色需为红色, 否则在插入时会破坏性质4
    // 若新节点的父节点也是红色, 就会破坏性质2, 此时会进行调整, 使树平衡
    node->rb_color = RB_RED;

    node->rb_parent = parent;
    node->rb_left = node->rb_right = NULL;

    // 调整parent的子节点为node, rb_link在插入时决定是左还是右
    *rb_link = node;
}

/**
 * @brief 左旋
 */
void __rb_rotate_left(struct rb_node* node, struct rb_root* root);

/**
 * @brief 右旋
 */
void __rb_rotate_right(struct rb_node* node, struct rb_root* root);

/**
 * @brief 插入
 */
void rb_insert_color(struct rb_node* node, struct rb_root* root);

/**
 * @brief 删除
 */
void rb_erase(struct rb_node* node, struct rb_root* root);

/**
 * @brief 删除的底层实现
 */
void __rb_erase_color(struct rb_node* node, struct rb_node* parent, struct rb_root* root);


struct rb_node* rb_next(struct rb_node* node);
struct rb_node* rb_prev(struct rb_node* node);
struct rb_node* rb_first(struct rb_root* root);

#define rb_entry(member_val, container_type, member_name) \
    entry_of(member_val, container_type, member_name)

#endif // RBTREE_H
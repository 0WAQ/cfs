/**
 * 
 * rbtree基本类型
 * 
 */
#ifndef RBTREE_T_H
#define RBTREE_T_H

#include "common/types.h"

/***
 * 
 * @brief 红黑树的性质
 * 
 * 1. 每个节点都会有颜色, 要么是红色, 要么是黑色 
 * 2. 若一个节点为红色, 则它的两个子节点为黑色 (一条路径上, 不能出现相邻的红色节点)
 * 3. 树中的空节点被视为黑色
 * 4. 对于每个节点, 所有向下的路径上包含相同数量的黑色节点
 * 5. 根节点是黑色的()
 * 
 */

// 节点颜色 
#define RB_RED          0
#define RB_BLACK        1

/**
 * @brief rbtree节点, 通过container_of取节点元素
 */
struct rb_node {
    struct rb_node* rb_parent;
    int rb_color;
    struct rb_node* rb_right;
    struct rb_node* rb_left;
};

/**
 * @brief 红黑树根节点
 */
struct rb_root {
    struct rb_node* rb_node;
};


#define RB_ROOT             ((struct rb_root){NULL, })
#define rb_parent(r)        ((struct rb_node*)((r)->rb_parent))
#define rb_color(r)         ((r)->rb_color)
#define rb_is_red(r)        (!rb_color(r))
#define rb_is_black(r)      (rb_color(r))
#define rb_set_red(r)       do { (r)->rb_color = RB_RED; } while(0)
#define rb_set_black(r)     do { (r)->rb_color = RB_BLACK;  } while(0)


#endif // RBTREE_T_H
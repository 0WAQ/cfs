/**
 * 
 * rbtree实现
 * 
 */

#include "tools/rbtree.h"

void __rb_rotate_left(struct rb_node* node, struct rb_root* root)
{   
    /***
	 * 
     *      A  <- node                                  C  <- right
     *     / \                                         / \
     *    B   C  <- right    =============>   node->  A   E
     *       / \                                	 / \ 
     *      D   E                           		B   D
     * 
	 */

    // 这棵子树的新根是node->rb_right
    struct rb_node* right = node->rb_right;

	// right的左孩子(D)要变为node(A)的右孩子
    node->rb_right = right->rb_left;
    if(node->rb_right != NULL)	// 如果该结点(D)不空的话, 还要调整其父节点
        right->rb_left->rb_parent = node;
	
	// right新的左孩子应调整为node(A)
    right->rb_left = node;

	// 调整新根的父节点
	right->rb_parent = node->rb_parent;
    
    // right的父节点为空, 说明right是整颗树的根
	if(right->rb_parent == NULL)
    {
		root->rb_node = right;	// 调整root指针
    }
	else	// right不是整棵树的根
    {
		// 调整原根父节点的指针

		// 若node是其原父节点的左孩子, right也是左孩子
        if(node == node->rb_parent->rb_left)
            node->rb_parent->rb_left = right;
        else // 否则right就是右孩子
            node->rb_parent->rb_right = right;
    }

	// 调整原根的父节点
    node->rb_parent = right;
}

void __rb_rotate_right(struct rb_node* node, struct rb_root* root)
{

	/**
	 * 
	 * 与左旋相反
	 * 
	 */

	struct rb_node *left = node->rb_left;

	node->rb_left = left->rb_right;
	if (node->rb_left != NULL)
		left->rb_right->rb_parent = node;
	left->rb_right = node;

	left->rb_parent = node->rb_parent;
	if (left->rb_parent == NULL)
	{
		root->rb_node = left;
	}
	else
    {
		if (node == node->rb_parent->rb_right)
			node->rb_parent->rb_right = left;
		else
			node->rb_parent->rb_left = left;
    }
    node->rb_parent = left;
}

void rb_insert_color(struct rb_node* node, struct rb_root* root)
{

	/**
	 * 
	 * 
	 * 
	 * 
	 * 
	 */

	struct rb_node *parent, *gparent;

	while ((parent = node->rb_parent) && parent->rb_color == RB_RED)
	{
		gparent = parent->rb_parent;

		if (parent == gparent->rb_left)
		{
			{
				struct rb_node *uncle = gparent->rb_right;
				if (uncle && uncle->rb_color == RB_RED)
				{
					uncle->rb_color = RB_BLACK;
					parent->rb_color = RB_BLACK;
					gparent->rb_color = RB_RED;
					node = gparent;
					continue;
				}
			}

			if (parent->rb_right == node)
			{
				struct rb_node *tmp;
				__rb_rotate_left(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			parent->rb_color = RB_BLACK;
			gparent->rb_color = RB_RED;
			__rb_rotate_right(gparent, root);
		}
        else
        {
			{
				struct rb_node *uncle = gparent->rb_left;
				if (uncle && uncle->rb_color == RB_RED)
				{
					uncle->rb_color = RB_BLACK;
					parent->rb_color = RB_BLACK;
					gparent->rb_color = RB_RED;
					node = gparent;
					continue;
				}
			}

			if (parent->rb_left == node)
			{
				struct rb_node *tmp;
				__rb_rotate_right(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			parent->rb_color = RB_BLACK;
			gparent->rb_color = RB_RED;
			__rb_rotate_left(gparent, root);
		}
	}

	root->rb_node->rb_color = RB_BLACK;
}

void rb_erase(struct rb_node* node, struct rb_root* root)
{
	struct rb_node *child, *parent;
	int color;

	if (!node->rb_left)
		child = node->rb_right;
	else if (!node->rb_right)
		child = node->rb_left;
	else
	{
		struct rb_node *old = node, *left;

		node = node->rb_right;
		while ((left = node->rb_left))
			node = left;
		child = node->rb_right;
		parent = node->rb_parent;
		color = node->rb_color;

		if (child)
			child->rb_parent = parent;
		if (parent)
		{
			if (parent->rb_left == node)
				parent->rb_left = child;
			else
				parent->rb_right = child;
		}
		else
			root->rb_node = child;

		if (node->rb_parent == old)
			parent = node;
		node->rb_parent = old->rb_parent;
		node->rb_color = old->rb_color;
		node->rb_right = old->rb_right;
		node->rb_left = old->rb_left;

		if (old->rb_parent)
		{
			if (old->rb_parent->rb_left == old)
				old->rb_parent->rb_left = node;
			else
				old->rb_parent->rb_right = node;
		} else
			root->rb_node = node;

		old->rb_left->rb_parent = node;
		if (old->rb_right)
			old->rb_right->rb_parent = node;
		goto color;
	}

	parent = node->rb_parent;
	color = node->rb_color;

	if (child)
		child->rb_parent = parent;
	if (parent)
	{
		if (parent->rb_left == node)
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->rb_node = child;

 color:
	if (color == RB_BLACK)
		__rb_erase_color(child, parent, root);
}

void __rb_erase_color(struct rb_node* node, struct rb_node* parent, struct rb_root* root)
{
	struct rb_node *other;

	while ((!node || node->rb_color == RB_BLACK) && node != root->rb_node)
	{
		if (parent->rb_left == node)
		{
			other = parent->rb_right;
			if (other->rb_color == RB_RED)
			{
				other->rb_color = RB_BLACK;
				parent->rb_color = RB_RED;
				__rb_rotate_left(parent, root);
				other = parent->rb_right;
			}
			if ((!other->rb_left ||
			     other->rb_left->rb_color == RB_BLACK)
			    && (!other->rb_right ||
				other->rb_right->rb_color == RB_BLACK))
			{
				other->rb_color = RB_RED;
				node = parent;
				parent = node->rb_parent;
			}
			else
			{
				if (!other->rb_right ||
				    other->rb_right->rb_color == RB_BLACK)
				{
					register struct rb_node *o_left;
					if ((o_left = other->rb_left))
						o_left->rb_color = RB_BLACK;
					other->rb_color = RB_RED;
					__rb_rotate_right(other, root);
					other = parent->rb_right;
				}
				other->rb_color = parent->rb_color;
				parent->rb_color = RB_BLACK;
				if (other->rb_right)
					other->rb_right->rb_color = RB_BLACK;
				__rb_rotate_left(parent, root);
				node = root->rb_node;
				break;
			}
		}
		else
		{
			other = parent->rb_left;
			if (other->rb_color == RB_RED)
			{
				other->rb_color = RB_BLACK;
				parent->rb_color = RB_RED;
				__rb_rotate_right(parent, root);
				other = parent->rb_left;
			}
			if ((!other->rb_left ||
			     other->rb_left->rb_color == RB_BLACK)
			    && (!other->rb_right ||
				other->rb_right->rb_color == RB_BLACK))
			{
				other->rb_color = RB_RED;
				node = parent;
				parent = node->rb_parent;
			}
			else
			{
				if (!other->rb_left ||
				    other->rb_left->rb_color == RB_BLACK)
				{
					register struct rb_node *o_right;
					if ((o_right = other->rb_right))
						o_right->rb_color = RB_BLACK;
					other->rb_color = RB_RED;
					__rb_rotate_left(other, root);
					other = parent->rb_left;
				}
				other->rb_color = parent->rb_color;
				parent->rb_color = RB_BLACK;
				if (other->rb_left)
					other->rb_left->rb_color = RB_BLACK;
				__rb_rotate_right(parent, root);
				node = root->rb_node;
				break;
			}
		}
	}
	if (node)
		node->rb_color = RB_BLACK;
}

// 取node的下一个节点
struct rb_node* rb_next(struct rb_node* node)
{
    // 右子树的最左边
    if(node->rb_right)
    {
        node = node->rb_right;
        while(node->rb_left) {
            node = node->rb_left;
        }
        return node;
    }

    // 若没有右子树, 需判断node是parent的左孩子还是👉孩子
    //  若node是parent的左孩子, 那么parent就是node的下一个节点
    //  若node是parent的右孩子, 那么node的下一个节点是: 沿着父节点向上走, 碰到的第一个可以将node划分到左子树的节点
    while(node->rb_parent && node == node->rb_parent->rb_right) {
        node = node->rb_parent;
    }

    return node->rb_parent;
}

// 取node的前一个节点
struct rb_node* rb_prev(struct rb_node* node)
{
    // 左子树的最右边
    if(node->rb_left)
    {
        node = node->rb_left;
        while(node->rb_right) {
            node = node->rb_right;
        }
        return node;
    }

    // 若没有左子树, 需判断node是parent的左孩子还是右孩子
    //  若node是parent的右孩子, 那么parent就是node的前一个节点
    //  若node是parent的左孩子, 那么node的前一个节点是: 沿着父节点向上走, 碰到的第一个可以将node划分到右子树的节点
    while(node->rb_parent && node == node->rb_parent->rb_left) {
        node = node->rb_parent;
    }

    return node->rb_parent;
}

// 取树中第一个节点
struct rb_node* rb_first(struct rb_root* root)
{
    struct rb_node* node = root->rb_node;
    
    if(node == NULL) {
        return NULL;
    }

    // 一直向左走
    while(node->rb_left) {
        node = node->rb_left;
    }
    return node;
}
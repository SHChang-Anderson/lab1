#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct StackNode {
 int pre_low, pre_high;
 int in_low, in_high;
 struct TreeNode* tnode;
};



#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (size_t) & (((type *) 0)->member)))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)



void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first)
        h->first->pprev = &n->next;
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}


int find(int num, int size, const struct hlist_head *heads)
{
    struct hlist_node *p;
    int hash = (num < 0 ? -num : num) % size;
    hlist_for_each (p, &heads[hash]) {
        struct order_node *on = list_entry(p, struct order_node, node);
        if (num == on->val) {
            return on->idx;
        }
    }
    return -1;
}





void node_add(int val,
                            int idx,
                            int size,
                            struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->idx = idx;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

struct TreeNode *buildTree(int *preorder,
                                  int preorderSize,
                                  int *inorder,
                                  int inorderSize)
{
    struct hlist_head in_heads[inorderSize];
    for (int i = 0; i < inorderSize; i++)
        INIT_HLIST_HEAD(&in_heads[i]);
    for (int i = 0; i < inorderSize; i++)
        node_add(inorder[i], i, inorderSize, in_heads);


    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    struct StackNode stack[preorderSize];

    int top = 0;
    struct TreeNode* root = malloc(sizeof(*root));
    root->val = preorder[0];
    root->left = root->right = NULL;
    top++;
    stack[top].tnode = root;
    stack[top].pre_low = 0;
    stack[top].pre_high = preorderSize - 1;
    stack[top].in_low = 0;
    stack[top].in_high = inorderSize - 1;
    
    while (top >= 0) {
        struct StackNode curr = stack[top--];
        if (top < 0) {
            break;
        }
        int fdnum = curr.tnode->val;
        int idx = find(fdnum, inorderSize, in_heads);
        curr.tnode->left = NULL;
        if (idx > curr.in_low) {
            struct TreeNode* node_ = malloc(sizeof(*node_));
            top++;
            stack[top].pre_low = curr.pre_low + 1;
            stack[top].pre_high = curr.pre_low + (idx - curr.in_low);
            stack[top].in_low = curr.in_low;
            stack[top].in_high = idx - 1;
            node_->val = preorder[stack[top].pre_low];
            node_->left = node_->right = NULL;
            curr.tnode->left = node_;
            stack[top].tnode = node_;
        }

        curr.tnode->right = NULL;
        if (idx < curr.in_high) {
            struct TreeNode* node_ = malloc(sizeof(*node_));
            top++;
            stack[top].pre_low = curr.pre_high - (curr.in_high - idx - 1);
            stack[top].pre_high = curr.pre_high;
            stack[top].in_low = idx + 1;
            stack[top].in_high = curr.in_high;
            node_->val = preorder[stack[top].pre_low];
            node_->left = node_->right = NULL;
            curr.tnode->right = node_;
            stack[top].tnode = node_;
        }

    }

    return root;
}



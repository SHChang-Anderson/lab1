#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

#define Tree_size(d) (1 << d) - 1

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (size_t) & (((type *) 0)->member)))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)


struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

struct hlist_head {
    struct hlist_node *first;
};

struct order_node {
    struct hlist_node node;
    int val;
    int idx;
};

// Function declarations

void INIT_HLIST_HEAD(struct hlist_head *h);
void hlist_add_head(struct hlist_node *n, struct hlist_head *h);
int find(int num, int size, const struct hlist_head *heads);
void node_add(int val, int idx, int size, struct hlist_head *heads);
struct TreeNode *buildTree(int *preorder, int preorderSize,
                            int *inorder, int inorderSize);

#endif // TREE_BUILDER_H

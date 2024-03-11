#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"




static struct TreeNode *InitTree(int counter, int depth, int *i) 
{
    if (counter > depth)
        return NULL;
    
    struct TreeNode *tn = malloc(sizeof(struct TreeNode));
    tn->val = (*i)++;
    tn->left = InitTree(counter+1, depth, i);
    tn->right = InitTree(counter+1, depth, i);

    return tn;
}

/* Assume each value is unique, check if two tree are same */
bool checkTree(struct TreeNode *a, struct TreeNode *b)
{
    if (!a && !b)
        return true;
    
    if ((a && b) && (a->val == b->val))
        return checkTree(a->left, b->left) && checkTree(a->right, b->right);

    return false;
}

void FreeTree(struct TreeNode *root) 
{
    if (!root)
        return;
    
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

void inorder(struct TreeNode *root, int *ret, int *i)
{
    if (!root)
        return;

    inorder(root->left, ret, i);
    *(ret + (*i)) = root->val;
    (*i)++;
    inorder(root->right, ret, i);
}

void preorder(struct TreeNode *root, int *ret, int *i)
{
    if (!root)
        return;

    *(ret + (*i)) = root->val;
    (*i)++;
    preorder(root->left, ret, i);
    preorder(root->right, ret, i);
}

void print_list(int *ret, int depth)
{
    for(int i=0; i < Tree_size(depth); i++)
        printf("%d -> ", *(ret+i));
    printf("\n");
}



// Function to print the inorder traversal of a binary tree
void printInorder(struct TreeNode *root) {
    if (root == NULL)
        return;
    printInorder(root->left);
    printf("%d ", root->val);
    printInorder(root->right);
}

int main() {
    int i = 0;
    int depth = 10;
    struct TreeNode *root1 = InitTree(1, depth, &i);

    // for tree with d-depth, there are (1 << d) - 1 nodes
    int inorder_list[Tree_size(depth)], preorder_list[Tree_size(depth)]; 


    i = 0;
    inorder(root1, inorder_list, &i);
    i = 0;
    preorder(root1, preorder_list, &i);

    int preorderSize = sizeof(inorder_list) / sizeof(inorder_list[0]);
    int inorderSize = sizeof(preorder_list) / sizeof(preorder_list[0]);

    // Build the tree
    struct TreeNode *root = buildTree(preorder_list, preorderSize, inorder_list, inorderSize);

    // Print the inorder traversal of the built tree
    printf("Inorder traversal of the constructed tree: ");
    printInorder(root);
    printf("\n");

    printf("Inorder traversal of the original tree: ");
    printInorder(root1);
    printf("\n");
    // Free the dynamically allocated memory for the tree nodes
    // This step is necessary to avoid memory leaks
    // You can implement a separate function to handle deallocation as well
    // Here, we're doing it directly in main for simplicity
    // You should always free dynamically allocated memory after use
    // to avoid memory leaks
    // Implement your own function if the tree is more complex
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

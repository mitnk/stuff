//
// Binary Search Tree
//
// http://cslibrary.stanford.edu/110/BinaryTrees.html
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree_node Node;

struct tree_node {
    int data;
    Node *left;
    Node *right;
};

Node *create_node(int n)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = n;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node ** root, Node * node) {
    if (!node)
        return;
    if (!(*root))
    {
        *root = node;
        return;
    }
    if (node->data <= (*root)->data)
        insert(&(*root)->left, node);
    else
        insert(&(*root)->right, node);
}

void printout(Node * root) {
    if (root)
    {
        if (root->left)
            printout(root->left);
        printf("%d ", root->data);
        if (root->right)
            printout(root->right);
    }
}

Node *lookup(Node *root, int n)
{
    if(!root)
        return NULL;
    if (root->data == n)
        return root;
    else if (root->data > n)
        return lookup(root->left, n);
    else
        return lookup(root->right, n);

}

size_t tree_size(Node *root)
{
    if (!root)
        return 0;
    return 1 + tree_size(root->left) + tree_size(root->right);
}

size_t tree_max_depth(Node *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    size_t depth_left = tree_max_depth(root->left);
    size_t depth_right = tree_max_depth(root->right);
    return depth_right > depth_left ? 1 + depth_right : 1 + depth_left;
}

// for non-empty tree
int tree_min_value(Node *root)
{
    while(root->left)
    {
        root = root->left;
    }
    return root->data;
}

// left nodes, right nodes, finally node itself
// This is the sort of  bottom-up traversal that would be used,
// for example, to evaluate an expression tree where a node is
// an operation like '+' and its subtrees are, recursively,
// the two subexpressions for the '+'.
void tree_print_post_order(Node *root)
{
    if (!root)
        return;
    if (root->left)
        tree_print_post_order(root->left);
    if (root->right)
        tree_print_post_order(root->right);
    printf("%d ", root->data);
}

int main() {
    srand(time(0));
    Node *root = NULL;
    int i, n;
    printf("Input -> ");
    for (i = 1; i <= 6; ++i)
    {
        // number 1 - 10
        n = (int)(rand() % 10 + 1);
        printf("%d ", n);
        Node *node = create_node(n);
        insert(&root, node);
    }
    printf("\nTree  -> ");
    printout(root);
    printf("\n");

    printf("Size of the tree is %ld\n", tree_size(root));
    printf("The max depth of the tree is %ld\n", tree_max_depth(root));
    printf("The min value of the tree is %d\n", tree_min_value(root));
    printf("Print the tree with post order: ");
    tree_print_post_order(root);
    printf("\n");
    return 0;
}

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

int main() {
    srand(time(0));
    Node *root = NULL;
    int i;
    for (i = 1; i <= 20; ++i)
    {
        // number 1 - 30
        Node *node = create_node((int)(rand() % 30 + 1));
        insert(&root, node);
    }

    int seeking = 7;
    Node *item = lookup(root, seeking);
    if (item)
        printf("We have found: %d !!!\n", item->data);
    else
        printf("%d is not in the tree\n", seeking);

    printout(root);
    return 0;
}

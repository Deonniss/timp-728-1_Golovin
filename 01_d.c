#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree
{
    struct node *root;
    int count;
} tree;

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

void init(tree* t) {
    t->root = NULL;
    t->count = 0;
}

int insert(tree* t, int value) {
    
    node *nodeNew = (node*) malloc(sizeof(node));
    node *node1 = t->root, *node2 = NULL;
    while (node1 != NULL) {
        node2 = node1;
        if (value < node1->key) {
            node1 = node1->left;
        } else if (value == node1->key) {
            return 1;
        } else {
            node1 = node1->right;
        }
    }
    nodeNew->key = value;
    nodeNew->left = NULL;
    nodeNew->right = NULL;
    nodeNew->parent = node2;
    
    if (t->root == NULL) {
        t->root = nodeNew;
    }

    if (node2 != NULL) {
        if (value < node2->key) {;
            node2->left = nodeNew;
        } else  {
            node2->right = nodeNew;
        }
    }
    t->count++;
    return 0;
}

//СТЭК

typedef struct Stack_tag {
    node data[8];
    int size;
} Stack;

void push(Stack *stack, node* value) {
    stack->data[stack->size] = *value;
    stack->size++;
}

node pop(Stack *stack) {

    stack->size--;
    return stack->data[stack->size];
}

int empty(Stack *stack) {

    if (stack->size == 0) {
        return 0;
    } else {
        return 1;
    }
}

void direct(node* nodeA){

    if (nodeA == NULL) {
        return;
    }
    
    Stack st;
    st.size = 0;
    push(&st, nodeA);
    
    while (empty(&st) != 0) {
        *nodeA = pop(&st);
        printf("%d ", nodeA->key);
        if (nodeA->right != NULL) {
            push(&st, nodeA->right);
        }
        if (nodeA->left != NULL) {
            push(&st, nodeA->left);
        }
    }
}

void print_tree(tree* t) {
    direct(t->root);
}


int main()
{
    tree t;
    init(&t);
    int a, a1, a2, a3, a4, a5, a6;
    
    scanf("%d %d %d %d %d %d %d", &a, &a1, &a2, &a3, &a4, &a5, &a6);
    insert(&t, a);
    insert(&t, a1);
    insert(&t, a2);
    insert(&t, a3);
    insert(&t, a4);
    insert(&t, a5);
    insert(&t, a6);
    print_tree(&t);
    printf("\n");
    return 0;
}



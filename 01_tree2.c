#include <stdio.h>
#include <stdlib.h>

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


// Инициализация дерева
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

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(node* n, int value) {
    if (n == NULL || (n->key == value)) {
        return n;
    }
    if (value < n->key) {
        return find(n->left, value);
    } else {
        return find(n->right, value);
    }
}



typedef struct struct_item{
    void *payload;
    struct struct_item* next;
} item;

typedef struct struct_queue{
    item* begin;
    item* end;
}queue;

queue* create_queue(){
    queue* res = malloc(sizeof(queue));
    res->begin = NULL;
    res->end = NULL;
    return res;
}

void queue_push(queue* q, void *payload){
    item *i = malloc(sizeof(item));
    i->next = NULL;
    i->payload = payload;

    if(q->end == NULL){
        q->begin = i;
        q->end = i;
    }else{
        q->end->next = i;
        q->end = i;
    }
}

void* queue_pop(queue *q){
    if(q->begin == NULL) return NULL;
    item *current = q->begin;
    q->begin = q->begin->next;
    if(q->begin == NULL) q->end = NULL;
    void* payload = current->payload;
    free(current);
    return payload;
}


void print(node* root){
    queue* q_current = NULL;
    queue* q_next = create_queue();
    queue_push(q_next, (void *) root);

    int isNotLastLevel;
    do{
        free(q_current);
        q_current = q_next;
        q_next = create_queue();
        void* payload;

        isNotLastLevel = 0;
        while(q_current->begin != NULL){
            payload = queue_pop(q_current);
            if(payload != NULL){
                node* n = (node *)payload;
                printf("%d ", n->key);
                queue_push(q_next, n->left);
                queue_push(q_next, n->right);
                isNotLastLevel = isNotLastLevel || n->left || n->right;
            }else{
                printf("_ ");
                queue_push(q_next, NULL);
                queue_push(q_next, NULL);
            }
        }
        printf("\n");
    } while(isNotLastLevel);

    free(q_current);
    while(q_next->begin != NULL) queue_pop(q_next);
    free(q_next);

    printf("\n");
}

void clean(tree* tr, node* t) {
    if (t->left != NULL) {
        clean(tr, t->left);
    }
    if (t->right != NULL) {
        clean(tr, t->right);
    }
    if (t->parent != NULL) {
        node* node3 = t->parent;
        if (node3->right == t) {
           node3->right = NULL;
        } else {
            node3->left = NULL;
        }
    } else {
        tr->root = NULL;
    }
    tr->count--;
    free(t);
    
}




node *min(node *root)
{
    node *l = root;
    while (l -> left != NULL)
        l = l -> left;
    return l;
}

void replaceParent(node* son, node* new) {
    if (son->parent != NULL) {
        node* parentNode = son->parent;
        if (parentNode->right == son) {
            parentNode->right = new;
        } else {
            parentNode->left = new;
        }
        if (new != NULL)
            new->parent = parentNode;
    } else {
        if (new != NULL) 
            new->parent = NULL;
        
    }
    
}

int remove_node(tree* t, int value) {
    
    node *node1 = t->root, *node2 = NULL, *node3 = NULL;
    node2 = find(node1, value);
    
    if (node2 == NULL) {
        return 1;
    }
    
    
    if (node2->right == NULL && node2->left == NULL) {
        replaceParent(node2, NULL);
        free(node2);
        t->count--;
        return 0;
    } else if (node2->right != NULL && node2->left == NULL) {

        replaceParent(node2, node2->right);
        free(node2);
        t->count--;
        return 0;
    } else if (node2->right == NULL && node2->left != NULL) { 

        replaceParent(node2, node2->left);
        free(node2);
        t->count--;
        return 0;
    } else if ((node2->left != NULL) && (node2->right != NULL)) {
        node1 = min(node2->right);
        if (node1 != NULL) {
            int a = node1->key;
            remove_node(t, a);
            node2->key = a;
            return 0;
        }
    }
    return 1;
    
}

int remove_min(tree* t, node* n) {
    if (n == NULL) {
        return 0;
    }
    node *node1 = min(n);
    int a = node1->key;
    remove_node(t, a);
    t->count--;
    return a;
}

int rotate_right(tree* t, node* n) {
    
    if (n != NULL && n->left != NULL) {
        t->root = n->left;
        node *temp = n->left->right;
        n->left->right = n;
        n->parent = n->left;
        n->left->parent = NULL;
        n->left = temp;
        if (temp != NULL) 
            temp->parent = n;
        return 0;
    }
    return 1;
}

int rotate_left(tree* t, node* n) {

    if (n != NULL && n->right != NULL) {
        t->root = n->right;
        node *temp = n->right->left;
        n->right->left = n;
        n->parent = n->right;
        n->right->parent = NULL;
        n->right = temp;
        
        if (temp != NULL) 
            temp->parent = n;
        return 0;
    }
    return 1;
}

void print_tree(tree* t) {
    print(t->root);
}

void printFound(node* n) {
    if (n == NULL) {
        printf("-");
    }else {
        if (n->parent == NULL) {
            printf("_ "); 
        } else {
            printf("%d ", n->parent->key);
        }
        if (n->left == NULL) {
            printf("_ "); 
        } else {
            printf("%d ", n->left->key);
        }
        if (n->right == NULL) {
            printf("_"); 
        } else {
            printf("%d", n->right->key);
        }
    }
    printf("\n\n");
}


int main()
{
    tree t;
    init(&t);
    int a, a1, a2, a3;
    
    scanf("%d %d %d %d", &a, &a1, &a2, &a3);
    insert(&t, a);
    insert(&t, a1);
    insert(&t, a2);
    insert(&t, a3);
    print_tree(&t);
    
    scanf("%d %d %d", &a, &a1, &a2);
    insert(&t, a);
    insert(&t, a1);
    insert(&t, a2);
    print_tree(&t);
    
    scanf("%d", &a);
    node* n = find(t.root, a);
    printFound(n);
    
    scanf("%d", &a);
    n = find(t.root, a);
    printFound(n);
    
    scanf("%d", &a);
    remove_node(&t, a);
    print_tree(&t);

    a = 0;
    while (a == 0) {
       a = rotate_left(&t, t.root); 
    }
    print_tree(&t);
    a = 0;
    while (a == 0) {
       a = rotate_right(&t, t.root); 
    }
    print_tree(&t);

    printf("%d\n", t.count);
    clean(&t, t.root);
    print_tree(&t);
    return 0;
}

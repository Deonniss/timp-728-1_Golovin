#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;


// инициализация пустого списка
void init(list *l) {
	l->head = NULL;
}

// удалить все элементы из списка
void clean(list *l) {
	node *next_t = l->head->next;
	while (next_t) {
        next_t = l->head->next;
        free(l->head);
        l->head = l->head->next;
    }
}

// проверка на пустоту списка
bool is_empty(list *l) {
    if (l->head == NULL) {
        return true;
    } else {
        return false;
    }
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int value) { 
    node* nodeN = l->head;
    while (nodeN) {
    	if (nodeN->value == value) {
        	return nodeN;
        }
        nodeN = nodeN->next;
    }
    return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value) {
	if (l->head == NULL) {
	    l->head = (node*) malloc(sizeof(node));
	    l->head->value = value; 
		l->head->next = NULL;
		return 0;
	} else {
		node* nodeN = l->head;
        while (nodeN->next != NULL) {
        	nodeN = nodeN->next;
        }
        node *nodeNew = (node*) malloc(sizeof(node));
		nodeNew->value = value; 
		nodeNew->next = NULL;
		nodeN->next = nodeNew;
	}   
    return 0; //nodeNew->value == value ? 0 : 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value) {
	node *nodeNew = (node*) malloc(sizeof(node));
	nodeNew->value = value; 
	nodeNew->next = l->head;
	l->head = nodeNew;
	return nodeNew->value == value ? 0 : 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value) {
    if (n != NULL) {
        node *nodeNew = (node*) malloc(sizeof(node));
		nodeNew->value = value; 
		nodeNew->next = n->next;
		n->next = nodeNew;
		return 0;
    } else {
        return 1;
    }    
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value) { 
	node* nodeN = l->head;
	node* nodeL = NULL;
    while (nodeN) {
        if (nodeN->value == value) {
            if (nodeL != NULL) {
                nodeL->next = nodeN->next;
                free(nodeN);    
            } else {
                l->head = nodeN->next;
                free(nodeN);
            }
            return 0;
        }
        nodeL = nodeN;
        nodeN = nodeN->next;
    }
    return 1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
	node *temp = l->head;
	while (l->head) {
	    printf(" %d ", l->head->value);
        l->head = l->head->next;
    }
    l->head = temp;
    printf(" \n");
}

void add(list *l, int value, int index) {
    node* nodeN = l->head;
    for (int i = 1; i < index; i++) {
        nodeN = nodeN->next;
    }
    if (nodeN != NULL) {
        node *nodeNew = (node*) malloc(sizeof(node));
        nodeNew->value = value; 
		nodeNew->next = nodeN->next;
		nodeN->next = nodeNew;
    }
}


int main()
{
	int n, s, s1, s2;
    list l;
    init(&l);
	scanf(" %d", &n);
	    for (int i = 0; i < n; i++) {
	        scanf("%d", &s);
	        push_back(&l, s);
	    }
	   
	print(&l);
	scanf(" %d %d  %d ", &s, &s1, &s2);
	printf(" %d %d  %d \n", find(&l, s) != NULL, find(&l, s1) != NULL, find(&l, s2) != NULL);

	scanf("%d", &s);
	push_back(&l, s);
	print(&l);
	
	scanf(" %d", &s);
	push_front(&l, s);
	print(&l);
	
	scanf(" %d %d", &s, &s1);
	add(&l, s1, s);
	print(&l);
	
	scanf(" %d", &s);
	remove_node(&l, s);
	print(&l);
	
	clean(&l);
	print(&l);

	return 0;
}

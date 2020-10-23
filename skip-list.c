#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// todo: what is the use of keys in here

typedef char DATA;

typedef struct node_t {
    int key; // key should be INT_MIN for head nodes
    DATA value;
    struct node_t *up, *down, *left, *right;
} NODE;

// struct defination for skip list
typedef struct list_t {
    NODE *head;
    int levels; // levels are 0 indexed
} LIST;

NODE *insertAfterAbove(NODE *after, NODE *above, int key, DATA data);
NODE *promote(LIST *list, NODE *node);
bool tossCoin();
NODE *promoteNewLevel(LIST *list, NODE *node);
NODE *init_node(int key, DATA value);
LIST *init_list();
NODE *search(LIST *list, int key);
NODE *insert(LIST *list, int key, DATA data);
bool tossCoin();
NODE *parent(const NODE *node);
void deleteNode(LIST *list, NODE *node);

#define DEBUG

// return pointer to a node with given key in the lowest level
NODE *search(LIST *list, const int key) {
    NODE *node = list->head;

    while (true) {
        assert(node);
        while (node->right && node->right->key <= key)
            node = node->right;

        if (node->down)
            node = node->down;
        else
            break;
    }

    return node;
}

NODE *insert(LIST *list, int key, DATA data) {
    NODE *prev = search(list, key);

    // check if key is already present
    if (prev->key == key)
        return prev;

    NODE *newNode = insertAfterAbove(prev, NULL, key, data);

#ifdef DEBUG
    printf("\nInserting %d into tree, %d, %d", key,
           newNode->left->key, newNode->key);
    if (newNode->right)
        printf(", %d", newNode->right->key);
    printf("\n");
#endif

    while (tossCoin()) {
        newNode = promote(list, newNode);
    }

    return newNode;
}

void removeKey(LIST *list, int key) {
    NODE *node = search(list, key);

    if (node->key == key)
        deleteNode(list, node);
}

void deleteNode(LIST *list, NODE *node) {
#ifdef DEBUG
    printf("deleting %d\n", node->key);
#endif

    NODE *parent = node->up;

    NODE *left = node->left;
    NODE *right = node->right;

    if (left)
        left->right = right;
    if (right)
        right->left = left;

    free(node);

    if (parent != NULL)
        deleteNode(list, parent);
}

void printList(LIST *list) {
    printf("Number of levels: %d\n\n", list->levels);

    for (NODE *head = list->head; head; head = head->down) {
        assert(head);

        for (NODE *node = head; node; node = node->right) {
            printf("  %d", node->key);
            if (node->down)
                printf("(%d)", node->down->key);
        }
        printf("\n\n");
    }
}

// initialize node of a skip list
NODE *init_node(const int key, const DATA value) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->up = NULL;
    newNode->down = NULL;
    return newNode;
}

// initialize a new skip list
LIST *init_list() {
    LIST *newList = (LIST *)malloc(sizeof(LIST));
    newList->head = init_node(INT_MIN, 0);
    newList->levels = 0;
    return newList;
}

static bool _rand_init =
    false; // a flag indicating the initialization of seed
bool tossCoin() {
    if (_rand_init == false) { // if the seed has not been set
        srand(time(0));        // set the seed of the random number
                               // initializer to the current time
        _rand_init = true; // set the flag to true so that the seed is
                           // not set again
    }
    return (double)rand() / RAND_MAX < 0.5;
}

// get parent
NODE *parent(const NODE *node) {
    // printf("finding parent of %d\n", node->key);

    assert(node);

    NODE *parent = node->left;
    while (parent && parent->up == NULL)
        parent = parent->left;
    if (parent && parent->up)
        parent = parent->up;

    // printf("found parent of %d\n", node->key);
    return parent;
}

// insert 'node' into higher level
NODE *promote(LIST *list, NODE *node) {
    NODE *parentNode = parent(node);

#ifdef DEBUG
    printf("Promoting %d to a higher level\n", node->key);
#endif

    if (parentNode == NULL)
        return promoteNewLevel(list, node);
    else
        return insertAfterAbove(parentNode, node, node->key,
                                node->value);
}

NODE *promoteNewLevel(LIST *list, NODE *node) {
    NODE *newHead = init_node(INT_MIN, 0);
    NODE *oldHead = list->head;
    oldHead->up = newHead;
    newHead->down = oldHead;
    list->head = newHead;

    list->levels += 1;

    printf("Created new level for %d\n", node->key);

    return insertAfterAbove(newHead, node, node->key, node->value);
}

NODE *insertAfterAbove(NODE *after, NODE *above, int key, DATA data) {
    NODE *newNode = init_node(key, data);
    newNode->down = above;
    newNode->up = NULL;
    newNode->right = after->right;
    newNode->left = after;

    assert(after);
    after->right = newNode;

    if (above)
        above->up = newNode;

    assert(after);
    assert(after->right->key == newNode->key);
    if (above)
        assert(above->up->key == newNode->key);

    return newNode;
}

int main() {
    LIST *list = init_list();
    insert(list, 1, 1);
    insert(list, 2, 2);
    insert(list, 3, 3);
    insert(list, 4, 4);
    insert(list, 5, 5);
    insert(list, 6, 6);
    insert(list, 7, 7);

    removeKey(list, 1);
    // removeKey(list, 2);
    removeKey(list, 3);
    removeKey(list, 4);
    removeKey(list, 5);

    printList(list);

    return 0;
}

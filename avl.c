#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode_t {
    int key;
    struct treenode_t *left;
    struct treenode_t *right;
    int height;
};

typedef struct treenode_t *Tree;

// Allocate memory for a new tree
Tree newTree(int key) {
    Tree tree = (Tree)calloc(1, sizeof(struct treenode_t));
    tree->key = key;
    tree->height = 1;

    return tree;
}

// safe way of getting height
int max(int a, int b) { return a > b ? a : b; }

int height(Tree tree) { return tree ? tree->height : 0; }

int updateHeight(Tree tree) {
    if (tree == NULL) {
        tree->height =
            max(height(tree->left), height(tree->right)) + 1;
    }
    return 0;
}

bool verifyHeight(Tree tree) {
    if (tree == NULL) {
        return true;
    }

    int trueHeight = max(height(tree->left), height(tree->right)) + 1;
    if (height(tree) != trueHeight) {
        fprintf(stderr,
                "Line %d: %s called but the tree %d does not have "
                "correct height: %d, %d.\n",
                __LINE__, __func__, tree->key, height(tree),
                trueHeight);
        return false;
    }

    return true;
}

int getBalanceFactor(Tree tree) {
    if (tree == NULL) {
        fprintf(stderr,
                "Line %d: %s called but the tree does not exist.\n",
                __LINE__, __func__);
        return 0;
    }
    return height(tree->left) - height(tree->right);
}

// check if a given BST is an AVL tree
bool checkAVL(Tree tree) {
    if (tree == NULL) {
        return true;
    }
    // check balance factor
    int balanceFactor = getBalanceFactor(tree);
    verifyHeight(tree);
    if (balanceFactor < -1 || balanceFactor > 1) {
        fprintf(stderr, "Line %d: %s tree is not balanced at %d.\n",
                __LINE__, __func__, tree->key);
        return false;
    }
    else {
        return checkAVL(tree->left) && checkAVL(tree->right);
    }
}

// Right rotate an AVL tree
Tree rotateRight(Tree tree) {
    //      x           y
    //     / \         / \
    //    y   c  -->  a   x
    //   / \             / \
    //  a   b           b   c

    Tree x = tree;
    Tree y = x->left;
    assert(y);
    Tree b = y->right;

    // now rotating
    y->right = x;
    x->left = b;

    // update heights
    updateHeight(x);
    updateHeight(y);

    checkAVL(x);
    checkAVL(y);

    printf("Line %d: Height of tree %d: %d %d\n", __LINE__, tree->key,
           height(tree),
           max(height(tree->left), height(tree->right)) + 1);

    return y;
}

// Left rotate an AVL tree
Tree rotateLeft(Tree tree) {
    //    y               x
    //   / \             / \
    //  a   x    -->    y   c
    //     / \         / \
    //    b   c       a   b

    Tree y = tree;
    Tree x = y->right;
    assert(x);
    Tree b = x->left;

    // now rotating
    y->right = b;
    x->left = y;

    // update heights
    updateHeight(y);
    updateHeight(x);

    checkAVL(x);
    checkAVL(y);

    printf("Line %d: Height of tree %d: %d %d\n", __LINE__, tree->key,
           height(tree),
           max(height(tree->left), height(tree->right)) + 1);

    return x;
}

// Insert a node into a BST tree
Tree insertBST(Tree tree, int key) {
    // base case
    if (tree == NULL)
        return newTree(key);

    if (tree->key == key)
        return tree;

    if (tree->key < key)
        tree->right = insertBST(tree->right, key);
    if (tree->key > key)
        tree->left = insertBST(tree->left, key);

    updateHeight(tree);
    return tree;
}

// balance a tree
Tree balanced(Tree tree) {
    int balanceFactor = getBalanceFactor(tree);

    // right heavy
    if (balanceFactor < -1) {
        if (tree->right && getBalanceFactor(tree->right) > 0) {
            // TODO: understand
            // right left
            tree->right = rotateRight(tree->right);
            checkAVL(tree->right);
        }
        // for both right right and right left
        tree = rotateLeft(tree);
        checkAVL(tree);
        return tree;
    }
    // left heavy
    if (balanceFactor > 1) {
        if (tree->left && getBalanceFactor(tree->left) < 0) {
            // TODO: understand
            // left right
            tree->left = rotateLeft(tree->left);
            checkAVL(tree->left);
        }
        // for both left right and left left
        tree = rotateRight(tree);
        checkAVL(tree);
        return tree;
    }

    return tree;
}

// find node with min value in the BST
Tree minTreeBST(Tree tree) {
    while (tree && tree->left) {
        tree = tree->left;
    }
    return tree;
}

// Insert a node into an AVL tree
Tree insertAVL(Tree tree, int key) {
    // base case
    if (tree == NULL)
        return newTree(key);

    if (tree->key == key)
        return tree;

    if (tree->key < key)
        tree->right = insertAVL(tree->right, key);
    if (tree->key > key)
        tree->left = insertAVL(tree->left, key);

    assert(tree);
    updateHeight(tree);

    // return tree after balancing
    Tree balancedTree = balanced(tree);
    checkAVL(tree);
    return balancedTree;
}

Tree deleteBST(Tree tree, int key) {
    // base case
    if (tree == NULL) {
        return NULL;
    }

    if (key < tree->key) {
        tree->left = deleteBST(tree->left, key);
    }
    if (key > tree->key) {
        tree->right = deleteBST(tree->right, key);
    }
    if (key == tree->key) {
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        }
        if (tree->right && tree->left == NULL) {
            Tree tempTree = tree;
            tree = tree->right;
            free(tempTree);
        }
        if (tree->right == NULL && tree->left) {
            Tree tempTree = tree;
            tree = tree->left;
            free(tempTree);
        }
        if (tree->right && tree->left) {
            // TODO: understand
            Tree tempTree = minTreeBST(tree->right);
            tree->key = tempTree->key;
            tree->right = deleteBST(tree->right, tempTree->key);
        }
    }
    assert(tree);
    updateHeight(tree);
    return tree;
}

Tree deleteAVL(Tree tree, int key) {
    // base case
    if (tree == NULL) {
        return NULL;
    }

    if (key < tree->key) {
        tree->left = deleteAVL(tree->left, key);
    }
    if (key > tree->key) {
        tree->right = deleteAVL(tree->right, key);
    }
    if (key == tree->key) {
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        }
        if (tree->right && tree->left == NULL) {
            Tree tempTree = tree;
            tree = tree->right;
            free(tempTree);
        }
        if (tree->right == NULL && tree->left) {
            Tree tempTree = tree;
            tree = tree->left;
            free(tempTree);
        }
        if (tree->right && tree->left) {
            // TODO: understand
            Tree tempTree = minTreeBST(tree->right);
            tree->key = tempTree->key;
            tree->right = deleteAVL(tree->right, tempTree->key);
            printf("Line %d: Height of %d: %d %d\n", __LINE__,
                   tree->key, height(tree),
                   max(height(tree->left), height(tree->right)) + 1);
        }
    }
    assert(tree);
    updateHeight(tree);
    checkAVL(tree);
    return balanced(tree);
}

// copy pasted from stackoverflow
int _print_t(Tree tree, int is_left, int offset, int depth,
             char s[20][255]) {
    char b[20];
    int width = 5;

    if (!tree)
        return 0;

    sprintf(b, "(%03d)", tree->key);

    int left = _print_t(tree->left, 1, offset, depth + 1, s);
    int right =
        _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] =
            '+';
    }
    else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}

Tree search(Tree tree, int key) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree->key == key) {
        return tree;
    }
    else if (tree->key < key) {
        return search(tree->right);
    }
    else {
        return search(tree->left);
    }
}

// copy pasted from stackoverflow
void print_t(Tree tree) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

void driver() {
    Tree avl = NULL;
    char command[80];
    while (true) {
        // check validity of AVL tree on every step
        assert(checkAVL(avl));

        printf("[bs-avl@tree ~]$ ");
        scanf("%s", command);
        if (strcmp(command, "exit") == 0) {
            break;
        }
        else if (strcmp(command, "insert") == 0) {
            int key = 0;
            scanf("%d", &key);
            avl = insertAVL(avl, key);
            print_t(avl);
        }
        else if (strcmp(command, "delete") == 0) {
            int key = 0;
            scanf("%d", &key);
            avl = deleteAVL(avl, key);
            print_t(avl);
        }
        else if (strcmp(command, "print") == 0) {
            print_t(avl);
        }
    }
}

int main() {
    driver();
    return 0;
}

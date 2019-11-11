
#ifndef AA_TREE_H
#define AA_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

struct Node {
    struct Node *left;
    struct Node *right;
    int level;
    long key;
};

typedef struct Node Node;

Node *successor(Node *n);

Node *predecessor(Node *n);

Node *decrease_level(Node *T);

Node *skew(Node *T);

Node *split(Node *T);

Node *insert(long value, Node *T);

Node *delete(long value, Node *T);

#endif


#include "aa_tree.h"


Node *skew(Node *T)
{
    if (T == NULL) {
        return NULL;
    } else if (T->left == NULL) {
        return T;
    } else if (T->left->level == T->level) {
        Node *L = T->left;
        T->left = L->right;
        L->right = T;
        return L;
    } else {
        return T;
    }
}

Node *split(Node *T)
{
    if (T == NULL) {
        return NULL;
    } else if (T->right == NULL || T->right->right == NULL) {
        return T;
    } else if (T->level == T->right->right->level) {
        Node *R = T->right;
        T->right = R->left;
        R->left = T;
        R->level++;
        return R;
    } else {
        return T;
    }
}

Node *insert(long value, Node *T)
{
    if (T == NULL) {
        Node *n = (Node*)malloc(sizeof(Node));
        n->key = value;
        n->level = 1;
        n->left = NULL;
        n->right = NULL;
        return n;
    } else if (value < T->key) {
        T->left = insert(value, T->left);
    } else if (value > T->key) {
        T->right = insert(value, T->right);
    }
    T = skew(T);
    T = split(T);
    return T;
}

Node *delete(long value, Node *T)
{
    if (T == NULL) {
        return T;
    } else if (value > T->key) {
        T->right = delete(value, T->right);
    } else if (value < T->key) {
        T->left = delete(value, T->left);
    } else {
        if (T->left == NULL && T->right == NULL) {
            return NULL;
        } else if (T->left == NULL) {
            Node *L = successor(T);
            T->right = delete(L->key, T->right);
            T->key = L->key;
        } else {
            Node *L = predecessor(T);
            T->left = delete(L->key, T->left);
            T->key = L->key;
        }
    }
    T = decrease_level(T);
    T = skew(T);
    T->right = skew(T->right);
    if (T->right != NULL) {
        T->right->right = skew(T->right->right);
    }
    T = split(T);
    T->right = split(T->right);
    return T;
}

Node *successor(Node *n)
{
    Node *temp = n->right;
    while (temp != NULL) {
        temp = temp->left;
    }
    return temp;
}

Node *predecessor(Node *n)
{
    Node *temp = n->left;
    while (temp != NULL) {
        temp = temp->right;
    }
    return temp;
}

Node *decrease_level(Node *T)
{
    int should_be = min(T->left->level, T->right->level + 1);
    if (should_be < T->level) {
        T->level = should_be;
        if (should_be < T->right->level) {
            T->right->level = should_be;
        }
    }
    return T;
}








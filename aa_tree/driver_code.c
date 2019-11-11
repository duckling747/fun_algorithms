
#include "aa_tree.h"


void print_tree(Node *T);

void main(void)
{
    char *line = NULL;
    size_t buff = 0;
    ssize_t len;
    
    while ((len = getline(&line, &buff, stdin)) != EOF) {
        char *end = NULL;
        Node *tree = NULL;
        for (long i = strtol(line, &end, 10);
                line != end;
                i = strtol(line, &end, 10)) {
            tree = insert(i, tree);
            line = end;
        }
        // print tree
        print_tree(tree);
        printf("\n");
    }
}

void print_tree(Node *T)
{
    if (T == NULL) {
        return;
    } else {
        printf("%ld ", T->key);
        print_tree(T->left);
        print_tree(T->right);
    }
}

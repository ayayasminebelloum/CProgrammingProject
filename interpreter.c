#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ASSIGN_NODE,
    PRINT_NODE,
    ADD_NODE,
    NUMBER_NODE,
    IDENTIFIER_NODE
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *create_node(NodeType type, const char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = strdup(value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_node(ASTNode *node) {
    if (node == NULL)
        return;
    free(node->value);
    free_node(node->left);
    free_node(node->right);
    free(node);
}

void interpret(ASTNode *root) {
    if (root == NULL)
        return;

    switch (root->type) {
    case ASSIGN_NODE:
        printf("Assign: %s = %s\n", root->left->value, root->right->value);
        break;
    case PRINT_NODE:
        printf("Print: %s\n", root->left->value);
        break;
    case ADD_NODE:
        printf("Add: %s + %s\n", root->left->value, root->right->value);
        break;
    case NUMBER_NODE:
        printf("Number: %s\n", root->value);
        break;
    case IDENTIFIER_NODE:
        printf("Identifier: %s\n", root->value);
        break;
    default:
        printf("Unknown node type\n");
    }

    interpret(root->left);
    interpret(root->right);
}

int main() {
    ASTNode *root = create_node(ASSIGN_NODE, "=");
    root->left = create_node(IDENTIFIER_NODE, "x");
    root->right = create_node(NUMBER_NODE, "10");

    interpret(root);

    free_node(root);

    return 0;
}

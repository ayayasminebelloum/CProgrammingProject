#include <stdio.h>

// Define AST node types
typedef enum {
    ASSIGN_NODE,
    PRINT_NODE,
    ADD_NODE,
    NUMBER_NODE,
    IDENTIFIER_NODE,
    UNKNOWN_NODE
} ASTNodeType;

// Define AST node structure
typedef struct ASTNode {
    ASTNodeType type;
    char* value; // For simplicity, assuming it's a string for all node types
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

// Function to interpret the AST
void interpret(ASTNode* root) {
    if (root == NULL) {
        return;
    }

    switch (root->type) {
        case ASSIGN_NODE:
            // Interpret assignment node
            printf("Assign: %s = %s\n", root->left->value, root->right->value);
            break;
        case PRINT_NODE:
            // Interpret print node
            printf("Print: %s\n", root->left->value);
            break;
        case ADD_NODE:
            // Interpret add node
            printf("Add: %s + %s\n", root->left->value, root->right->value);
            break;
        case NUMBER_NODE:
            // Interpret number node
            printf("Number: %s\n", root->value);
            break;
        case IDENTIFIER_NODE:
            // Interpret identifier node
            printf("Identifier: %s\n", root->value);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }

    // Recursively interpret child nodes
    interpret(root->left);
    interpret(root->right);
}

int main() {
    // Example AST (replace with your actual AST)
    ASTNode* root = malloc(sizeof(ASTNode));
    root->type = ASSIGN_NODE;
    root->left = create_node(IDENTIFIER_NODE, "x");
    root->right = create_node(NUMBER_NODE, "10");

    // Interpret the AST
    interpret(root);

    return 0;
}

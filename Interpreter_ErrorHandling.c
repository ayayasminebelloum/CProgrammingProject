#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define AST node types
typedef enum {
    ASSIGN_NODE,
    PRINT_NODE,
    ADD_NODE,
    NUMBER_NODE,
    IDENTIFIER_NODE
} NodeType;

// Define AST node structure
typedef struct ASTNode {
    NodeType type;
    char* value;  // For simplicity, using 'value' to store lexemes or values
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

// Function to create AST nodes
ASTNode* create_node(NodeType type, const char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = strdup(value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to free AST nodes
void free_node(ASTNode* node) {
    if (node == NULL) return;
    free(node->value);
    free_node(node->left);
    free_node(node->right);
    free(node);
}

// Define error types
typedef enum {
    NO_ERROR,
    ASSIGNMENT_ERROR,
    PRINT_ERROR,
    ADDITION_ERROR,
    NUMBER_ERROR,
    IDENTIFIER_ERROR,
    UNKNOWN_ERROR
} ErrorCode;

// Define error structure
typedef struct {
    ErrorCode code;
    char* message;
} Error;

// Function to create an error
Error create_error(ErrorCode code, const char* message) {
    Error error;
    error.code = code;
    error.message = malloc(strlen(message) + 1);
    strcpy(error.message, message);
    return error;
}

// Function to free an error
void free_error(Error error) {
    free(error.message);
}

// Function to interpret the AST with error handling
Error interpret_with_errors(ASTNode* root) {
    if (root == NULL) {
        return create_error(UNKNOWN_ERROR, "Empty AST");
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
            return create_error(UNKNOWN_ERROR, "Unknown node type");
    }

    // Recursively interpret child nodes
    Error left_error = interpret_with_errors(root->left);
    Error right_error = interpret_with_errors(root->right);

    // Combine errors (if any)
    if (left_error.code != NO_ERROR) {
        return left_error;
    } else if (right_error.code != NO_ERROR) {
        return right_error;
    }

    return create_error(NO_ERROR, "No error");
}

int main() {
    // Example AST (replace with your actual AST)
    ASTNode* root = create_node(ASSIGN_NODE, "=");
    root->left = create_node(IDENTIFIER_NODE, "x");
    root->right = create_node(NUMBER_NODE, "10");

    // Interpret the AST with error handling
    Error error = interpret_with_errors(root);

    // Print error message (if any)
    if (error.code != NO_ERROR) {
        printf("Error: %s\n", error.message);
    }

    // Free memory
    free_error(error);
    free_node(root);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NO_ERROR,
    ASSIGNMENT_ERROR,
    PRINT_ERROR,
    ADDITION_ERROR,
    NUMBER_ERROR,
    IDENTIFIER_ERROR,
    UNKNOWN_ERROR
} ErrorCode;

typedef struct {
    ErrorCode code;
    char *message;
} Error;

Error create_error(ErrorCode code, const char *message) {
    Error error;
    error.code = code;
    error.message = malloc(strlen(message) + 1);
    strcpy(error.message, message);
    return error;
}

void free_error(Error error) {
    free(error.message);
}

Error interpret_with_errors(ASTNode *root) {
    if (root == NULL) {
        return create_error(UNKNOWN_ERROR, "Empty AST");
    }

    switch (root->type) {
    case ASSIGN_NODE:
    case PRINT_NODE:
    case ADD_NODE:
    case NUMBER_NODE:
    case IDENTIFIER_NODE:
        break;
    default:
        return create_error(UNKNOWN_ERROR, "Unknown node type");
    }

    Error left_error = interpret_with_errors(root->left);
    Error right_error = interpret_with_errors(root->right);

    if (left_error.code != NO_ERROR) {
        return left_error;
    } else if (right_error.code != NO_ERROR) {
        return right_error;
    }

    return create_error(NO_ERROR, "No error");
}

int main() {
    ASTNode *root = create_node(ASSIGN_NODE, "=");
    root->left = create_node(IDENTIFIER_NODE, "x");
    root->right = create_node(NUMBER_NODE, "10");

    Error error = interpret_with_errors(root);

    if (error.code != NO_ERROR) {
        printf("Error: %s\n", error.message);
    }

    free_error(error);
    free_node(root);

    return 0;
}

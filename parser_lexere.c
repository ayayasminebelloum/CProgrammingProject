#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ID, IS, NUMBER, TEXT, ADD, SUB, MUL, DIV, PRINT, SEMICOLON, UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct Node {
    TokenType type;
    char *value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    char *name;
    int value;
} Variable;

Variable variables[26]; // Assuming variables are single letters

void initVariables() {
    for (int i = 0; i < 26; i++) {
        variables[i].name = NULL;
        variables[i].value = 0;
    }
}

Node *createNode(TokenType type, const char *value, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->type = type;
    node->value = strdup(value);
    node->left = left;
    node->right = right;
    return node;
}

void freeNode(Node *node) {
    if (node) {
        free(node->value);
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}

Variable *findVariable(char *name) {
    for (int i = 0; i < 26; i++) {
        if (variables[i].name != NULL && strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

void executeNode(Node *node) {
    if (node) {
        switch (node->type) {
            case NUMBER:
                printf("Result: %s\n", node->value);
                break;
            case ID:
                printf("Variable %s = %d\n", node->value, findVariable(node->value)->value);
                break;
            case IS: {
                Variable *var = findVariable(node->left->value);
                if (var == NULL) {
                    for (int i = 0; i < 26; i++) {
                        if (variables[i].name == NULL) {
                            variables[i].name = strdup(node->left->value);
                            var = &variables[i];
                            break;
                        }
                    }
                }
                executeNode(node->right);
                var->value = atoi(node->right->value);
                break;
            }
            case ADD:
                printf("Result: %d\n", atoi(node->left->value) + atoi(node->right->value));
                break;
            case SUB:
                printf("Result: %d\n", atoi(node->left->value) - atoi(node->right->value));
                break;
            case MUL:
                printf("Result: %d\n", atoi(node->left->value) * atoi(node->right->value));
                break;
            case DIV:
                printf("Result: %d\n", atoi(node->left->value) / atoi(node->right->value));
                break;
            case PRINT:
                executeNode(node->left);
                break;
            default:
                break;
        }
    }
}

int main() {
    const char *source = "x = 10; y = 5; result = x + y; print result;";

    Token tokens[] = {
        {ID, "x"}, {IS, "="}, {NUMBER, "10"}, {SEMICOLON, ";"}, 
        {ID, "y"}, {IS, "="}, {NUMBER, "5"}, {SEMICOLON, ";"}, 
        {ID, "result"}, {IS, "="}, {ID, "x"}, {ADD, "+"}, {ID, "y"}, {SEMICOLON, ";"}, 
        {PRINT, "print"}, {ID, "result"}, {SEMICOLON, ";"}
    };

    Node *program = createNode(UNKNOWN, "", NULL, NULL);
    Node *current = program;
    int i = 0;

    while (tokens[i].type != UNKNOWN) {
        Node *expression = createNode(tokens[i].type, tokens[i].value, NULL, NULL);
        i++;

        if (tokens[i].type == IS || tokens[i].type == ADD || tokens[i].type == SUB ||
            tokens[i].type == MUL || tokens[i].type == DIV || tokens[i].type == PRINT) {
            Node *operation = createNode(tokens[i].type, tokens[i].value, expression, NULL);
            current->right = operation;
            current = current->right;
            i++;
        } else {
            current->right = expression;
            current = current->right;
        }

        if (tokens[i].type == SEMICOLON) {
            i++;
        } else {
            break;
        }
    }

    initVariables();
    executeNode(program->right);

    freeNode(program);

    return 0;
}

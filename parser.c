#include <stdio.h>

typedef enum {
    ID,
    ASSIGN,
    NUMBER,
    SEMICOLON,
    UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

void parse_assignment(Token *tokens) {
    Token *current = tokens;

    while (current->type != UNKNOWN) {
        if (current->type == ID && current[1].type == ASSIGN && current[2].type == NUMBER && current[3].type == SEMICOLON) {
            printf("Assignment: %s = %s\n", current->value, current[2].value);
            current += 4; // Move to the next statement
        } else {
            printf("Invalid statement\n");
            break;
        }
    }
}

int main() {
    // Sample tokens (replace with your actual tokens)
    Token tokens[] = {
        {ID, "x"}, {ASSIGN, "="}, {NUMBER, "10"}, {SEMICOLON, ""},
        {ID, "y"}, {ASSIGN, "="}, {NUMBER, "5"}, {SEMICOLON, ""},
        {UNKNOWN, ""}
    };

    parse_assignment(tokens);

    return 0;
}

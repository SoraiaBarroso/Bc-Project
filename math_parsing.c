#include "my_bc.h"

/* Return an operator's precedence.  */
int operation_precedence(char operator) 
{
    switch (operator) {
        case REVERSE_SIGN:
            return 4;
        case MULTIPLY: case DIVIDE: case MODULO: 
            return 3;
        case ADD: case SUBTRACT: 
            return 2;
        case EMPTY: 
            return 0;
        default:
            return -1;
    }
}

/* Help decide whether or not stack should be popped.  */
bool ispop(int A, int B) {
    return operation_precedence(A) >= operation_precedence(B);
}


/* Condense sparse data for ease of use.  */
int* data_compactor(Token* token) 
{
    // Initialize:
    int token_count = token->token_count;
    int integer_count = 0;

    for (int i = 0; token_count--; ) {
        if (token->type[i++] == INTEGER_VALUE) {
            integer_count++;
        }
    }

    // Definitions:
    token_count = token->token_count;
    int* result = malloc((integer_count+1)*sizeof(int));
    int* compactor = result;
    *compactor++ = integer_count;

    for (int i = 0; token_count--; i++) {
        if (token->type[i] == INTEGER_VALUE) {
            *compactor++ = token->value[i];
        }
    }

    return result;
}

/* Parsing makes an expression out of lexemes.  */
expression_t* parse_token(Token* token) 
{
    char*   postfix = malloc(sizeof(char)*token->token_count);
    char*   stack   = malloc(sizeof(char)*token->token_count);
    int     index   = 0;
    char*   parsed  = token->type;

    // Shunting-yard:
    *stack++ = EMPTY;
    for (int i = 0; i++ < token->token_count; parsed++) {
        switch (*parsed) {
            case INTEGER_VALUE:
                    postfix[index++] = *parsed;
                    break;
            case OPEN_PARENTHESIS:
                    *stack++ = *parsed;
                    break;
            case CLOSE_PARENTHESIS:
                    while (*--stack != OPEN_PARENTHESIS) {
                        postfix[index++] = *stack;
                    }
                    break;
            default:
                    while (ispop(*--stack, *parsed) == true) {
                        postfix[index++] = *stack;
                    }
                    stack[1] = *parsed;
                    stack += 2;
                    break;
        }
    }

    while (*--stack != EMPTY) {
        postfix[index++] = *stack;
    }

    postfix[index] = '\0';
    free(stack);

    // Consolidate results:
    expression_t* expression = malloc(sizeof(expression_t));
    expression->formula      = postfix;
    expression->values       = data_compactor(token);
    return expression;
}

/* Print expression for error checkings.  */
void see_results(expression_t* exp) 
{
    // Print formula:
    printf("Solve ");

    for (int i = 0, j = 0; exp->formula[i] != '\0'; i++) {
        if (exp->formula[i] == 'N') {
            printf("%c", 'a'+j++);
        } else {
            printf("%c", exp->formula[i]); 
        }
    }

    // Print values:
    printf(", where ");

    switch (*exp->values) {
        case 1: printf("a is %d.\n", exp->values[1]); break; 
        case 2: printf("a, b is %d, %d.\n", exp->values[1], exp->values[2]); break; 
        default: 
            printf("a, b, ... is"); 
            int i = 1;
            for ( ; i < *exp->values; ) printf(" %d,", exp->values[i++]);
            printf(" %d.\n", exp->values[i]);
            break;
    }
}
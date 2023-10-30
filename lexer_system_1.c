#include "my_bc.h"

/* Help to filter away useless characters.  */
bool valid_op(char c) {
    return (c == '(' || c == ')') || 
    ((c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ));
}

/* STEP 1: cleaning and preparing input for lexical analysis.  */
char* input_preprocessing(char* input) 
{
    int     len   = 0;
    char*   copy  = NULL;
    int     index = 0;

    if (input == NULL || (len = my_strlen(input)) == 0) {
        report(ERN_USAGE);
        return NULL;
    }

    copy = malloc(len*sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (input[i] == ' ') {
            continue;
        } else if (isdigit(input[i]) || valid_op(input[i])) {
            copy[index++] = input[i];
        } else {
            report(ERN_UNKNOWN_LEX);
            return NULL;
        }
    }
    
    if (copy[index] = '\0', my_strlen(copy) == 0) {
        report(ERN_USAGE);
        return NULL;
    }
    return copy;
}

/* STEP 2: tokenize, splitting the input text into a sequence of tokens.  */
Token* tokenize(char *input, Token* tokens) {
    
    int ctn_token = 0, ctn = 0, length;
    char* new_token = malloc(sizeof(char) * 10);

    for (int i = 0; i < tokens->token_count; i++)
    {
        if (valid_op(input[i]) == true) {
            new_token[ctn] = input[i];
            ctn++;
        } else {
            length = 0;
            while(isdigit(input[i]) && input[i] != '\0') {
                new_token[ctn] = input[i];
                ctn++;
                i++;
                length++;
            }
            if (length > 9) {
                report(ERN_TOO_LONG);
                return NULL;
            }
            i--;
        }

        new_token[ctn] = '\0';
        my_strcpy(tokens->token[ctn_token], new_token);
        ctn_token++;

        new_token[0] = '\0';
        ctn = 0;
    }

    tokens->token_count = ctn_token;
    free(new_token);
    
    return tokens;
}

/* AUXILIARY of STEP 2: Count the number of tokens.  */
int count_token(char *input) 
{
    int index = 0, ctn = 0;

    while (input[index] != '\0') {
        ctn++;
        index++;
    }

    return ctn;
}

/* AUXILIARY of STEP 2: Allocate heap memories in Token struct.  */
Token* init_lexer(char *input)
{
    Token* tokens;
    tokens = malloc(sizeof(Token));
    tokens->token_count = count_token(input);
    tokens->token = malloc(tokens->token_count*sizeof(char*));
    tokens->type  = malloc(tokens->token_count*sizeof(int));
    tokens->value = malloc(tokens->token_count*sizeof(int));

    for (int i = 0; i < tokens->token_count; i++) {
        tokens->token[i] = (char *)malloc(tokens->token_count * sizeof(char));

        if(tokens->token[i] == NULL) {
            report(ERN_MALLOC);
            return NULL;
        }
    }

    return tokens;
}

/* AUXILIARY of STEP 2: Free all heap memories in Token struct.  */
void free_lexer(Token* tokens) 
{
    for (int i = 0; i < tokens->token_count; i++) {
        free(tokens->token[i]);
    }
    
    free(tokens->type);
    free(tokens->value);
    free(tokens);
}
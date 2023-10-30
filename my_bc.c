#include "my_bc.h"

/* Produce error-proof tokens out of a text.  */
Token *lexical_analysis(char* input)
{
    Token *tokens;
    char *cleaned_input;

    /* Process the input */
    cleaned_input = input_preprocessing(input);
    if (cleaned_input == NULL) {
        return NULL;
    } 

    /* Initialize the token structure */
    tokens = init_lexer(cleaned_input);
    if (tokens == NULL) {
        return NULL;
    }

    /* Tokenize the input */
    tokens = tokenize(cleaned_input, tokens);
    if (tokens == NULL) {
        return NULL;
    }
    tokens = get_token_type(tokens);

    /* Catch errors in the tokens */
    if (err_handler(tokens) == -1) {
        return NULL;
    }

    return tokens;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        report(ERN_USAGE);
        return EXIT_FAILURE;
    } else {
        /* (A) lexical analysis:  */
        Token *tokens = NULL;

        if ((tokens = lexical_analysis(argv[1])) == NULL) {
            return EXIT_FAILURE;
        }

        // See result: for (int i = 0; i < tokens->token_count; i++) {printf("token: %s type: %c value %d\n", tokens->token[i], tokens->type[i], tokens->value[i]);}

        /* (B & C) parsing & evaluation:  */
        expression_t* exp = parse_token(tokens);

        // See result: see_results(a);
        if (evaluate_expression(exp) == -1) {
            return EXIT_FAILURE;
        }

        // Clean up allocated memory
        free_lexer(tokens);
        free(exp);
    }
  
    return EXIT_SUCCESS;
}
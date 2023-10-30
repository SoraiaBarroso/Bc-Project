#ifndef MY_BC_H_
#define MY_BC_H_

/* Header files.  */
#include <stdlib.h> // malloc(), free()
#include <unistd.h> // write()
#include <stdio.h>  // printf()
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 

/* Error definitions.  */
#define SUCCESS             0
#define ERN_MALLOC          1
#define ERN_USAGE           3
#define ERN_UNKNOWN_LEX     2
#define ERN_SYNTAX          4
#define ERN_PARENTHESIS     5
#define ERN_DIVIDED_ZERO    6
#define ERN_TOO_LONG        7

#define ERR_MALLOC          "Error: Memory allocation failed\n"
#define ERR_USAGE           "Error: Usage: ./my_bc \"[operation]\"'\n"
#define ERR_UNKNOWN_LEX     "Parse Error: unknown lexeme\n"  // "1+bonjour"
#define ERR_SYNTAX          "Parse Error: syntax\n"
#define ERR_PARENTHESIS     "Parse Error: improper parenthesis\n"
#define ERR_DIVIDED_ZERO    "Math Error: Divide by zero\n"
#define ERR_TOO_LONG        "Error: a number was too large\n"

/* Categorical values of token types.  */
typedef enum {
    EMPTY               = '\0',    
    ADD                 = '+',
    SUBTRACT            = '-',
    MULTIPLY            = '*',
    DIVIDE              = '/',
    MODULO              = '%',
    REVERSE_SIGN        = '~',
    INTEGER_VALUE       = 'N',
    OPEN_PARENTHESIS    = '(',
    CLOSE_PARENTHESIS   = ')',
} TokenType;

/* Structs.  */
typedef struct {
    char    *type;
    char    **token;
    int     *value;
    int     token_count;
} Token;

typedef struct {
    char*   formula;
    int*    values;
} expression_t;

/* Function declarations.  */

/* Under lexer_system.c:  */
Token*  init_lexer          (char *input);
void    free_lexer          (Token* tokens);
char*   input_preprocessing (char* input);
char    *str_malloc         (char *src);
int     collapse_signs      (Token* tokens, int position);
Token*  tokenize            (char *input, Token* tokens);
Token*  get_token_type      (Token* tokens);

/* Under error_management.c:  */ 
int     report      (int status);
bool    isoperator  (int N);
bool    valid_op    (char c);
int     count_token (char *input);
int     err_handler (Token* tokens);
bool    consec_op   (int n);
size_t  my_strlen   (const char *str);
char*   my_strcpy   (char *dest, const char *src);

/* Under parsing.c:  */
expression_t*   parse_token          (Token* token);
void            see_results          (expression_t* exp);
int             operation_precedence (char operator_type);
int*            data_compactor       (Token* token);

/* Under evaluation.c:  */
int     evaluate_expression (expression_t* exp);

#endif
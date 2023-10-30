#include "my_bc.h"

/* Simplify status message reporting.  */
int report(int status)
{
    char *message = "unknown error";
    switch (status)
    {
        case SUCCESS:
            return 0;
        case ERN_SYNTAX:
            message = ERR_SYNTAX;
            break;
        case ERN_PARENTHESIS:
            message = ERR_PARENTHESIS;
            break;
        case ERN_DIVIDED_ZERO:
            message = ERR_DIVIDED_ZERO;
            break;
        case ERN_MALLOC:
            message = ERR_MALLOC;
            break;
        case ERN_USAGE:
            message = ERR_USAGE;
            break;
        case ERN_UNKNOWN_LEX:
            message = ERR_UNKNOWN_LEX;
            break;
        case ERN_TOO_LONG:
            message = ERR_TOO_LONG;
            break;
    }

    write(2, message, my_strlen(message));
    return -1;
}

/* Return true if among the five operators.  */
bool isoperator(int N)
{
    return (N == ADD || N == SUBTRACT) ||
           (N == MULTIPLY || N == DIVIDE || N == MODULO);
}

/* Categories of parse errors, explained:
    1. ERR_PARENTHESIS:
        (A) none
        (B) overclosed ")", or hastily closed = ()"
        (C) unclosed "("
    2. ERR_SYNTAX:
        (A) adjacent integers/equivalent = "NN", ")N"
        (B) bad leftside: of close = "*), of operator = "\0*", "(+", "+*"
        (C) bad rightside: of operator = "N+"
*/

/* Catch all categories of parse error.  */
int err_handler(Token *tokens)
{
    int unclosed_parenthesis = 0;
    char leftside = EMPTY;

    for (int i = 0; i < tokens->token_count; leftside = tokens->type[i++])
    {
        switch (tokens->type[i])
        {
            // Part A
            case OPEN_PARENTHESIS:
                unclosed_parenthesis++;
                // fallthrough
            case INTEGER_VALUE:
                if (leftside == INTEGER_VALUE || leftside == CLOSE_PARENTHESIS)
                {
                    return report(ERN_SYNTAX);
                }
                break;

            // Part B
            case CLOSE_PARENTHESIS:
                if (--unclosed_parenthesis < 0 || leftside == OPEN_PARENTHESIS)
                {
                    return report(ERN_PARENTHESIS);
                }
                // fallthrough
            case ADD:
            case SUBTRACT:
            case MULTIPLY:
            case MODULO:
            case DIVIDE:
                if (isoperator(leftside) || leftside == EMPTY ||
                    leftside == OPEN_PARENTHESIS)
                {
                    return report(ERN_SYNTAX);
                }
                break;
        }
    }

    // Part C
    if (unclosed_parenthesis > 0)
    {
        return report(ERN_PARENTHESIS);
    }
    if (isoperator(tokens->type[tokens->token_count - 1]))
    {
        return report(ERN_SYNTAX);
    }

    return SUCCESS;
}

size_t my_strlen(const char *str)
{
    size_t len = 0;

    while (*str != '\0')
    {
        len++;
        str++;
    }

    return len;
}

char *my_strcpy(char *dest, const char *src)
{
    if (dest == NULL) return NULL;

    char *ptr = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return ptr;
}
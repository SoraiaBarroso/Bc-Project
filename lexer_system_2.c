#include "my_bc.h"

int my_atoi(char* a) {
    if (*a != '-') {
        int i = 0;
        while (*a) i = (i*10)+(*(a++)-'0');
        return i;
    }
    return -my_atoi(++a);
}

/* AUXILIARY of STEP 3: distinguish ADD, SUBTRACT from positive, negative signs.  */
int collapse_signs(Token* tokens, int position) 
{
    
    if (position == 0) return position;
    int     save         = position;
    bool    reverse_sign = false;
    char*   type         = tokens->type;

    // Get Sign: parse backward until signs has been collapsed, and +/- is determined.
    for (bool stoploop = false; !stoploop && --position >= 0; )
    {
        switch (type[position]) {
            case SUBTRACT:
                    reverse_sign = !reverse_sign;
                    // fallthrough
            case ADD:
                    continue;

            case CLOSE_PARENTHESIS:
            case INTEGER_VALUE:
                    if (type[++position] == SUBTRACT) {
                        reverse_sign = !reverse_sign;
                    }
                    // fallthrough
            default:
                    stoploop = true;
                    break;
        }
    }
    if (++position == save) return position;


    // Apply or Engrave: with the +/- determined, apply them to the integer or engrave them as special character '~'
    if (reverse_sign == true)
    {
        switch (tokens->type[save])
        {
            case 'N':
                    tokens->value[save] *= -1;
                    break;
            case '(':
                    *tokens->token[position] = '~';
                    tokens->type[position]   = '~';
                    tokens->value[position]  = 0;
                    position++;
                    break;
        }
    }


    // Pullback: With the signs collapsed, the rest of the tokens needs to be pullbacked too.
    tokens->token_count -= (save-position);
    tokens->type[position] = tokens->type[save];
    tokens->value[position] = tokens->value[save];
    for (int dest = position; ++dest < tokens->token_count; )
    {
        tokens->token[dest] = tokens->token[++save];
    }
    return position;
}

/* STEP 3: Token classification.  */
Token* get_token_type(Token* tokens) 
{
    int index = 0;

    for (int i = 0; i < tokens->token_count; i++, index++) {
        switch (tokens->token[i][0]) {
            case '(':
                    tokens->type[index] = OPEN_PARENTHESIS;
                    i = index = collapse_signs(tokens, i);
                    break;
            case ')':
                    tokens->type[index] = CLOSE_PARENTHESIS;
                    break;
            case '+':
                    tokens->type[index] = ADD;
                    break;
            case '-':
                    tokens->type[index] = SUBTRACT;
                    break;
            case '*':
                    tokens->type[index] = MULTIPLY;
                    break;
            case '/':
                    tokens->type[index] = DIVIDE;
                    break;
            case '%':
                    tokens->type[index] = MODULO;
                    break;
            default:
                    if (isdigit(tokens->token[i][0])) 
                    {
                        tokens->type[index] = INTEGER_VALUE;
                        tokens->value[index] = my_atoi(tokens->token[i]);
                        i = index = collapse_signs(tokens, i);
                    }
                    break;
        }
    }

    return tokens;
};
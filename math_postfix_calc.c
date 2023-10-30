#include "my_bc.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

/* Check if the two values are going to cause integer underflow or overflow.  */ 
bool err_check_too_long(int op, int l, int r)
{
    switch (op)
    {
        case ADD:
            return ((r > 0) && (l > INT_MAX - r))
                    || ((r < 0) && (l < INT_MIN - r));
        case SUBTRACT:
            return (((r < 0) && (l > INT_MAX + r))
                    || ((r > 0) && (l < INT_MIN + r)));
        case MULTIPLY:
            if (l < 0) l *= -1;
            if (r < 0) r *= -1;
            return ((r != 0) && (((l > (INT_MAX / r)))
                    || ((l < (INT_MIN / r)))));
        case DIVIDE:
            return ((r == -1) && (l == INT_MIN));
    }
    return false;
}

/* Evaluate the operation using the given leftside and rightside value.  */ 
int evaluate(int op, int l, int r)
{
    switch (op)
    {
        case ADD:
            return l+r;
        case SUBTRACT:
            return l-r;
        case MULTIPLY:
            return l*r;
        case DIVIDE:
            return l/r;
        case MODULO:
            return l%r;
    }
    return 0;
}

/* Evaluate expression using the given formula and values.  */ 
int evaluate_expression(expression_t* exp) 
{
    int* indice = malloc((*exp->values - 1)*sizeof(int));
    int latest_index = 1;
    int i = -1;
    int l, r;

    for (char* equation = exp->formula; *equation != EMPTY; equation++) 
    {
        l = exp->values[indice[i-1]];
        r = exp->values[indice[i]];

        /* Since it's troublesome to adjust the value array {n1, n2, n3},
            we instead use an index list of {to n1, to n2, to n4...}:
                every integer grows the list, every operator shrinks the list,
                when n2 and n3 are evaluated together, the output is saved in n2,
                and 'to n3' will soon be replaced by 'to n4' (if any was later found). */
        switch (*equation) {
            case INTEGER_VALUE:
                indice[++i] = latest_index++;
                break;
            case REVERSE_SIGN:
                exp->values[indice[i]] *= -1;
                break;

            case DIVIDE:
            case MODULO:
                if (r == 0) {
                    return report(ERN_DIVIDED_ZERO);
                }
                // fallthrough
            case ADD:
            case SUBTRACT:
            case MULTIPLY:
                if (err_check_too_long(*equation, l, r)) {
                    return report(ERN_TOO_LONG);
                }
                exp->values[indice[--i]] = evaluate(*equation, l, r);
                break;
        }
        // See Process:
        // printf("(%c: %d)", *parser, exp->values[indice[i]]); 
    }

    printf("%d\n", exp->values[*indice]);
    return SUCCESS;
}
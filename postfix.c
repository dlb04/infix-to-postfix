#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

#define STACK_SIZE 128
#define unreacheable() \
    do {\
        fprintf(stderr, "%s:%s:%d\n", \
            __FILE__, __FUNCTION__, __LINE__); \
        exit(1); \
    } while (0)

typedef uint8_t u8;
typedef struct Stack Stack;

struct Stack {
    u8 *array;
    size_t size;
    size_t stackptr;
};

/**
 * Prints contents of stack, used only for debugging purposes.
 */
static void
__peek_stack_contents(Stack *s){
    printf("[");
    for (size_t i = 0; i < s->stackptr; ++i)
        printf("%c ", s->array[i]);
    printf("]\n");
}

static int
push(Stack *sp, u8 i){
    if (sp->stackptr >= sp->size - 1)
        return -1;
    sp->array[sp->stackptr++] = i;
    return 0;
}

static int
pop(Stack *sp, u8 *p){
    if(sp->stackptr == 0)
        return -1;
    *p = sp->array[--sp->stackptr];
    return 0;
}

static inline int
is_operator(int c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

static int
create_stack(size_t size, Stack **sp){
    Stack *s = malloc(sizeof(*s));
    if (!s)
        return -1;
    if (!(s->array = malloc(size))){
        free(s);
        return -1;
    }
    
    s->size = size;
    s->stackptr = 0;
    *sp = s;
    return 0;
}

static void
destroy_stack(Stack **s){
    free((*s)->array);
    free(*s);
    *s = NULL;
}

/**
 * Pseudocode for the infix to postfix algorithm:
 * infix_to_postfix (I :: String):
 *     P :: String
 * 
 *     for c in I 
 *         if c is Operator:
 *             Pop from stack until an operator with less precedence
 *              is found or a Left Parenthesis is found.
 *             Push the new Operator.
 *      
 *         else if c is left Parenthesis:
 *             Push c to stack
 * 
 *         else if c is Right Parenthesis
 *             Pop and append until Left Parenthesis is found.
 *             Pop Left Parenthesis from stack (dont append to string).
 *         else
 *             Append to P.
 * 
 *     Pop everything in the stack and append to P.
 *     return P.
 */
char *
infix_to_postfix(const char *inf, size_t len){
    Stack *postfix, *operators;
    if (create_stack(len + 1, &postfix) || create_stack(len, &operators))
        return NULL;

    static const int precedences[256] = {
        ['+'] = 1,          ['-'] = 1,
        ['*'] = 2,          ['/'] = 2,
        ['('] = INT_MIN,    [')'] = INT_MIN,
    };
    
    for(;*inf; ++inf){

        if (is_operator(*inf)){
            u8 i;
            while (!pop(operators, &i)){
                if (precedences[i] < precedences[(int)*inf]){
                    push(operators, i);
                    break;
                }
                push(postfix, i);
            }
            push(operators, *inf);
        }
        else if (*inf == '('){
            push(operators, *inf);
        }
        else if (*inf == ')'){
            u8 i;
            while (!pop(operators, &i)){
                if (i == '(')
                    break;
            push(postfix, i);
            }
        }
        else {
            push(postfix, *inf);
        }
    }

    char *s = (char *)postfix->array;
    u8 i;
    while (!pop(operators, &i)){
        push(postfix, i);
    }
    push(postfix, 0);
    free(postfix);
    destroy_stack(&operators);
    return s;
}
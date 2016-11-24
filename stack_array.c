#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>
typedef struct _stack
{
    int* data;
    int top;
    int r_size;
}stack;
void stack_create(stack* Stack)
{
    Stack->top = -1;
    Stack->r_size = 10;
    Stack->data = (int*)calloc(Stack->r_size, sizeof(int));
    return;
}
bool stack_is_empty(stack* Stack)
{
    if(Stack->top < 0)
        return true;
    return false;
}
int stack_top(stack* Stack)
{
    if(!stack_is_empty(Stack))
        return Stack->data[Stack->top];
    return -1;
}
int stack_pop(stack* Stack)
{
    int r = stack_top(Stack);
    if(r >= 0)
        Stack->top--;
    return r;
}
void stack_push(stack* Stack, int n)
{
    Stack->top++;
    if(Stack->top >= Stack->r_size)
    {
        Stack->r_size *= 2;
        Stack->data = (int*)realloc(Stack->data, Stack->r_size*sizeof(int));
    }
    Stack->data[Stack->top] = n;
    return;
}
void stack_destroy(stack* Stack)
{
    Stack->top = -1;
    Stack->r_size = 0;
    free(Stack->data);
    return;
}

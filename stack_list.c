#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>
typedef struct _node node;
typedef struct _node
{
    int val;
    node* next;
}node;
typedef struct _stack
{
    node* head;
    int size;
}stack;
void stack_create(stack* Stack)
{
    Stack->head = NULL;
    Stack->size = 0;
    return;
}
bool stack_is_empty(stack* Stack)
{
    return !Stack->size;
}
int stack_top(stack* Stack)
{
    if(!stack_is_empty(Stack))
        return Stack->head->val;
    return -1;
}
int stack_pop(stack* Stack)
{
    int r = stack_top(Stack);
    if(r >= 0)
    {
        node* tmp = Stack->head;
        Stack->head = Stack->head->next;
        free(tmp);
        Stack->size--;
    }
    return r;
}
void stack_push(stack* Stack, int n)
{
    node* new_n = (node*)malloc(sizeof(node));
    new_n->val = n;
    if(!stack_is_empty(Stack))
        new_n->next = Stack->head;
    Stack->head = new_n;
    Stack->size++;
    return;
}
void stack_destroy(stack* Stack)
{
    int t;
    while(!stack_is_empty(Stack))
        t = stack_pop(Stack);
    return;
}

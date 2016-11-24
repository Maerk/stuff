#ifndef _STACK_H_
#define _STACK_H_
#include <stdbool.h>

typedef struct _stack stack;
void stack_create(stack* Stack);
void stack_destroy(stack* Stack);
bool stack_is_empty(stack* Stack);
int stack_top(stack* Stack);
int stack_pop(stack* Stack);
void stack_push(stack* Stack, int n);

#endif //_STACK_H_

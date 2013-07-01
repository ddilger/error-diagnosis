/* Implementation of a Stack in C */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "linkedlist.h"

typedef List Stack;

#define stack_init list_init;

#define stack_destroy list_destroy

int stack_push(Stack *stack, const void *data);

int stack_pop(Stack *stack, void **data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

#define stack_size list_size

#endif



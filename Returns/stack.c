/* Implementation of stacks in C */

#include <stdlib.h>

#include "linkedlist.h"
#include "stack.h"
#include "linkedlist.c"

int stack_push(Stack *stack, const void *data)
{
  /* By design of list_ins_next, a 2nd arg of NULL means data's added
   to the beginning of the list*/
  return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data)
{
  /* I'm not sure what list_rem_next does with data */
  return list_rem_next(stack, NULL, data);
}

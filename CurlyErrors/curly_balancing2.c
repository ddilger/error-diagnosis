/* balances parentheses using a stack */

#include <stdio.h>
#include "stack.h"
#include "stack.c"

enum token{NONE, OPEN='{', CLOSE='}', END};

char open_tok = OPEN;

FILE *fid;
Stack s;
Stack *stack;
char curToken;

char readToken()
{
  char curChar;
  while(1)
    {
      curChar = getc(fid);
      if(curChar == EOF || curChar == '\0')
	return END;
      if(curChar == '{')
	return OPEN;
      if(curChar == '}')
	return CLOSE;
  /* eat "whitespace" -- anything other than predefined tokens */
    }
}

int balance()
{
  char c = 'c';
  char *ptr1 = &c;
  char **data = &ptr1;

  do
    {
      if(curToken == OPEN)
	stack_push(stack, &open_tok);
      if(curToken == CLOSE)
	if(stack_pop(stack, (void **) data) == -1)
	  return 0;
      curToken = readToken();
    } while(curToken != END);
  if(stack->size == 0)
    return 1;
  return 0;
}


int main(int argc, char *argv[])
{
  /* Why does the macro give me a "statement with no effect" error? */
  stack = &s;
  list_init(stack, NULL);
  if((fid = fopen(argv[1], "r")) == NULL)
    return -1;
  curToken = readToken();
  int i = balance();
  if(i)
    {
      printf("The braces are balanced\n");
    }
  else
    {
      printf("The braces are unbalanced\n");
    }
  fclose(fid);
  return 0;
}

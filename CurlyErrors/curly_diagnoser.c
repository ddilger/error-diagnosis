/*Diagnoses causes of curly brace errors*/

#include <stdio.h>
#include "stack.h"
#include "stack.c"

enum tokens{
  NONE=0, BLOCK_START=1, OPEN_CURLY=2,
  CLOSE_CURLY=3, NEWLINE=4, ARRAY_START=5,
  END=6
};

enum errors{
  EXCESS_CLOSE,
  EXCESS_OPEN,
  LACKS_CLOSE
};


typedef struct StackElm
{
  int lineNum;
  int token;
} StackElm;


FILE *fid;

Stack s;
Stack *stack;

int curTok;
int curLine=1;
int errorNum=0;

/*Data needs to point to StackElm structs (or their pointers)*/
StackElm c;
StackElm *ptr1 = &c;
StackElm **stackdata = &ptr1;

void readToken()
{
  fscanf(fid, "%i", &curTok);
}

void error(int msg)
{
  switch(msg)
    {
    case EXCESS_CLOSE:
      printf("Excess close token encountered at line %i\n", (*stackdata)->lineNum);
      break;
    case EXCESS_OPEN:
      printf("Excess open token encountered at line %i\n", (*stackdata)->lineNum);
      break;
    case LACKS_CLOSE:
      printf("Missing close token at line %i\n", (*stackdata)->lineNum);
      break;
    }
}

int diagnose()
{

  do
    {
      if(curTok ==  CLOSE_CURLY)
	{
	 if(stack->size > 0 && stack_pop(stack, (void **) stackdata) == -1)
	   return -1;
	 /* If it popped and found something other than an open curly,
	  or it couldn't pop because stack was empty, then an excess close
	 has been encountered*/
	 if((*stackdata)->token != OPEN_CURLY)
	   {
	     error(EXCESS_CLOSE);
	     errorNum++;
	   }
	 /* Else means it's seen an open curly, now looking for block start */
	 else
	   {
	     if(stack_pop(stack, (void **) stackdata) == -1)
	       return -1;
	     if((*stackdata)->token != BLOCK_START && (*stackdata)->token != ARRAY_START)
	       {
		 error(EXCESS_OPEN);
		 /* Pop the block start off the stack */
		 /* If there wasn't a block start this can cause problems*/
		 if((*stackdata)->token == OPEN_CURLY)
		   if(stack_pop(stack, (void **) stackdata) == -1)
		     return -1;
		 errorNum++;
	       }
	   }
	}
      else if(curTok == NEWLINE)
	{
	  curLine++;
	}
      else
	{
	  StackElm *elm = (StackElm *) malloc(sizeof(StackElm));
	  elm->lineNum = curLine;
	  elm->token = curTok;
	  stack_push(stack, elm);
	}
      readToken();
    } while(curTok != END);
  if(stack->size == 0)
    return 0;
  error(LACKS_CLOSE);
  errorNum++;
  /* Print out all block_starts (and array_starts?) on stack */
  printf("Possible unclosed blocks: \n");
  while(stack->size > 0)
    {
      if(stack_pop(stack, (void **) stackdata) == -1)
	return -1;
      if((*stackdata)->token == BLOCK_START)
	printf("line %i\n", (*stackdata)->lineNum);
    }
  /* Print a suggested area */
  return 0;
}

int main(int argc, char *argv[])
{
  /* Open file */
  if((fid = fopen(argv[1], "r")) == NULL)
    return -1;
  /* Run diagnosis process */
  stack = &s;
  list_init(stack, NULL);
  readToken();
  if(diagnose() == -1)
    printf("The diagnosis program crashed\n");
  else if (errorNum == 0)
    printf("The diagnosis program couldn't find any errors\n");
  return 0;
}



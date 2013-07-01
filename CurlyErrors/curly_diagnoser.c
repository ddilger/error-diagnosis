/*Diagnoses causes of curly brace errors*/

/* I might want to make (*stackdata)->token a macro */

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
  LACKS_CLOSE,
  LACKS_OPEN
};


typedef struct StackElm
{
  int lineNum;
  int token;
} StackElm;


FILE *fid;

Stack s;
Stack *stack;

List l;
List *bList;

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
      if ((*stackdata)->lineNum == 0)
	{
	  /* The excess close happened at the end of the file, 
	   the cause is unknown*/
	  printf("Missing close token in the file\n");
	}
      else
	{
	  printf("Excess close token encountered at line %i\n", (*stackdata)->lineNum);
	}
      break;
    case EXCESS_OPEN:
      printf("Excess open token encountered at line %i\n", (*stackdata)->lineNum);
      break;
    case LACKS_CLOSE:
      printf("Missing close token at line %i\n", (*stackdata)->lineNum);
      break;
    case LACKS_OPEN:
      printf("Missing open token at line %i\n", (*stackdata)->lineNum);
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
	 /* To prevent stackdata from persisting after the final pop*/
	 if(stack->size == 0)
	   {
	     (*stackdata)->token = NONE;
	     (*stackdata)->lineNum = 0;
	   }
	 /* If it popped and found something other than an open curly,
	  or it couldn't pop because stack was empty, then an excess close
	 has been encountered*/
	 if((*stackdata)->token != OPEN_CURLY)
	   {
	     if((*stackdata)->token == BLOCK_START || (*stackdata)->token == ARRAY_START)
	       {
		 error(LACKS_OPEN);
	       }
	     else
	       {
		 error(EXCESS_CLOSE);
	       }
	     errorNum++;
	   }
	 /* Else means it's seen an open curly, now looking for block start */
	 else
	   {
	     if(stack_pop(stack, (void **) stackdata) == -1)
	       return -1;
	     if((*stackdata)->token != BLOCK_START && (*stackdata)->token != ARRAY_START)
	     /* Why not just this? */
	     /* if((*stackdata)->token == OPEN_CURLY) */
	       {
		 error(EXCESS_OPEN);
		 /* This will only work when there are exactly two open curlies... */
		 /* Pop the block start off the stack */
		 /* If there wasn't a block start this can cause problems*/
		 /* Add a while loop to keep eating excess opens? */
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

	  if(curTok == BLOCK_START || curTok == ARRAY_START)
	    {
	      list_ins_end(bList, elm);
	    }
	}
      readToken();
    } while(curTok != END);
  if(stack->size == 0)
    return 0;
  /* Doesn't account for multiple blocks lacking closure at the end */
  error(LACKS_CLOSE);
  errorNum++;
  /* Print out all block_starts (and array_starts?) on stack */
  printf("Possible unclosed blocks: \n");
  /*
  while(stack->size > 0)
    {
      if(stack_pop(stack, (void **) stackdata) == -1)
	return -1;
      if((*stackdata)->token == BLOCK_START)
	printf("line %i\n", (*stackdata)->lineNum);
    
  }
  */

  /* More accuracy could be had with tab information */
  ListElmt *e;
  for(e=list_head(bList); e != NULL; e=e->next)
    {
      StackElm *se = (StackElm *) e->data;
      /* Can't terminate a block that starts after the element in question */
      if(se->lineNum > (*stackdata)->lineNum)
	break;
      printf("line %i\n", se->lineNum);

    }
  /* Print a suggested area */
  return 0;
}

int main(int argc, char *argv[])
{
  /* Open file */
  if((fid = fopen(argv[1], "r")) == NULL)
    {
      printf("The diagnosis program could not open the read file\n");
      return -1;
    }
  /* Run diagnosis process */
  stack = &s;
  list_init(stack, NULL);

  bList = &l;
  list_init(bList, NULL);

  readToken();
  if(diagnose() == -1)
    printf("The diagnosis program crashed\n");
  else if (errorNum == 0)
    printf("The diagnosis program couldn't find any errors\n");
  return 0;
}



#include <stdio.h>
#include "return_header.h"

/* Consider putting the grammar and lookup table in a header */

/* How are NONEs (epsilons) accounted for in a predictive parser?
 By the lookup table? or by a special "backtracking" function? */

/* CFG for terminating methods:
   METHOD ::= VOID_METHOD_START OPENTOK CONTENTS CLOSETOK
   METHOD ::= METHOD_START OPENTOK CONTENTS RETURN CLOSETOK
   CONTENTS ::= (IFLADDER |SWITCH | TERMLOOP ) CONTENTS | NONE
   IFLADDER ::= IF ELSEIFS ELSE
   ELSEIFS ::= ELSEIF ELSEIFS | None
   ELSE ::= ELSE_START | NONE
   IF ::= IF_START OPENTOK CONTENTS CLOSETOK
   ELSEIF ::= ELSEIF_START OPENTOK CONTENTS CLOSETOK
   ELSE ::= ELSE_START OPENTOK CONTENTS CLOSETOK
   SWITCH ::= SWITCH_START OPENTOK CASES DEFAULT CLOSETOK
   CASES ::= CASE CASES | NONE
   DEFAULT ::= DEFAULT_START RETURN
   TERMLOOP ::= FORTERM OPENTOK CONTENTS CLOSETOK
 */

FILE *fid;

Element ee;
Element me;

int end = END;
int method = METHOD;

Element *endElm;
Element *methodElm;

Stack s;
Stack *stack;

int top;

/* Error gives a report on a possible cause of the error */
void error(int top, int e)
{
  switch(e)
    {
    case CLOSETOK:
      printf("Missing return statement");
      break;
    }
}

/* Return 0 if not a terminal */
int isterminal(int X)
{
  switch(X)
    {
    case NONE:
    case IF_START:
    case ELSEIF_START:
    case ELSE_START:
    case SWITCH_START:
    case CASE:
    case DEFAULT:
    case METHOD_START:
    case VOID_METHOD_START:
    case WHILE_START:
    case FOR_START:
    case FORTERM_START:
    case NEWLINE:
    case OPENTOK: 
    case CLOSETOK:
    case  RETURN:
    case END:
      return 1;
    default: 
      return 0;
    }
}

/* Given a grammar construct, returns either that that construct is a terminal,
or performs the pushing actions needed for a nonterminal*/
int lookup(int X, int a)
{
  /* How to safely access these? */
  if(table[X][a] == NULL)
    {
      return 0;
    }
  /* Push the contents of M[X, a] onto the stack */
  Production *p = table[X][a];
  Element *l;
  for(l=p->head; l != NULL; l=l->next)
    {
      stack_push(stack, l);
    }
}

/* Return 1 for a valid sentence, 0 otherwise */
int stack_parser()
{
  /* Push the end of input to the bottom of stack */
  stack_push(stack, endElm);
  /* Push method onto the stack, to be validated*/
  stack_push(stack, methodElm);

  /* Go top-down through productions until end or an error */
  while(top != END)
    {
      top = *((int *) stack->head->data);
      if(isterminal(top))
	{
	  if(top == curTok)
	    {
	      stack_pop(stack, data);
	      readToken();
	    }
	  else
	    {
	      /* Diagnose why the error ocurred here */
	      error(top, curTok);
	      return 0;
	    }
	}
      else
	{
	  if(lookup(top, curTok))
	    {
	      stack_pop(stack, data);
	      /* No output for simple validation */
	    }
	  else
	    {
	      /* Diagnose why the error ocurred here */
	      error(top, curTok);
	      return 0;
	    }
	}
    }
}

int main(int argc, char *argv[])
{
  /* Open file */
  if((fid = fopen(argv[1], "r")) == NULL)
    return -1;
  /* Initialize the lookup table */
  int i,j;
  for(i=0; i<LENGTH; i++)
      for(j=0; j<WIDTH; j++)
	  table[i][j] = NULL;
  tableInit();
  /* Run diagnosis process */
  stack = &s;
  endElm = &ee;
  endElm->data = &end;
  methodElm = &me;
  methodElm->data = &method;
  list_init(stack, NULL);
  readToken();
  if(diagnose() == -1)
    printf("The diagnosis program crashed\n");
  else if (errorNum == 0)
    printf("The diagnosis program couldn't find any errors\n");
  return 0;
}

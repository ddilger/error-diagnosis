/* Any stylistic improvements I note here can be used in a CFG remake
of the curly error program */
#include <stdio.h>
#include "return_header.h"

#define nextTok(index) tokens[index = readTok(index)]

typedef enum ErrorType{
  MALFORMED,
  NO_RETURN,
  NO_DEFAULT

} ErrorType;

/* Two more stumbling blocks:
   error throws with enums
   reading multiple methods in a file (and multiple error reports)
 */

/* Have a global variable that remembers the last place where 0 was returned,
for ease of error reporting. */

/* CFG for terminating methods:
   METHOD ::= VOID_METHOD_START OPENTOK CONTENTS CLOSETOK
   METHOD ::= METHOD_START OPENTOK CONTENTS RETURN CLOSETOK
   CONTENTS ::= (IFLADDER |SWITCH | TERMLOOP ) CONTENTS | NONE
   IFLADDER ::= IF ELSEIFS ELSE
   ELSEIFS ::= ELSEIF ELSEIFS | None
   ELSE ::= ELSE_START | NONE
   IF ::= IF_START OPENTOK CONTENTS CLOSETOK
   ELSEIF ::= ELSEIF_START OPENTOK CONTENTS CLOSETOK
   ELSE ::= ELSE_START OPENTOK CONTENTS CLOSETOK | None
   SWITCH ::= SWITCH_START OPENTOK CASES DEFAULT CLOSETOK
   CASES ::= CASE CASES | NONE
   DEFAULT ::= DEFAULT_START RETURN
   TERMLOOP ::= FORTERM OPENTOK CONTENTS CLOSETOK
 */

/* This grammar won't check to see if returns are handled by the if ladder or switch */
/* Maybe the chain-based approach would be better? */
/* Another option: add some semantic actions within some production's functions.
 These actions would maintain a chain. A new chain would be maintained within recursive levels,
and would "collapse" into one link in the chain at the higher level, with the proper coloring
(return or no)*/

FILE *fid;
int tokens[1000];

/* curLine necessitates a more complicated read-and-push back function */
int curLine = 0;

Nonterminal errorTok = NONE;
ErrorType errorType;
int errorLine = 0;
int errorNum = 0;

int readTok(int index)
{
  while(1)
    {
      index++;
      /* There's a serious problem with terminating the program where needed */
      if(tokens[index]==END)
	{
	  printf("The diagnosis program crashed (reached end of file)\n");
	  /*
	  int i;
	  for(i=0; i<1000; i++)
	    tokens[i] = 0;
	  */
	  return -1;
	}
      if(tokens[index]!=NEWLINE)
	{
	  break;
	}
      curLine++;
    }
  return index;
}

int pushBack(int index)
{
  while(1)
    {
      index--;
      if(tokens[index]!=NEWLINE)
	break;
      curLine--;
    }
  return index;
}

/* Error reporting */
/* Should this be a macro instead? */
void errorReport(int eType, int eTok, int eLine)
{
  errorType = eType;
  errorTok = eTok;
  errorLine = eLine;
}

/* Error diagnosis */
/* Uses an ErrorType,  an errorTok, and errorLine to pointpoint the type and location
of the error*/
void error()
{
  switch(errorType)
    {
    case METHOD:
      printf("");
      break;
    case IFLADDER:
      break;
    case IF:
      break;
    case ELSEIF:
      break;
    case SWITCH:
      break;
    case DEFAULT:
      break;
    case TERMLOOP:
      break;
    default:
      printf("The diagnoser cannot read the program.\n");
    }
}

/* Diagnose is the driver method for this recursive descent parser */
int diagnose()
{
  int index = 0;
  /* This method needs work... it's causing an infinite loop*/
  //  while(tokens[index] != END)
  //    {
      index = method(index);
      //    }
  return 0;
}

/* Returns index if a sentence matches, 0 otherwise */
int method(int index)
{
  if(tokens[(index = readTok(index))] == VOID_METHOD_START)
    {
      if(tokens[(index = readTok(index))] == OPENTOK)
	{
	  if(index = contents(index))
	    {
	      if(tokens[(index = readTok(index))] == CLOSETOK)
		return index;
	    }
	}
    }
  if(nextTok(index) == METHOD_START)
    {
      if(nextTok(index) == OPENTOK)
	{
	  if(index = contents(index))
	    {
	      if(nextTok(index) == CLOSETOK)
		return index;
	    }
	}
    }
  return index;
}

/* Returns index if a sentence matches, 0 otherwise */
int contents(int index)
{
  if(index = ifladder(index))
    {
      index = contents(index);
    }
  else if(index= switch_(index))
    {
      index = contents(index);
    }
  /*
  else if(index = termloop(index))
    {
      index = contents(index);
    }
  */
  return index;
 }

/* Returns index if a sentence matches, 0 otherwise */
int ifladder(int index)
{
  /* Local var blockLine and passing the error message implicitly
   declares a backtrace. (Maybe include an indentation level value somewhere?)*/
  int blockLine = curLine;
  if(index = if_(index))
    {
      if(index = elseifs(index))
	{
	  if(index = else_(index))
	    return index;
	}
    }
  error(IFLADDER, blockLine);
  return index;
}

/* Returns index if a sentence matches, 0 otherwise */
int elseifs(int index)
{
  if(index = elseif_(index))
    {
      if (index = elseifs(index))
	{
	  return index;
	}
    }
  return index;
}

/* Returns 1 if a sentence matches, 0 otherwise */
int if_(int index)
{
  if(nextTok(index) == IF_START)
    {
      if(nextTok(index) == OPENTOK)
	{
	  if(index = contents(index))
	    {
	      if(nextTok(index)==CLOSETOK)
		return index;
	    }
	}
    }
  return 0;
}

/* Returns index if a sentence matches, 0 otherwise */
int elseif_(int index)
{
  if(nextTok(index) == ELSEIF_START)
    {
      if(nextTok(index) == OPENTOK)
	{
	  if(index = contents(index))
	    {
	      if(nextTok(index)==CLOSETOK)
		return index;
	    }
	}
      index = pushBack(index);
      return 0;
    }
  /* I have a feeling this line needs to be in more places */
  index = pushBack(index);
  return index;
}


/* Returns index if a sentence matches, 0 otherwise */
int else_(int index)
{
  if(nextTok(index) == ELSE_START)
    {
      if(nextTok(index)==OPENTOK)
	{
	  if(index = contents(index))
	    {
	      if(nextTok(index)==CLOSETOK)
		return index;
	    }
	}
      return 0;
    }
  index = pushBack(index);
  return index;
}

/* Returns index if a sentence matches, 0 otherwise */
int switch_(int index)
{
  if(nextTok(index) == SWITCH_START)
    {
      if(nextTok(index)==OPENTOK)
	{
	  if(index = cases(index))
	    {
	      if(index = default_(index))
		{
		  if(nextTok(index) == CLOSETOK)
		    return index;
		}
	    }
	}
    }
  return 0;
}

/* Returns index if a sentence matches, 0 otherwise */
int cases(int index)
{
  if(nextTok(index) == CASE)
    {
      if(index = cases(index))
	return index;
    }
  index = pushBack(index);
  return index;
}

/* Returns index if a sentence matches, 0 otherwise */
int default_(int index)
{
  if(nextTok(index) == DEFAULT_START)
    {
      if(nextTok(index) == RETURN)
	return index;
      pushBack(index);
    }
  pushBack(index);
  return 0;
}

/* Feeds the token file into an array */
/* I guess I could make macros to treat taking from and pushing back
into an input buffer the same as the array, but that's more complicated */
/* (I need practice using input buffers, though) */
int main(int argc, char *argv[])
{
  /* Open file */
  if((fid = fopen(argv[1], "r")) == NULL)
    {
      printf("The diagnosis program crashed \n");
      return -1;
    }
  /* Allocated to the file size, an upper bound of the number of tokens */
  /* Actually I'll just allocate 1000 bytes for now. It's simpler. */
  //  tokens = malloc(1000*sizeof(int));
  int i;
  for(i = 0; i < 1000; i++)
    {
      fscanf(fid, "%i", &tokens[i]);
    }
  if(diagnose() == -1)
    printf("The diagnosis program crashed\n");
  else if (errorNum == 0)
    printf("The diagnosis program couldn't find any errors\n");
 
  return 0;
}

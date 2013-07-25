/* Rewrite this to fit GNU Coding Standards... */
#include <stdio.h>
#include "return_header.h"

#define STREAMSIZE 100

#define nextTok(t_index) tokens[t_index = readTok(t_index)]

typedef List Chain;
typedef ListElmt Link;

enum Color
  {
    NORETURN, HASRETURN, MISSRETURN
  };

typedef struct Block
{
  int blockType;
  int startLine;
  //  int returnType;
  int color;
  int linkage;
} Block;

Block findReturnGaps(int *indexPtr);
int *colorPtr(int color);

/************* Global variables **************/
FILE *fid;

/* Current t_index of the token stream */
int t_index = 0;
int curLine = 1;
int tokens[100];
int errorNum = 0;
int last_err = 0;

/************* Functions **************/
/* To create a block that will exist beyond the execution of a function */
Block *blockCopy(Block org)
{
  Block *bcpy = (Block *) malloc(sizeof(Block));
  bcpy->blockType = org.blockType;
  bcpy->startLine = org.startLine;
  bcpy->color = org.color;
  return bcpy;
}

int blockStart(int tokenType)
{
  switch(tokenType)
    {      
    case IF_START:
      //      printf("IF \n");
      return IF;

    case ELSEIF_START:
      return ELSEIF;

    case ELSE_START: 
      //      printf("ELSE \n");
      return ELSE;

    case SWITCH_START:
      return SWITCH;

    case CASE:
      return CASE;

    case DEFAULT_START:
      return DEFAULT;

    case METHOD_START:
      //      printf("METHOD \n");
      return METHOD;

    case VOID_METHOD_START:
      //      printf("VOID METHOD \n");
      return VOID_METHOD;

    case WHILE_START:
      return TERMLOOP;

    case FOR_START:
      return TERMLOOP;

    case FORTERM_START:
      return TERMLOOP;
    }
  return 0;
}

int readTok(int index)
{
  while(1)
    {
      index++;
      if(tokens[index]==END)
	{
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
void error(Block b)
{
  if(last_err == b.startLine)
    return;
  printf("Missing return in ");
  switch(b.blockType)
    {
    case METHOD:
      printf("method ");
      break;
    case CONTENTS:
      break;
    case IFLADDER:
      break;
    case ELESIFS:
      break;
    case ELSE:
      printf("else ");
      break;
    case IF:
      printf("if ");
      break;
    case ELSEIF:
      printf("else if ");
      break;
    case SWITCH:
      printf("switch ");
      break;
    case CASES:
      printf("case ");
      break;
    case DEFAULT:
      printf("default ");
      break;
    case TERMLOOP:
      printf("loop ");
      break;
    default:
        printf("unidentified block ");
    }
  errorNum++;
  last_err = b.startLine;
  printf("on line %i \n", b.startLine);
}

int diagnose()
{
  while(nextTok(t_index) == METHOD_START || tokens[t_index] == VOID_METHOD_START)
    {
      /* Can assume that all blocks at this level are methods*/
     Block method;
     method = findReturnGaps(&t_index);
     if(method.color != HASRETURN && method.blockType != VOID_METHOD)
       /* if the method color is MISSRETURN, the error has already been reported */
       if(method.color != MISSRETURN)
	 error(method);
    }
  return 0;
}

/* Should probably unit test this */
int analyzeChain(Chain *chain)
{
  Link *curLink;
  int allReturns = 0;
  int returnCount = 0;
  //  int hasElse = 0; Necessary?
  for(curLink = chain->head; curLink != NULL; curLink = curLink->next)
    {
      Block *curBlock = (Block *) curLink->data;
      if(curBlock->color == HASRETURN)
	{
	  allReturns = 1;
	  returnCount++;
	}
      /*
      if(curBlock->color == MISSRETURN)
	{
	  return MISSRETURN;
	}
      */
    }
  if(allReturns)
    {
      if(returnCount != chain->size)
	{
	  /* Go back and print out all holes in the chain */
	  for(curLink = chain->head; curLink != NULL; curLink = curLink->next)
	    {
	      Block *curBlock = (Block *) curLink->data;
	      if(curBlock->color != HASRETURN)
		{
		  error(*curBlock);
		}
	    }
	  return MISSRETURN;
	}
      return HASRETURN;
    }

  return NORETURN;
}

Block findReturnGaps(int *indexPtr)
{
  Block curBlock;
  Chain subChainMem;
  Chain *subChain = &subChainMem;
  list_init(subChain, NULL);
  curBlock.blockType = blockStart(tokens[*indexPtr]);
  curBlock.startLine = curLine;
  curBlock.color = NORETURN;

  while(nextTok(*indexPtr) != CLOSETOK)
    {
      /* Chain creation */
      if(blockStart(tokens[*indexPtr]))
	{
	  list_ins_end(subChain, blockCopy(findReturnGaps(indexPtr)));
	}
      if(tokens[*indexPtr]==RETURN)
	{
	  curBlock.color = HASRETURN;
	}
      /* Necessary? */
      if(tokens[*indexPtr]==END)
	{
	  printf("End of input unexpectedly encountered. Program crashed.\n");
	  return curBlock;
	}
    }
  if(curBlock.color != HASRETURN)
    {
      /* Chain analysis */
      switch(analyzeChain(subChain))
	{
	case MISSRETURN:
	  curBlock.color = MISSRETURN;
	  error(curBlock);
	  break;

	case HASRETURN:
	  curBlock.color = HASRETURN;
	  break;
	}
    }
  return curBlock;
}

int main(int argc, char *argv[])
{
  /* Open file */
  if((fid = fopen(argv[1], "r")) == NULL)
    {
      printf("The diagnosis program crashed \n");
      return -1;
    }
  int i;
  for(i = 0; i < STREAMSIZE; i++)
    {
      fscanf(fid, "%i", &tokens[i]);
      if(feof(fid))
	break;
    }
  /* Eat class declaration and its opening curly*/
  nextTok(t_index);
  nextTok(t_index);
  if(diagnose() == -1)
    printf("The diagnosis program crashed\n");
  else if (errorNum == 0)
    printf("The diagnosis program couldn't find any errors\n");
 
  return 0;
}

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
  int color;
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

int NORETURN_val = NORETURN;
int HASRETURN_val = HASRETURN;
int MISSRETURN_val = MISSRETURN;


/************* Functions **************/
/* To create a block that will exist beyond the execution of a function */
Block *blockCopy(Block org)
{
  Block *bcpy = (Block *) malloc(sizeof(Block));
  bcpy->blockType = org.blockType;
  bcpy->startLine = org.startLine;
  bcpy->color = org.color;
}

int *colorPtr(int color)
{
  switch(color)
    {
    case NORETURN:
      return &NORETURN_val;
    case HASRETURN:
      return &HASRETURN_val;
    case MISSRETURN:
      return &MISSRETURN_val;
    }
}
int blockStart(int tokenType)
{
  switch(tokenType)
    {      
    case IF_START:
      printf("IF \n");
      return IF;

    case ELSEIF_START:
      return ELSEIF;

    case ELSE_START: 
      printf("ELSE \n");
      return ELSE;

    case SWITCH_START:
      return SWITCH;

    case CASE:
      return CASE;

    case DEFAULT_START:
      return DEFAULT;

    case METHOD_START:
      printf("METHOD \n");
      return METHOD;

    case VOID_METHOD_START:
      printf("VOID METHOD \n");
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
  printf("on line %i \n", b.startLine);
}
/*
void error(Block b)
{
  printf("Missing return in ");
  switch(b.blockType)
    {
    case METHOD:
      printf("method ");
      break;
    }
  errorNum++;
  printf("on line %i \n", b.startLine);
}
*/
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
}

/* Should probably unit test this */
int analyzeChain(Chain *chain)
{
  Link *curLink;
  int allReturns = 0;
  int returnCount = 0;
  for(curLink = chain->head; curLink != NULL; curLink = curLink->next)
    {
      Block *curBlock = (Block *) curLink->data;
      if(curBlock->color == HASRETURN)
	{
	  allReturns = 1;
	  returnCount++;
	}
    }
  if(allReturns)
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
  return NORETURN;
}

Block findReturnGaps(int *indexPtr)
{
  Block curBlock;
  Chain subChainMem;
  Chain *subChain = &subChainMem;
  Link **curLink;
  list_init(subChain, NULL);
  curLink = &(subChain->head);
  curBlock.blockType = blockStart(tokens[*indexPtr]);
  curBlock.startLine = curLine;
  curBlock.color = NORETURN;
  nextTok(*indexPtr);
  
  while(nextTok(*indexPtr) != CLOSETOK)
    {
      if(blockStart(tokens[*indexPtr]))
	{
	  Link *newLink = malloc(sizeof(Link));
	  if(*curLink == NULL)
	    {
	      *curLink = newLink;
	      subChain->size++;
	    }
	  else
	    {
	      (*curLink)->next = newLink;
	      curLink = &((*curLink)->next);
	      subChain->size++;
	    }
	  (*curLink)->data = blockCopy(findReturnGaps(indexPtr));
	}
      if(tokens[*indexPtr]==RETURN)
	curBlock.color = HASRETURN;
      if(tokens[*indexPtr]==END)
	{
	  printf("End of input unexpectedly encountered. Program crashed.\n");
	  return curBlock;
	}
    }
  if(analyzeChain(subChain)==MISSRETURN)
    {
      error(curBlock);
      curBlock.color = MISSRETURN;
    }

  return curBlock;
}

/*
Block findReturnGaps(int *indexPtr)
{
  Block curBlock;
  curBlock.blockType = blockStart(tokens[*indexPtr]);
  curBlock.startLine = curLine;
  curBlock.color = NORETURN;
  while(nextTok(*indexPtr) != CLOSETOK)
    {
      if(blockStart(tokens[*indexPtr]))
	{
	  findReturnGaps(indexPtr);
	}
      if(tokens[*indexPtr]==RETURN)
	curBlock.color = HASRETURN;      
    }
  return curBlock;
}
*/

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

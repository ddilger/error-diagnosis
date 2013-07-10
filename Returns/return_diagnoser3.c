#include <stdio.h>
#include "return_header.h"

#define nextTok(index) tokens[index = readTok(index)]

/************* Function declarations **************/
int readTok(int index);

/************* Special type declarations **************/



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
/************* Global variables **************/

/* Current index of the token stream */
int index = 0;

int curLine = 0;


/************* Functions **************/
int readTok(int index)
{
  while(1)
    {
      index++;
      /* There's a serious problem with terminating the program where needed */
      if(tokens[index]==END)
	{
	  printf("The diagnosis program crashed (reached end of file)\n");
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

int diagnose()
{
  while(nextTok(index) != END)
    {
      /* Can assume that all blocks at this level are methods*/
     Block method = findReturnGaps(&index);
     if(method.color != HASRETURN && method.blockType != VOID_METHOD)
       error(method);
    }
}

int analyzeChain(Chain *chain)
{
  Link *curLink;
  int allReturns = 0;
  int returnCount = 0;
  for(curLink = chain->head; curLink != NULL; curLink = curLink->next)
    {
      //Needs work because of pointers
      if(curLink->data == HASRETURN)
	{
	  allReturns = 1;
	  returnCount++;
	}
    }
  if(allReturns)
    if(returnCount != chain->size)
      return MISSINGRETURN;
  return NORETURN;
}

/* Maintains a flattened chain of chains of chains (etc) using the 
stack frame. If any link in this chain is colored "MissingReturn", then
the whole chain is "MissingReturn"  */
Block findReturnGaps(int *indexPtr)
{
  Block curBlock;
  Chain *subChain;
  Link *curLink;
  curBlock.blockType = blockStart(tokens[*indexPtr]);
  curBlock.startLine = curLine;

  while(nextTok(*indexPtr) != CLOSETOK)
    {
      if(blockStart(tokens[*indexPtr]))
	{
	  /* New link in the chain */
	  newLink = malloc();
	  curLink->next = newLink;
	  curLink = newLink;
	  /* link color is based on a findReturnGaps */
	  //Needs work because of pointers
	  curLink->data = findReturnGaps(indexPtr).color;
	}
      /* can assume this only happens once in the block */
      if(tokens[*index]==RETURN)
	curBlock.color = HASRETURN;
      if(tokens[*indexPtr]==END)
	{
	  /* Error */
	  return NULL;
	}
    }
  if(analyzeChain(subChain)==MISSRETURN)
    {
      /* This error will be reported each level up in the hierarchy,
       so it's like a backtrace*/
      error(curBlock);
      curBlock.color = MISSRETURN;
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

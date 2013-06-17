/* A stack-based predictive parser for curly brace errors */
/* Parser of type LL(1) */

/* The Grammar:

   for starters there will only be blocks
   "public" is a block starter for simplicity's sake

   program ::= prog_list end | end
   prog_list ::= block_start {block} | null
   block ::= block_start {block} | null
   block_start ::= for(...) | while(...) | if | else | public

   whitespace and characters not part of a terminal token are thrown out
   by the lexer

 */

#include <stdio.h>

enum token_val{

};

int curToken;
int lastOpenLine;
int firstCloseLine;
int state;
int curLine;
int curIndent;

/* Reads through the stack to discern the error */
/* Uses panic mode to recover from error */
/* Runs down a tree (explicit or not) representing the diagnosis machine */
void error()
{
  
}

/* Tokenizes input */
/* I need to use flex for tokenizing this stuff */
void readToken()
{
 char curChar = getc(fid);
 int blockStart;
 switch(state)
   {
   case 1:
     if(curChar == 'f')
       state = 2;
     break;
   case 2:
     if(curChar == 'o')
       state = 3;
     break;
   case 3:
     if(curChar == 'r')
       {
	 state = 4;
	 blockStart = FOR;
       }
     break;
   case 4:
     if(curChar == '(')
       state = 5;
     break;
   case 5:
     if(curChar == ')')
       if (blockStart != NONE)
	 curToken = blockStart;
     
   }
 
}

int isTerminal()
{

}

/*token and look-ahead symbol a */
int table_lookup(int token, int a)
{

}

/* The predictive parser */
int parser()
{
  do
    {
      if(isTerminal(X)) 
	{
	  if(X == curTok)
	    {
	      pop(stack, data);
	      readToken();
	    }
	  else
	    error();
	}
      else
	{
	  if(table_lookup(X, curTok))
	    {
	      /* This part of algorithm handled by table_lookup */
	    }
	  else
	    error();
	}
    } while(X != END);
}

/* If compound errors reduce accuracy, perhaps 
have start and end line numbers as arguments */
/* Currently just opens a token stream file */
int main(int argc, char *argv[])
{
  return 0;
}

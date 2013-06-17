/* Uses recursion to balance curly opening and closing braces */
#include <stdio.h>
enum token{NONE, OPEN='{', CLOSE='}', END};

FILE *fid;

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

int balanced()
{
  if(curToken == OPEN)
    {
      curToken = readToken();
      if(curToken == OPEN)
	{
	/* If part of a compiler,
	 the semantic actions would
	happen here, before the
	push to the stack of
	the production being pushed,
	balance()*/
	if(!balanced())
	  return 0;
        curToken = readToken();
	}
      if(curToken == CLOSE)
	return 1;
      return 0;
    }
  curToken = readToken();
  if(curToken == OPEN)
    return balanced();
  else if(curToken == END)
    return 1;
  
  return 0;
}

/* Superfluous representation of the empty string */
int epsilon()
{
  return 1;
}



int main(int argc, char *argv[])
{
  if((fid = fopen(argv[1], "r")) == NULL)
    return -1;
  curToken = readToken();
  int i = balanced();
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

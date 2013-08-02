/* A finite automata attempt at diagnosing string errors */

#include <stdio.h>
#include <ctype.h>

#define LINESIZE 200

enum
  {
    NONE, ODD, NO_CLOSE, NO_OPEN, NEWLINE, BAD_ESCAPE,
    EXAMINE
  };

FILE *fp;

void reportError(int diagnosis, int error_line)
{
 switch(diagnosis)
    {
    case NO_CLOSE:
      printf("No closing quotation mark on line %i\n", error_line);
      break;
    case NO_OPEN:
      printf("No opening quotation mark on line %i\n", error_line);
      break;
    case ODD:
      printf("Odd number of quotation marks on line %i\n", error_line);
      break;
    case NEWLINE:
      printf("The string is broken up over multiple lines starting at line %i\n", error_line);
      break;
    case BAD_ESCAPE:
      printf("Bad escape sequence definitions on line %i\n", error_line);
      break;
    case EXAMINE:
      printf("Oops\n");
      break;
    default:
      printf("Could not find a source of error in the program \n");
    }
}

void checkStrErrors(char* filename)
{
  int error_count=0;
  int diagnosis=NONE;
  int cur_line=0;
  int error_line=0;
  int state = 0;
  char line[LINESIZE];
  if ((fp = fopen(filename, "r")) == NULL)
    return;
  while (fgets(line, LINESIZE, fp) != NULL)
    {
      cur_line++;
      int i;
      for(i=0; line[i]!='\0'; i++)
	{
	  switch(state)
	    {
	    case 0:
	      if(diagnosis!=NONE)
		{
		  error_count++;
		  reportError(diagnosis, error_line);
		  diagnosis=NONE;
		}
	      if(line[i] == '"')
		state = 3;
	      else if(line[i]=='/')
		state=11;
	      else
		state=0;
	      break;
	    case 1:
	      diagnosis=NONE;
	      if(line[i] == '\\')
		state=2;
	      else if(line[i]=='+')
		state=1;
	      else if(line[i]=='"')
		state=3;
	      else if(line[i] != '\n' && isspace(line[i]))
		state=1;
	      else if(line[i] == '\n')
		state=7;
	      else
		state=0;
	      break;
	    case 2:
	      state=1;	      
	      break;
	    case 3:
	      diagnosis=ODD;
	      error_line=cur_line;
	      if(line[i]=='"')
		state=1;
	      else if(line[i]=='\\')
		state=4;
	      else if(line[i]=='\n')
		state=9;
	      break;
	    case 4:
	      state=3;
	      break;
	    case 5:
	      if(line[i]=='\n')
		state=0;
	      break;
	    case 6:
	      if(line[i]=='\n')
		state=0;
	      break;
	    case 7:
	      error_line=cur_line-1;
	      diagnosis=NEWLINE;
	      if(line[i]=='"')
		state=8;
	      if(line[i]=='\n')
		state=0;
	      break;
	    case 8:
	      error_line=cur_line-1;
	      diagnosis=NEWLINE;
	      if(line[i]=='"')
		state=1;
	      if(line[i]=='\n')
		state=0;
	      break;
	      /* Should 9 be its own state? */
	    case 9:
	      error_line=cur_line-1;
	      diagnosis=ODD;
	      if(line[i]=='"')
		state=8;
	      if(line[i]=='\n')
		state=0;
	      break;
	    case 10:
	      if(line[i]=='\n')
		state=0;
	      break;
	    case 11:
	      if(line[i]=='*')
		state=12;
	      if(line[i]=='/')
		state=14;
	      break;
	    case 12:
	      if(line[i]=='*')
		state=13;
		break;
	    case 13:
	      if(line[i]=='/')
		state=0;
	      if(line[i]=='\n')
		state=0;
		break;
	    case 14:
	      if(line[i]=='/')
		state=0;
	      break;
	    }
	}

    }
  if (error_count == 0)
    {
      reportError(NONE, 0);
    }
  fclose(fp);
}

int main(int argc, char *argv[])
{
  checkStrErrors(argv[1]);
  return 0;
}


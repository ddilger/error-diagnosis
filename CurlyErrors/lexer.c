/* I should redo this program to support pipelining */
/* tokenizes an input file and produces a token file*/
#include <stdio.h>


FILE *in;
FILE *out;

enum tokens{
  NONE=0, BLOCK_START=1, OPEN_CURLY=2,
  CLOSE_CURLY=3, NEWLINE=4, ARRAY_START=5,
  END=6
};

/* A very poor lexer */
void lexer()
{
  char line[100];
  int end = 0;
  do{
    /* Somehow essential to terminate the program */
    if(fgets(line, 100, in) == NULL)
      break;
    int i=0;
    while(line[i]!='\0')
      {
	/* Loop breaking conditionals */
	if(line[i] == EOF)
	  {
	    end=1;
	    break;
	  }
	if(line[i] == '\n')
	  {
	    fprintf(out, "%i ", NEWLINE);
	     break; 
	  }

	/*** Print block start ***/
	/* for*/
	if(line[i+0]=='f'&&line[i+1]=='o'&&line[i+2]=='r'&&line[i+3]=='(')
	  fprintf(out, "%i ", BLOCK_START);
	/* while */
	if(line[i+0]=='w'&&line[i+1]=='h'&&line[i+2]=='i'&&line[i+3]=='l'&&line[i+4]=='e')
	  fprintf(out, "%i ", BLOCK_START);
	/* public--stands for methods and class declarations*/
	if(line[i+0]=='p'&&line[i+1]=='u'&&line[i+2]=='b'&&line[i+3]=='l'&&line[i+4]=='i'&&line[i+5]=='c')
	  fprintf(out, "%i ", BLOCK_START);
	/* if*/
	if(line[i+0]=='i'&&line[i+1]=='f')
	  fprintf(out, "%i ", BLOCK_START);
	/* else*/
	if(line[i+0]=='e'&&line[i+1]=='l'&&line[i+2]=='s'&&line[i+3]=='e')
	  fprintf(out, "%i ", BLOCK_START);

	/*** Print curly open ***/
	if(line[i]=='{')
	  fprintf(out, "%i ", OPEN_CURLY);
	
	/*** Print curly close ***/
	if(line[i]=='}')
	  fprintf(out, "%i ", CLOSE_CURLY);

	/*** Print array open ***/
	if(line[i]=='[' && line[i+1]==']')
	  {
	    int j;
	    for(j=0; line[j] != '\0'; j++)
	      {
		if(line[j] == '=')
		  {
		    fprintf(out, "%i ", ARRAY_START);
		    break;
		  }
	      }
	  }

	i++;
      }
  loopend: ;
  } while(!end);
  fprintf(out, "%i", END);
}

int main(int argc, char *argv[])
{
  if((in = fopen(argv[1], "r")) == NULL)
    {
      printf("lexer crashed: bad read file \n");
      return -1;
    }
  if((out = fopen(argv[2], "w")) == NULL)
    {
      printf("lexer crashed: bad write file \n");
      return -1;
    }
  lexer();
  fclose(in);
  fclose(out);
  return 0;
}

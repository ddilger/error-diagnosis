#include "return_header.h"

FILE *in;
FILE *out;

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
	/* for (later needs a terminable for)*/
	if(line[i+0]=='f'&&line[i+1]=='o'&&line[i+2]=='r'&&line[i+3]=='(')
	  fprintf(out, "%i ", FOR_START);
	/* while */
	if(line[i+0]=='w'&&line[i+1]=='h'&&line[i+2]=='i'&&line[i+3]=='l'&&line[i+4]=='e')
	  fprintf(out, "%i ", WHILE_START);
	/* public--stands for methods and class declarations*/
	if(line[i+0]=='p'&&line[i+1]=='u'&&line[i+2]=='b'&&line[i+3]=='l'&&line[i+4]=='i'&&line[i+5]=='c')
	  {
	    if(line[i+7]=='c'&&line[i+8]=='l'&&line[i+9]=='a'&&line[i+10]=='s'&&line[i+11]=='s')
	      {
		/* Do nothing */
	      }
	    else
	      {
		if(line[i+7]=='v'&&line[i+8]=='o'&&line[i+9]=='i'&&line[i+10]=='d')
		  fprintf(out, "%i ", VOID_METHOD_START);
		fprintf(out, "%i ", METHOD_START);
	      }
	  }
	/* else if */
	if(line[i+0]=='i'&&line[i+1]=='f'&&line[i+3]=='e'&&line[i+4]=='l'&&line[i+5]=='s'&&line[i+6]=='e')
	  fprintf(out, "%i ", ELSEIF_START);
	/* if*/
	else if(line[i+0]=='i'&&line[i+1]=='f')
	  fprintf(out, "%i ", IF_START);
	/* else*/
	else if(line[i+0]=='e'&&line[i+1]=='l'&&line[i+2]=='s'&&line[i+3]=='e')
	  fprintf(out, "%i ", ELSE_START);

	/*** Open token ***/
	if(line[i]=='{')
	  fprintf(out, "%i ", OPENTOK);
	
	/*** Close token ***/
	if(line[i]=='}')
	  fprintf(out, "%i ", CLOSETOK);
	
	/* Case */
	if(line[i+0]=='c'&&line[i+1]=='a'&&line[i+2]=='s'&&line[i+3]=='e')
	  fprintf(out, "%i ", CASE);

	/* return */
	if(line[i+0]=='r'&&line[i+1]=='e'&&line[i+2]=='t'&&line[i+3]=='u'&&line[i+4]=='r'&&line[i+5]=='n')
	  fprintf(out, "%i ", RETURN);

	/* switch */
	if(line[i+0]=='s'&&line[i+1]=='w'&&line[i+2]=='i'&&line[i+3]=='t'&&line[i+4]=='c'&&line[i+5]=='h')
	  fprintf(out, "%i ", SWITCH_START);

	/* default */
	if(line[i+0]=='d'&&line[i+1]=='e'&&line[i+2]=='f'&&line[i+3]=='a'&&line[i+4]=='u'&&line[i+5]=='l'&&line[i+6]=='t')
	  fprintf(out, "%i ", DEFAULT);

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


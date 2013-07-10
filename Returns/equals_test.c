/* A test of how the equals operator works in C */
#include <stdio.h>

int inc(int index)
{
  index++;
  return index;
}

int main()
{
  int index = 1;
  if((index = inc(index)) == 2)
    printf("Everything works as expected\n");
  else
    printf("Error\n");
  return 0;
}


#ifndef RETURNH
#define RETURNH

#include "linkedlist.h"
#include "linkedlist.c"
#include "stack.h"
#include "stack.c"

#define LENGTH 27
#define WIDTH 27

typedef List Production;
typedef ListElmt Element;

/* Can I have a multidimensional array of pointers? */
Production *table[LENGTH][WIDTH];

typedef enum Token
  {
    NONE = 0, 
    IF_START = 1, 
    ELSEIF_START = 2, 
    ELSE_START = 3, 
    SWITCH_START = 4, 
    CASE = 5, 
    DEFAULT_START = 6, 
    METHOD_START = 7, 
    VOID_METHOD_START = 16,
    WHILE_START = 8, 
    FOR_START = 9, 
    FORTERM_START = 10, 
    NEWLINE = 11, 
    OPENTOK = 12, 
    CLOSETOK = 13, 
    RETURN = 14, 
    END = 15,
  } Token;

typedef enum Nonterminal
  {
    /* "None" in here seems like unclean code */
    METHOD=20,
    CONTENTS=21, 
    IFLADDER=22, 
    ELESIFS=23, 
    ELSE=24, 
    IF=25, 
    ELSEIF=26,
    SWITCH=28, 
    CASES=29, 
    DEFAULT=30, 
    TERMLOOP=31
  } Nonterminal;

/* Is having this function in a header good programming practice? */
/* It might be better to follow the algorithm (using FIRST and FOLLOW) for filing tables from
 CFGs, as presented in the Dragon Book*/
/*  void tableInit()
  {
    
  }
*/
#endif

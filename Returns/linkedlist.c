/* Linked list using the template in
 "Mastering Algorithms in C"  

In C++ there would be a linked list class, an element class,
and the public interface would be in the list class. Instead
of using void pointers the classes would be implemeneted using
templates.

*/

/* 
******** Extensions ********
Comment per new commenting standard
Get map to work
Implement more features from Mastering Algorithms book
 */

/* This really should be in a header file... */
#ifndef LIST_C
#define LIST_C

#include "linkedlist.h"

void list_init(List *list, void (*destroy) (void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void list_destroy(List *list)
{
  
}
/* Removes head of list */
int list_rem_head(List *list)
{
  list->head = list->head->next;
  list->size--;
  return 0;
}

/* list_rem_next */
int list_rem_next(List *list, ListElmt *element, void **data)
{
  if (list_size(list) == 0)
    return -1;

  ListElmt *old_element;
  if(element == NULL)
    {
      *data = list->head->data;
      old_element = list->head;
      list->head = list->head->next;
      /* Essentially removing tail from list */
      if(list_size(list) == 1)
	list->tail = NULL;
    }
  else
    {
      if (element->next == NULL)
	return -1;
      *data = element->next->data;
      old_element = element->next;
      element->next = element->next->next;
      
      if(element->next == NULL)
	list->tail = element;
    }
  free(old_element);
  list->size--;
  return 0;
}

/*Inserts at the next*/
int list_ins_next(List *list, ListElmt *element, const void *data)
{
  ListElmt *newElm;

  if ((newElm = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
      return -1;

  /* How does casting to a void pointer 
   prevent a segfault? */
  newElm->data = (void *) data;

  if (element == NULL)
    {
      if (list_size(list) == 0)
	list->tail = newElm;
      newElm->next = list_head(list);
      list_head(list) = newElm;
    }
  else
    {
      if(element->next == NULL)
	{
	  list->tail = newElm;
	}

      newElm->next = element->next;
      element->next = newElm;
    }
  list->size++;
  return 0;
}
int list_ins_end(List *list, const void *data)
{
  if (list->size==0)
    return list_ins_next(list, NULL, data);
  return list_ins_next(list, list->tail, data);
}

void print_list(List *list)
{
  printf("list size: %i\n", list_size(list));
  ListElmt *curElmt = list_head(list);
  int *dataPtr = (int *) list_data(curElmt);
  printf("%i\n", *dataPtr);
  curElmt = curElmt->next;
  int i = 0;
  for (i=1; i<list_size(list); i++)
    {
      int *dataPtr = (int *) list_data(curElmt);
      printf("%i\n", *dataPtr);
      curElmt = curElmt->next;
    }
}

/* An implementation of map in C, using function pointers */
void map(List *list, void (*funct)(void *arg))
{
  printf("One");
  ListElmt *curElmt = list_head(list);
  int i;
  for (i=0; i<list_size(list); i++)
    {
      printf("Two");
      funct(curElmt->data);
      curElmt = curElmt->next;
    }
}

void *add1(void *data)
{
  printf("Three");
  int *numPtr = (int *) data;
  *numPtr += 1;
  return ((void *) numPtr);
}
/*
int main()
{
  List l;
  list_init(&l, NULL);
  int i;
  data[0] = 2;
  list_ins_next(&l, NULL, &data[0]);
    for (i=1; i<5; i++)
    {
      data[i] = (i+1)*2;
      list_ins_next(&l, list_tail(&l), &data[i]);
    }
  
  print_list(&l);
  //  void (* fp)(void *);
  //  map(&l, fp);
  //  print_list(&l);

  return 0;
}

*/

#endif

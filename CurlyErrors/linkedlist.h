#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_data(element) ((element)->data)

int data[8];

/********** Structure for Linked List Elements ***********/
typedef struct ListElmt_ ListElmt;

struct ListElmt_
{
  void *data;
  ListElmt *next;
};

/************ Structure for linked lists ***************/

typedef struct List_ List;

struct List_
{
  int size;
  int (*match) (const void *key1, const void *key2);
  void (*destroy) (void *data);
  ListElmt *head;
  ListElmt *tail;
};

/************** Public Interface ************/

/*Initializes the linked list specified by list */
void list_init(List *list, void (*destroy) (void *data));

/* Destroy the linked list */
//void list_destroy(List *list);

/* Insert an element just after element */
//int list_ins_next(List *list, ListElmt *element, const void *data);

/* Remove an element just after element */
//int list_rem_next(List *list, ListElmt *element, void **data);

/* Number of elements in the list */
//int list_size(const List *list);

/* Element at the head of the list */
//ListElmt *list_head(const List *list);

/* Data stored in the element */
//void *list_data(const ListElmt *element);

/* Element following the specified element */
//ListElmt *list_next(const ListElmt *element);

#endif

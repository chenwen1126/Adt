/**
*	@file:		list.h
*	@details:	c doubly linked list head file
*	@author: 	chenwen(chenwen1126@tom.com)
*   @datetime:  2018-2-6
*   @history:   V1.0 first edition
*/

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* list node struct*/
typedef struct list_node{
    struct list_node* prev;
	struct list_node* next;
    void* val;
}list_node_t;

/* list struct */
typedef struct {
    list_node_t* head;
    list_node_t* tail;
    int len;
    void (*free)(void *);
	int (*match)(void *, void*);
}list_t;

/* list node create&destroy */
list_node_t* node_create(void* val);
void node_destroy(list_t *list, list_node_t* node);

/* list create&destroy */
list_t* list_create();
void list_destroy(list_t*self);

/* list push&pop */
void list_push_back(list_t*self, list_node_t* node);
void list_push_front(list_t*self, list_node_t* node);

list_node_t* list_pop_back(list_t*self);
list_node_t* list_pop_front(list_t*self);

/* list at&index */
list_node_t* list_at(list_t*self, int index);
int list_index(list_t* self, list_node_t* node);

/* list remove */
void list_remove(list_t* self, list_node_t* node);
void list_remove_front(list_t* self);
void list_remove_back(list_t* self);

/* list insert */
void list_insert_before(list_t* self, list_node_t* before, list_node_t* node);
void list_insert_after(list_t* self, list_node_t* after, list_node_t* node);

/* list find */
list_node_t* list_find(list_t* self, void* val);
list_node_t* list_find_reverse(list_t* self, void* val);

/* list reverse */
void list_reverse(list_t* self);

/* list swap */
void list_swap(list_t* self, list_node_t* node_a, list_node_t* node_b);

/* list foreach */
#define list_each(node, list)  for (list_node_t* node = list->head; node; node = node->next)
#define list_each_reverse(node, list) for (list_node_t* node = list->tail; node; node = node->prev)

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

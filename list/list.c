/**
*	@file:		list.c
*	@details:	c doubly linked list source file
*	@author: 	chenwen(chenwen1126@tom.com)
*   @datetime:  2018-2-6
*   @history:   V1.0 first edition
*/

#include "list.h"

#define null NULL

list_node_t* node_create(void* val)
{
	list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
	if (!node)
		return null;

	node->val = val;
	node->prev = null;
	node->next = null;

	return node;
}

void node_destroy(list_t *list, list_node_t* node)
{
	if (list->free)
		list->free(node->val);

	free(node);
}

list_t *list_create()
{
	list_t* self = (list_t*)malloc(sizeof(list_t));
	if (!self)
		return null;

	self->len = 0;
	self->head = null;
	self->tail = null;
	self->free = null;
	self->match = null;

	return self;
}

void list_destroy(list_t* self)
{
	list_node_t* curr = self->head, *next;
	while (curr)
	{
		next = curr->next;
		node_destroy(self, curr);
		curr = next;
	}
	free(self);
}

void list_push_front(list_t*self, list_node_t* node)
{
	if (self->len)
	{
		node->next = self->head;
		node->prev = null;

		self->head->prev = node;
		self->head = node;
	}
	else
	{
		node->prev = node->next = null;
		self->head = self->tail = node;
	}

	++self->len;
}

void list_push_back(list_t *self, list_node_t *node)
{
	if (self->len)
	{
		node->prev = self->tail;
		node->next = null;

		self->tail->next = node;
		self->tail = node;
	}
	else
	{
		node->prev = node->next = null;
		self->head = self->tail = node;
	}
	++self->len;
}

list_node_t* list_pop_front(list_t*self)
{
	list_node_t* node = self->head;
	if (!self->len)
		return null;

	if (--self->len)
	{
		self->head = node->next;
		self->head->prev = null;
	}
	else
	{
		self->head = self->tail = null;
	}

	node->prev = node->next = null;
	return node;
}

list_node_t* list_pop_back(list_t*self)
{
	list_node_t *node = self->tail;
	if (!self->len) 
		return null;

	if (--self->len) 
	{
		self->tail = node->prev;
		self->tail->next = null;
	}
	else 
	{
		self->head = self->tail = null;
	}

	node->next = node->prev = null;
	return node;
}

list_node_t* list_at(list_t*self, int index)
{
	list_node_t* node = null;
	if (index >= self->len || index < 0)
		return null;

	if (index > self->len / 2)
	{
		index = self->len - index;
		node = self->tail;
		while (--index)
			node = node->prev;
	}
	else
	{
		node = self->head;
		while (index--)
			node = node->next;
	}
	return node;
}

int list_index(list_t* self, list_node_t* node)
{
	int index = 0;

	list_each(node_, self)
	{
		if (node_ == node)
			return index;
		++index;
	}

	return -1;
}

void list_remove(list_t* self, list_node_t* node)
{
	if (node->prev)
		node->prev->next = node->next;
	else
		self->head = node->next;

	if (node->next)
		node->next->prev = node->prev;
	else
		self->tail = node->prev;

	node_destroy(self, node);
	--self->len;
}

void list_remove_front(list_t* self)
{
	node_destroy(self, list_pop_front(self));
}

void list_remove_back(list_t* self)
{
	node_destroy(self, list_pop_back(self));
}

void list_insert_before(list_t* self, list_node_t* before, list_node_t* node)
{
	node->next = before;
	node->prev = before->prev;

	if (before->prev)
		before->prev->next = node;
	else
		self->head = node;
	before->prev = node;

	++self->len;
}

void list_insert_after(list_t* self, list_node_t* after, list_node_t* node)
{
	node->prev = after;
	node->next = after->next;

	if (after->next)
		after->next->prev = node;
	else
		self->tail = node;
	after->next = node;

	++self->len;
}

list_node_t* list_find(list_t* self, void* val)
{
	if (!self->match)
		return null;

	list_each(node, self)
	{
		if (self->match(node->val, val))
			return node;
	}
	return null;
}

list_node_t* list_find_reverse(list_t* self, void* val)
{
	if (!self->match)
		return null;

	list_each_reverse(node, self)
	{
		if (self->match(node->val, val))
			return node;
	}
	return null;
}

void list_reverse(list_t* self)
{
	list_node_t* temp;
	if (self->len < 2)
		return;

	for (list_node_t* node = self->head; node; node = node->prev)
	{
		temp = node->prev;
		node->prev = node->next;
		node->next = temp;
	}

	temp = self->head;
	self->head = self->tail;
	self->tail = temp;

	return;
}

void list_swap(list_t* self, list_node_t* node_a, list_node_t* node_b)
{
	if (node_a->next == node_b && node_b->prev == node_a) //neighbor and node_a first
	{
		node_a->prev ? (node_a->prev->next = node_b) : (self->head = node_b);
		node_b->next ? (node_b->next->prev = node_a) : (self->tail = node_a);

		list_node_t* temp = node_b->next; 
		node_b->next = node_a; node_b->prev = node_a->prev;
		node_a->prev = node_b; node_a->next = temp;
	}
	else if (node_a->prev == node_b && node_b->next == node_a) //neighbor and node_b first
	{
		node_a->next ? (node_a->next->prev = node_b) : (self->tail = node_b);
		node_b->prev ? (node_b->prev->next = node_a) : (self->head = node_a);

		list_node_t* temp = node_b->prev;
		node_b->prev = node_a; node_b->next = node_a->next;
		node_a->next = node_b; node_a->prev = temp;
	}
	else
	{
		node_a->prev ? (node_a->prev->next = node_b) : (self->head = node_b);
		node_a->next ? (node_a->next->prev = node_b) : (self->tail = node_b);
		node_b->prev ? (node_b->prev->next = node_a) : (self->head = node_a);
		node_b->next ? (node_b->next->prev = node_a) : (self->tail = node_a);

		list_node_t* temp;
		temp = node_a->next;node_a->next = node_b->next;node_b->next = temp;
		temp = node_a->prev;node_a->prev = node_b->prev;node_b->prev = temp;
	}
}


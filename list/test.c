#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

#define null NULL
#define test_begin(test_unit)   printf("================== \"%s\" unit test begin!!!===============\r\n", #test_unit);
#define test_finshed(test_unit) printf("=========All \"%s\" unit test done and 100%% pass!!!========\r\n", #test_unit);
#define test(test_case) \
	test_##test_case(); \
	printf("%26s test case pass!!!\r\n", #test_case);

static free_cnt = 0;

void free_proxy(void* val)
{
	free_cnt++;
	free(val);
}

int char_equal(void* val_a, void* val_b)
{
	return *(char*)val_a == *(char*)val_b;
}

int list_size(list_t* self)
{
	int size = 0;
	list_each(node, self)
		size++;
	return size;
}

void test_list_create()
{
	list_t* list = list_create();
	if (!list)
		return;

	assert(list->len == 0);
	assert(list->head == null);
	assert(list->tail == null);

	list_destroy(list);
}

void test_list_push()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	assert(list->len == 4);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == d);
	assert(a->next == b);
	assert(b->next == c);
	assert(c->next == d);
	assert(d->next == null);
	assert(d->prev == c);
	assert(c->prev == b);
	assert(b->prev == a);
	assert(a->prev == null);

	list_push_front(list, e);
	list_push_front(list, f);
	list_push_front(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == g);
	assert(list->tail == d);
	assert(g->next == f);
	assert(f->next == e);
	assert(e->next == a);
	assert(a->prev == e);

	list_destroy(list);
}

void test_list_pop()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	list_pop_front(list);
	assert(list->len == 6);
	assert(list->len == list_size(list));
	assert(list->head == b);
	assert(list->tail == g);
	assert(g->next == null);
	assert(b->prev == null);

	list_pop_back(list);
	assert(list->len == 5);
	assert(list->len == list_size(list));
	assert(list->head == b);
	assert(list->tail == f);
	assert(f->next == null);
	assert(b->prev == null);

	list_pop_front(list);
	list_pop_front(list);
	assert(list->len == 3);
	assert(list->len == list_size(list));
	assert(list->head == d);
	assert(list->tail == f);
	assert(f->next == null);
	assert(d->prev == null);

	list_pop_back(list);
	list_pop_back(list);
	assert(list->len == 1);
	assert(list->len == list_size(list));
	assert(list->head == d);
	assert(list->tail == d);
	assert(d->next == null);
	assert(d->prev == null);

	list_destroy(list);
}

void test_list_clear()
{
	list_t* list = list_create();
	list->free = free_proxy;
	free_cnt = 0;

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, node_create(a));
	list_push_back(list, node_create(b));
	list_push_back(list, node_create(c));
	list_push_back(list, node_create(d));
	list_push_back(list, node_create(e));
	list_push_back(list, node_create(f));
	list_push_back(list, node_create(g));
	assert(list->len == 7);
	assert(list->len == list_size(list));

	list_clear(list);
	assert(free_cnt == 7);
	assert(list->len == 0);
	assert(list->len == list_size(list));
	assert(list->head == null);
	assert(list->tail == null);

	list_destroy(list);
}

void test_list_destroy()
{
	list_t* list = list_create();
	list->free = free_proxy;
	free_cnt = 0;

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, node_create(a));
	list_push_back(list, node_create(b));
	list_push_back(list, node_create(c));
	list_push_back(list, node_create(d));
	list_push_back(list, node_create(e));
	list_push_back(list, node_create(f));
	list_push_back(list, node_create(g));
	assert(list->len == 7);
	assert(list->len == list_size(list));

	list_destroy(list);
	assert(free_cnt == 7);
}

void test_list_index()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	list_node_t* node = null;
	node = list_at(list, 0);
	assert(*(char*)(node->val) == 'a');
	node = list_at(list, 1);
	assert(*(char*)(node->val) == 'b');
	node = list_at(list, 2);
	assert(*(char*)(node->val) == 'c');
	node = list_at(list, 3);
	assert(*(char*)(node->val) == 'd');
	node = list_at(list, 4);
	assert(*(char*)(node->val) == 'e');
	node = list_at(list, 5);
	assert(*(char*)(node->val) == 'f');
	node = list_at(list, 6);
	assert(*(char*)(node->val) == 'g');
	node = list_at(list, 7);
	assert(node == null);
	node = list_at(list, -1);
	assert(node == null);

	assert(list_index(list, a) == 0);
	assert(list_index(list, b) == 1);
	assert(list_index(list, c) == 2);
	assert(list_index(list, d) == 3);
	assert(list_index(list, e) == 4);
	assert(list_index(list, f) == 5);
	assert(list_index(list, g) == 6);

	list_node_t* h = node_create("h");
	assert(list_index(list, h) == -1);

	list_destroy(list);
}

void test_list_remove()
{
	list_t* list = list_create();
	list->free = free_proxy;
	free_cnt = 0;

	list_node_t* a = node_create(node_create("a"));
	list_node_t* b = node_create(node_create("b"));
	list_node_t* c = node_create(node_create("c"));
	list_node_t* d = node_create(node_create("d"));
	list_node_t* e = node_create(node_create("e"));
	list_node_t* f = node_create(node_create("f"));
	list_node_t* g = node_create(node_create("g"));

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));

	list_remove(list, b);
	assert(list->len == 6);
	assert(free_cnt == 1);
	assert(a->next = c);
	assert(c->prev == a);

	list_remove(list, a);
	assert(list->len == 5);
	assert(list->len == list_size(list));
	assert(free_cnt == 2);
	assert(list->head = c);
	assert(c->prev == null);
	assert(c->next == d);

	list_remove(list, g);
	assert(list->len == 4);
	assert(list->len == list_size(list));
	assert(free_cnt == 3);
	assert(list->tail = f);
	assert(f->next == null);

	list_remove_front(list);
	assert(list->len == 3);
	assert(list->len == list_size(list));
	assert(free_cnt == 4);
	assert(list->head = d);
	assert(d->prev == null);

	list_remove_back(list);
	assert(list->len == 2);
	assert(list->len == list_size(list));
	assert(free_cnt == 5);
	assert(list->tail = e);
	assert(e->next == null);

	list_destroy(list);
}


void test_list_insert()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	assert(list->len == 3);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == c);

	list_insert_after(list, a, d);
	assert(list->len == 4);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == c);
	assert(a->next = d);
	assert(d->prev = a);
	assert(d->next = b);
	assert(b->prev = d);
	assert(b->next = c);

	list_insert_after(list, c, e);
	assert(list->len == 5);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == e);
	assert(e->prev = c);
	assert(c->next = e);

	list_insert_before(list, c, f);
	assert(list->len == 6);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == e);
	assert(b->next = f);
	assert(f->next = c);
	assert(f->prev = b);

	list_insert_before(list, a, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == g);
	assert(list->tail == e);
	assert(g->next = a);
	assert(a->prev = g);

	list_destroy(list);
}

void test_list_find()
{
	list_t* list = list_create();
	list->match = char_equal;

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	list_node_t * node1 = null, *node2 = null;

	node1 = list_find(list, "a");
	node2 = list_find_reverse(list, "a");
	assert(a == node1);
	assert(a == node2);

	node1 = list_find(list, "c");
	node2 = list_find_reverse(list, "c");
	assert(c == node1);
	assert(c == node2);

	node1 = list_find(list, "e");
	node2 = list_find_reverse(list, "e");
	assert(e == node1);
	assert(e == node2);

	node1 = list_find(list, "g");
	node2 = list_find_reverse(list, "g");
	assert(g == node1);
	assert(g == node2);

	list_node_t* h = node_create("h");
	node1 = list_find(list, h);
	node2 = list_find_reverse(list, h);
	assert(null == node1);
	assert(null == node2);

	list_destroy(list);
}

void test_list_reverse()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	list_reverse(list);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == g);
	assert(list->tail == a);
	assert(a->next == null);
	assert(g->prev == null);

	assert(g->next == f);
	assert(f->next == e);
	assert(e->next == d);
	assert(d->next == c);
	assert(c->next == b);
	assert(b->next == a);

	assert(a->prev == b);
	assert(b->prev == c);
	assert(c->prev == d);
	assert(d->prev == e);
	assert(e->prev == f);
	assert(f->prev == g);

	list_reverse(list);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(a->prev == null);
	assert(g->next == null);

	assert(a->next == b);
	assert(b->next == c);
	assert(c->next == d);
	assert(d->next == e);
	assert(e->next == f);
	assert(f->next == g);

	assert(g->prev == f);
	assert(f->prev == e);
	assert(e->prev == d);
	assert(d->prev == c);
	assert(c->prev == b);
	assert(b->prev == a);

	list_destroy(list);
}

void test_list_swap()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	list_swap(list, a, c);

	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == c);
	assert(a->prev == b);
	assert(a->next == d);
	assert(b->prev == c);
	assert(b->next == a);
	assert(c->prev == null);
	assert(c->next == b);
	assert(d->prev == a);
	assert(d->next == e);

	list_swap(list, e, f);

	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == c);
	assert(list->tail == g);
	assert(d->prev == a);
	assert(d->next == f);
	assert(e->prev == f);
	assert(e->next == g);
	assert(f->prev == d);
	assert(f->next == e);
	assert(g->prev == e);
	assert(g->next == null);

	list_swap(list, c, b);

	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == b);
	assert(list->tail == g);
	assert(a->prev == c);
	assert(a->next == d);
	assert(b->prev == null);
	assert(b->next == c);
	assert(c->prev == b);
	assert(c->next == a);
	assert(d->prev == a);
	assert(d->next == f);
	assert(f->prev == d);
	assert(f->next == e);

	list_destroy(list);
}

void test_list_each()
{
	list_t* list = list_create();

	list_node_t* a = node_create("a");
	list_node_t* b = node_create("b");
	list_node_t* c = node_create("c");
	list_node_t* d = node_create("d");
	list_node_t* e = node_create("e");
	list_node_t* f = node_create("f");
	list_node_t* g = node_create("g");

	list_push_back(list, a);
	list_push_back(list, b);
	list_push_back(list, c);
	list_push_back(list, d);
	list_push_back(list, e);
	list_push_back(list, f);
	list_push_back(list, g);
	assert(list->len == 7);
	assert(list->len == list_size(list));
	assert(list->head == a);
	assert(list->tail == g);
	assert(g->next == null);
	assert(a->prev == null);

	int len = 0;
	char* buf = (char*)malloc(sizeof(char)* 16);

	list_each(node, list)
		len += sprintf_s(buf + len, sizeof(char)* 16, "%s", (char*)node->val);
	assert(0 == strcmp(buf, "abcdefg"));

	len = 0;
	list_each_reverse(node, list)
		len += sprintf_s(buf + len, sizeof(char)* 16, "%s", (char*)node->val);
	assert(0 == strcmp(buf, "gfedcba"));

	list_destroy(list);

}

int main(void)
{
	test_begin(list);
	test(list_create);
	test(list_push);
	test(list_pop);
	test(list_clear);
	test(list_destroy);
	test(list_index);
	test(list_remove);
	test(list_insert);
	test(list_find);
	test(list_reverse);
	test(list_swap);
	test(list_each);
	test_finshed(list);

	getchar();
	return 0;
}

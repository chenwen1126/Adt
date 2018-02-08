# Overview
adt is Abstract Data Type With C.Provide list and so on.<br>

# ADT
## list
doubly linked list,provide method:<br>
#### list node create&destroy 
```c
/* list node create&destroy */
list_node_t* node_create(void* val);
void node_destroy(list_t *list, list_node_t* node);
```
#### list create&destroy 
```c
/* list create&destroy */
list_t* list_create();
void list_destroy(list_t*self);
```
#### list push&pop
```c
/* list push&pop */
void list_push_back(list_t*self, list_node_t* node);
void list_push_front(list_t*self, list_node_t* node);

list_node_t* list_pop_back(list_t*self);
list_node_t* list_pop_front(list_t*self);
```
#### list at&index
```c
/* list at&index */
list_node_t* list_at(list_t*self, int index);
int list_index(list_t* self, list_node_t* node);
```
#### list remove
```c
/* list remove */
void list_remove(list_t* self, list_node_t* node);
void list_remove_front(list_t* self);
void list_remove_back(list_t* self);
```
#### list insert
```c
/* list insert */
void list_insert_before(list_t* self, list_node_t* before, list_node_t* node);
void list_insert_after(list_t* self, list_node_t* after, list_node_t* node);
```
#### list find
```c
/* list find */
list_node_t* list_find(list_t* self, void* val);
list_node_t* list_find_reverse(list_t* self, void* val);
void list_insert_after(list_t* self, list_node_t* after, list_node_t* node);
```
#### list reverse
```c
/* list reverse */
void list_reverse(list_t* self);
```
#### list swap
```c
/* list swap */
void list_swap(list_t* self, list_node_t* node_a, list_node_t* node_b);
```
#### list foreach macro 
```c
/* list foreach */
list_each(node, list)
list_each_reverse(node, list)
```
# Test
## list
list unit test record:<br>
        ================== "list" unit test begin!!!=============== 
                       list_create test case pass!!!
                         list_push test case pass!!!
                          list_pop test case pass!!!
                      list_destroy test case pass!!!
                        list_index test case pass!!!
                       list_remove test case pass!!!
                       list_insert test case pass!!!
                         list_find test case pass!!!
                      list_reverse test case pass!!!
                         list_swap test case pass!!!
                         list_each test case pass!!!
        =========All "list" unit test done and 100% pass!!!========

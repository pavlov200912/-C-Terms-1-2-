#include "clist.h"
#include <stddef.h>
void init_list(struct intrusive_list *list){
    list->head = 0;
 }
void add_node(struct intrusive_list *list, intrusive_node *node){
    node->next = 0;
    node->prev = list->head;
    if(list->head){
        list->head->next = node;
    }
    list->head = node;
}
void remove_node(struct intrusive_list *list, intrusive_node *node){
    if(list->head == node)
        list->head = node->prev;
    if(node->next)
        node->next->prev = node->prev;
    if(node->prev)
        node->prev->next = node->next;
}

int get_length(struct intrusive_list *list) {
    int size = 0;
    struct intrusive_node *it = list->head;
    while(it){
        it = it->prev;
        size++;
    }
    return size;
}
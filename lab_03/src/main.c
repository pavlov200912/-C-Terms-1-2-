#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
struct position_node {
  int x, y;
  struct intrusive_node node;
};

void remove_position(intrusive_list *list, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node *it = list->head;
    struct position_node *p0;
    while(it){
        p0 = container_of(it, struct position_node, node);
        struct intrusive_node *copy = it->prev;
        if(p0->x == x && p0->y == y) {
            remove_node(list, it);
            free(p0);
        }
        it = copy;
    }
}

void add_position(struct intrusive_list *list, int x, int y) {
    struct position_node *new_node = malloc(sizeof(struct position_node));
    new_node->x = x;
    new_node->y = y;
    new_node->node.prev = 0;
    new_node->node.next = 0;
    add_node(list, &(new_node->node));
}

void show_all_positions(struct intrusive_list *list) {
    struct intrusive_node *it = list->head;
    struct position_node *p0;
    while(it){
        p0 = container_of(it, struct position_node, node);
        printf("(%d %d) ", p0->x, p0->y);
        it = it->prev;
    }
    printf("\n");
}

void remove_all_positions(struct intrusive_list *list) {
    struct intrusive_node *it = list->head;
    struct position_node *p0;
    while(it){
        p0 = container_of(it, struct position_node, node);
        remove_node(list, it);
        it = it->prev;
        free(p0);
    }
}

int main() {

     struct intrusive_list l;
     init_list(&l);
     char command[32];
     while(1) {
         scanf("%s", command);
         if(!strcmp(command, "add")) {
             int x, y;
             scanf("%d %d", &x, &y);
             add_position(&l, x, y);
         }
         else if(!strcmp(command, "rm")) {
             int x, y;
             scanf("%d %d", &x, &y);
             remove_position(&l, x, y);
         }
         else if(!strcmp(command, "print")) {
             show_all_positions(&l);
         }
         else if(!strcmp(command, "rma")) {
             remove_all_positions(&l);
         }
         else if(!strcmp(command, "len")) {
             printf("%d\n", get_length(&l));
         }
         else if(!strcmp(command, "exit")) {
             remove_all_positions(&l);
             return 0;
         }
         else
            printf("Unknown command\n");

     }
}

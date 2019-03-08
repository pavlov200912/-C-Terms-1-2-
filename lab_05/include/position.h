#ifndef _POSITION_12102014_
#define _POSITION_12102014_

#include "clist.h"

typedef struct position_node {
    int x;
    int y;
    intrusive_node node;
} position_node;

void remove_position(intrusive_list *list, int x, int y);

void add_position(intrusive_list *list, int x, int y);

void show_all_positions(intrusive_list *list);

void remove_all(intrusive_list *list);

position_node *get_position(intrusive_node *node);

#endif

#include "position.h"
#include <stdio.h>
#include <string.h>

void print(intrusive_node* node, void* data) {
    position_node* point_node = get_position(node);
    char* format = data;
    printf(format, point_node->x, point_node->y);
}

void count(intrusive_node* node, void* data) {
    int* c = data;
    (*c)++;
    data = c;
}

void save_text(intrusive_node* node, void* data) {
    FILE* fout = data;
    position_node* point_node = get_position(node);
    fprintf(fout, "%d %d\n", point_node->x, point_node->y);
}
void save_bin(intrusive_node* node, void* data) {
    FILE* fout = data;
    position_node *point_node = get_position(node);
    fwrite(&(point_node->x), sizeof(char) * 3, 1, fout);
    fwrite(&(point_node->y), sizeof(char) * 3, 1, fout);
}

void apply(intrusive_list* list, void(*op)(intrusive_node*, void*), void* data) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    while (node != head) {
        intrusive_node *next = node->next;
        op(node, data);
        node = next;
    }
}

int isEmpty(FILE* f) {
    fseek (f, 0, SEEK_END);
    int size = ftell(f);
    if (0 == size) {
        return 1;
    }
    fseek(f, 0, SEEK_SET);
    return 0;
}


int main(int argc, char* argv[]) {

    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);

    if (!strcmp(argv[1], "loadtext")) {
        FILE *fin = fopen(argv[2], "rt");
        if(isEmpty(fin)){
            printf("File is empty\n");
            return 0;
        }
        int x = 0, y = 0;
        while (fscanf(fin, "%d %d\n", &x, &y)) {
            add_position(l, x, y);
            if (feof(fin))
                break;
        }
        fclose(fin);
    } else {
        FILE* fin = fopen(argv[2], "rb");
        if(isEmpty(fin)){
            printf("File is empty\n");
            return 0;
        }
        int x = 0, y = 0;
        while (fread(&x, sizeof(char) * 3, 1, fin)) {
            fread(&y, sizeof(char) * 3, 1, fin);
            add_position(l, x, y);
            if (feof(fin))
                break;

        }
        fclose(fin);
    }

    if (!strcmp(argv[3], "print")) {

        char* format;
        format = argv[4];
        apply(&list, print, format);

    } else if (!strcmp(argv[3], "count")) {

        int point_count = 0;
        apply(&list, count, &point_count);
        printf("%d\n", point_count);

    } else if (!strcmp(argv[3], "savetext")) {

        char* file_name;
        file_name = argv[4];
        FILE* fout = fopen(file_name, "wt");
        apply(&list, save_text, fout);
        fclose(fout);

    } else if (!strcmp(argv[3], "savebin")) {

        char* file_name;
        file_name = argv[4];
        FILE* fout = fopen(file_name, "wb");
        apply(&list, save_bin, fout);
        fclose(fout);

    }
    remove_all(&list);
    return 0;
}

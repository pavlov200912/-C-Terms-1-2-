#include "phonebook.h"
#include <stdlib.h>
#include <expat.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "names.h"

#define BUFFER_SIZE 100000

int cmpfunc (const void * a, const void * b) {
    human_t *human_a = (human_t *)a;
    human_t *human_b = (human_t *)b;
    return strcmp(human_a->family_name, human_b->family_name);
}

void start_element(void *data, const char *element, const char **attribute) {
    data_t *my_data = data;
    my_data->is_phone = 0;
    if (!strcmp("human", element)) {
        my_data->human.phones_count = 0;
        for (int i = 0; i < 10; ++i) {
            my_data->human.phones[i][0] = '\0';
        }
        char *str = (char *)attribute[1];
        char *token = strtok(str, " ");
        int j = 0;
        while (token) {
            if (j == 0) strcpy(my_data->human.name, token);
            if (j == 1) strcpy(my_data->human.middle_name, token);
            if (j == 2) strcpy(my_data->human.family_name, token);
            token = strtok(NULL, " ");
            j++;
        }
    } else if (!strcmp("phone", element)) {
        my_data->is_phone = 1;
    }
}

void end_element(void *data, const char *element) {
    data_t *my_data = data;
    if (!strcmp(element, "human")) {
        push_back_human(my_data->phonebook, &(my_data->human));
    } else if (!strcmp("phone", element)) {
        my_data->is_phone = 0;
        my_data->human.phones_count++;
    }
}

void handle_data(void *data, const char *content, int length) {
    char *tmp = malloc(length + 1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    data_t *my_data = data;
    if (my_data->is_phone) {
        strcat(my_data->human.phones[my_data->human.phones_count], tmp);
    }
    free(tmp);
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {

    char *buff = malloc(sizeof(char) * BUFFER_SIZE);

    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    data_t data;
    data.phonebook = book;
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, &data);

    memset(buff, 0, BUFFER_SIZE);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), BUFFER_SIZE, fin);
        done = len < BUFFER_SIZE;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            XML_ParserFree(parser);
            fclose(fin);
            return 2;
        }
    } while (!done);

    qsort(book->humans, book->size, sizeof(human_t), cmpfunc);

    XML_ParserFree(parser);
    fclose(fin);
    free(buff);
    return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE* fout = fopen(filename, "w");

    if(fout == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    fprintf(fout, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fout, "<phonebook>\n");
    for(int i = 0; i < book->size; i++) {
        fprintf(fout, "    <human name=\"%s %s %s\">\n", book->humans[i].name,
                book->humans[i].middle_name, book->humans[i].family_name);
        human_t *human = &book->humans[i];
        for (int j = 0; j < human->phones_count; ++j) {
            fprintf(fout, "        <phone>%s</phone>\n", human->phones[j]);
        }
        fprintf(fout, "    </human>\n");
    }
    fprintf(fout, "</phonebook>\n");
    fclose(fout);
    return 0;
}

void print_phonebook(phonebook_t *book) {
    printf("%zd\n", book->size);
    for(int i = 0; i < book->size; i++) {
        printf("name: %s\nmiddle name: %s\nfamily_name: %s\n", book->humans[i].name,
                book->humans[i].middle_name, book->humans[i].family_name);
        human_t *human = &book->humans[i];
        for (int j = 0; j < human->phones_count; ++j) {
            printf("phone: %s\n", human->phones[j]);
        }
        printf("\n");
    }
}

void gen_phonebook(phonebook_t *book, size_t size) {
    clear_phonebook(book);
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        human_t *human = malloc(sizeof(human_t));
        strcpy(human->name, kNames[rand() % NAMES_CNT]);
        strcpy(human->middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(human->family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
        int count = rand() % 10;
        human->phones_count = count;
        for(int j = 0; j < count; j++) {
            char str[21];
            sprintf(str, "%d", rand() % (1000000000));
            human->phones[j][0] = '\0';
            strcpy(human->phones[j], str);
        }
        push_back_human(book, human);
        free(human);
    }
    qsort(book->humans, book->size, sizeof(human_t), cmpfunc);
}


void clear_phonebook(phonebook_t *book) {
    book->size = 0;
    book->capacity = 1;
    free(book->humans);
    book->humans = 0;
}


void push_back_human(phonebook_t *book, human_t *human) {
    if(book->size + 1 >= book->capacity) {
        book->humans = realloc(book->humans, sizeof(human_t) * 2 * (book->capacity));
        book->capacity *= 2;
    }
    *(book->humans + book->size) = *human;
    book->size++;
}




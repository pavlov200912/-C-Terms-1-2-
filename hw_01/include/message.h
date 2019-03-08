//
// Created by S_P_ on 20.11.18.
//

#ifndef CLION_MESSAGE_H
#define CLION_MESSAGE_H

#include "bmp.h"

#pragma pack(push,1) ///Turning off alignment

typedef struct Key_s{
    int x;
    int y;
    char component;
} Key_t;

#pragma pack(pop) ///Turning on alignment

int code_message(BMP_picture* out_pic, FILE *key_file, FILE *msg_file);

int code_bit(BMP_picture* picture, Key_t key, int bit);

void change_bit(char* value, int bit);

int get_first_bit(char *value);

int find_char_code(char msg_char);

int calculate_index(int width, int height, Key_t key);

int decode_msg(BMP_picture* picture, FILE *key_file, FILE *msg_file);

#endif //CLION_MESSAGE_H

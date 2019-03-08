#include <stdlib.h>
#include "message.h"


const int ALPHABET_POWER = 29;

const char ALPHABET[29] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                           'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '.', ','};


int code_message(BMP_picture* out_pic, FILE *key_file, FILE *msg_file) {
    Key_t key;
    char msg_char;
    while (fscanf(msg_file, "%c", &msg_char) != EOF) {
        int dex_code_char = find_char_code(msg_char);
        for (int i = 0; i < 5; ++i) {
            fscanf(key_file, "%d %d %c\n", &key.x, &key.y, &key.component);
            int bit = (dex_code_char) & 1;
            code_bit(out_pic, key, bit);
            dex_code_char = dex_code_char >> 1;
        }
    }
    return 0;
}

void change_bit(char* value, int bit) {
    int first_bit = get_first_bit(value);
    if(first_bit != bit) {
        *value ^= 1;
    }
}

int find_char_code(char msg_char) {
    for (int i = 0; i < ALPHABET_POWER; ++i) {
        if (ALPHABET[i] == msg_char) {
            return i;
        }
    }
    return 0;
}

int code_bit(BMP_picture* picture, Key_t key, int bit) {
    int height = picture->info_header.biHeight;
    int width = picture->info_header.biWidth;
    int index = calculate_index(width, height, key);

    if(key.component == 'B') {
        change_bit(&(picture->colors[index].rgbtBlue), bit);
    } else if(key.component == 'R') {
        change_bit(&(picture->colors[index].rgbtRed), bit);
    } else {
        change_bit(&(picture->colors[index].rgbtGreen), bit);
    }
    return 0;
}

int get_first_bit(char *value) {
    return (*value & 1);
}

int calculate_index(int width, int height, Key_t key) {
    int index = key.x + key.y * width;
    return index;
}


int decode_bit(BMP_picture* picture, Key_t key) {
    int height = picture->info_header.biHeight;
    int width = picture->info_header.biWidth;
    int index = calculate_index(width, height, key);

    if(key.component == 'B') {
        return get_first_bit(&(picture->colors[index].rgbtBlue));
    } else if(key.component == 'R') {
        return get_first_bit(&(picture->colors[index].rgbtRed));
    } else {
        return get_first_bit(&(picture->colors[index].rgbtGreen));
    }
}

int decode_msg(BMP_picture* picture, FILE *key_file, FILE *msg_file) {
    Key_t key;
    char msg_char;
    while (fscanf(key_file, "%d %d %c\n", &key.x, &key.y, &key.component) != EOF) {
        int coded_char_index = decode_bit(picture, key);
        for (int i = 1; i < 5; ++i) {
            fscanf(key_file, "%d %d %c\n", &key.x, &key.y, &key.component);
            coded_char_index += (decode_bit(picture, key) << i);
        }
        msg_char = ALPHABET[coded_char_index];
        fwrite(&msg_char, sizeof(char), 1, msg_file);
    }
    return 0;
}
#include "bmp.h"
#include <stdlib.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
const int ALIGNMENT_MODULE = 4;

BITMAPFILEHEADER read_file_header(FILE* fin) {
    BITMAPFILEHEADER file_header;
    fread(&file_header, sizeof(BITMAPFILEHEADER), 1, fin);
    return file_header;
}

BITMAPINFOHEADER read_info_header(FILE* fin) {
    BITMAPINFOHEADER info_header;
    fread(&info_header, sizeof(BITMAPINFOHEADER), 1, fin);
    return info_header;
}

int read_picture(FILE* fin, BMP_picture* picture) {

    picture->file_header = read_file_header(fin);
    picture->info_header = read_info_header(fin);

    fseek(fin, picture->file_header.bfOffBits, SEEK_SET); // Read after headers

    int width = picture->info_header.biWidth;
    int height = picture->info_header.biHeight;

    picture->colors = malloc(sizeof(RGBTRIPLE) * height * width);

    if(picture->colors == NULL) {
        return 1;
    }

    int row_size = get_row_size(width, picture->info_header.biBitCount);

    for (int i = height - 1; i >= 0; i--) { //Reversed loop because BMP store pixels from left upper corner
        for (int j = 0; j < width; ++j) {
            fread(&picture->colors[j + i * width], sizeof(RGBTRIPLE), 1, fin);
        }
        int delta = sizeof(RGBTRIPLE) * width; //Actual read data size
        if(delta < row_size) {
            fseek(fin, row_size - delta, SEEK_CUR);  //We don't need to read alignments, so we skip it
        }
    }

    return 0;
}

int crop_picture(BMP_picture* out_picture, BMP_picture* picture, int x, int y, int w, int h) {

    if(x + w > picture->info_header.biWidth ||
       y + h > picture->info_header.biHeight) {
        return 1;
    }

    out_picture->info_header = picture->info_header;
    out_picture->file_header = picture->file_header;

    out_picture->info_header.biHeight = h;
    out_picture->info_header.biWidth = w;

    out_picture->info_header.biXPelsPerMeter = picture->info_header.biYPelsPerMeter; //Swap X and Y because image rotated
    out_picture->info_header.biYPelsPerMeter = picture->info_header.biXPelsPerMeter;

    out_picture->colors = malloc(sizeof(RGBTRIPLE) * w * h);

    if(out_picture->colors == NULL) {
        return 1;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            out_picture->colors[j + i * w] = picture->colors[j + x + (y + i) * picture->info_header.biWidth];
        }
    }

    return 0;
}

int save_picture(FILE* fout, BMP_picture* picture) {

    int height = picture->info_header.biHeight;
    int width = picture->info_header.biWidth;

    int row_size = get_row_size(width, picture->info_header.biBitCount);

    picture->info_header.biSizeImage = height * row_size; // Size WITH alignment

    picture->file_header.bfSize = picture->info_header.biSizeImage + sizeof(BITMAPFILEHEADER) +
                                  sizeof(BITMAPINFOHEADER);

    fwrite(&picture->file_header, sizeof(BITMAPFILEHEADER), 1, fout);
    fwrite(&picture->info_header, sizeof(BITMAPINFOHEADER), 1, fout);

    fseek(fout, picture->file_header.bfOffBits, SEEK_SET); // Write after headers

    for (int i = height - 1; i >= 0; i--) { //Reversed loop because BMP store pixels from left upper corner
        for (int j = 0; j < width; ++j) {
            fwrite(&picture->colors[j + i * width], sizeof(RGBTRIPLE), 1, fout);
        }
        int delta = sizeof(RGBTRIPLE) * width; //Actual recorded data size
        if(delta < row_size) {
            char c = 0; // <- 1 byte of zero-bits
            int it = 0;
            while (it++ < row_size - delta) {
                fwrite(&c, 1, 1, fout); // Alignment are filling with zeros
            }
        }
    }


    return  0;
}

int rotate_picture(BMP_picture* picture) {

    int pic_width = picture->info_header.biWidth;
    int pic_height = picture->info_header.biHeight;

    RGBTRIPLE* new_colors = malloc(sizeof(RGBTRIPLE) * pic_width * pic_height);

    if(new_colors == NULL) {
        return 1;
    }

    /*
     * Rotation of picture is based on taking the remainder modulo
     * For example, if default map was :
     *  width = 4, height = 3
     *  [0, 1, 2, 3]
     *  [4, 5, 6, 7]  == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11] = F[0...11]
     *  [8, 9, 10, 11]
     *  Then after rotation:
     *  [8, 4, 0]
     *  [9, 5, 1]     == [8, 4, 0, 9, 5, 1, 10, 6, 2, 11, 7, 3] = S[0...11]
     *  [10, 6, 2]
     *  [11, 7, 3]
     *  So,
     *  S[0] - greatest value of F[0...11], such that (F[i] % width) == 0, S[0] = 8
     *  S[1] - second maximum, such that (F[i] % width) == 0, S[1] == 4
     *  ...
     *  S[3] - greatest value of F[0...11], such that (F[i] % width) == 1, S[3] = 9
     *  S[4] - second maximum, such that (F[i] % width) == 1, S[4] == 5
     *  And so on.
     */
    // Magic Happens here
    for(int i = 0; i < pic_width; i++) {
        int x = (pic_height - 1) * pic_width + i;
        for (int j = 0; j < pic_height; ++j) {
            new_colors[j + pic_height * i] = picture->colors[x];
            x -= pic_width;
        }
    }

    clear_picture(picture);

    picture->colors = new_colors;

    picture->info_header.biWidth = pic_height; // Swap height and width because new image is rotated
    picture->info_header.biHeight = pic_width;

    return  0;
}

void clear_picture(BMP_picture* picture) {
    free(picture->colors);
}

// You can read more about this formula here : [Pixel Storage] at https://en.wikipedia.org/wiki/BMP_file_format
int get_row_size(int width, int biBiCount) {
    int denominator = ALIGNMENT_MODULE * BITS_IN_BYTE;
    int row_size = ((biBiCount * width + denominator - 1) / denominator) * ALIGNMENT_MODULE; //round up size in bites
    return row_size;
}

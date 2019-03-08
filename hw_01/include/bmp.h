#ifndef CLION_BMP_H
#define CLION_BMP_H

#include <stdio.h>


#pragma pack(push,1) ///Turning off alignment

/// Structures with fields as in Microsoft Documentation

// Microsoft sucks

typedef unsigned int DWORD;
typedef int LONG;
typedef short WORD;
typedef char BYTE;

typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    DWORD bfReserved;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE;

typedef struct tagBMP_Picture {
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    RGBTRIPLE* colors;
} BMP_picture;

#pragma pack(pop) ///Turning on alignment

BITMAPFILEHEADER read_file_header(FILE* fin);

BITMAPINFOHEADER read_info_header(FILE* fin);

int read_picture(FILE* fin, BMP_picture* picture);

int crop_picture(BMP_picture* out_picture, BMP_picture* picture, int x, int y, int w, int h);

int save_picture(FILE* fout, BMP_picture* picture);

void clear_picture(BMP_picture* picture);

int rotate_picture(BMP_picture* picture);

/*** Function get_row_size:
 *
 * @param width - Width of picture in pixels
 * @param biBiCount - Amount of bits per single pixel
 * @return - Actual byte-size of one string WITH! alignments
 */
int get_row_size(int width, int biBiCount);

#endif //CLION_BMP_H

#include "bmp.h"
#include "message.h"
#include <string.h>
#include <stdlib.h>

int main(int args, char* argv[]) {
    BMP_picture picture;
    BMP_picture out;

    if(args < 2) {
        return 1;
    }

    if (!strcmp(argv[1], "crop-rotate")) {

        if (args < 8) {
            return 1;
        }

        FILE *fin = fopen(argv[2], "r");
        if (fin == NULL) {
            return 3;
        }

        if (read_picture(fin, &picture)) {
            return 4;
        }
        if (crop_picture(&out, &picture, atoi(argv[4]),
                         atoi(argv[5]), atoi(argv[6]), atoi(argv[7]))) {
            return 5;
        }
        fclose(fin);

        if (rotate_picture(&out)) {
            return 6;
        }

        FILE *fout = fopen(argv[3], "w");
        save_picture(fout, &out);
        fclose(fout);

        clear_picture(&out);
        clear_picture(&picture);
    } else if(!strcmp(argv[1], "insert")){
        if(args < 6) {
            return 1;
        }

        FILE *fin = fopen(argv[2], "r");
        FILE *fout = fopen(argv[3], "w");
        FILE *fkey = fopen(argv[4], "r");
        FILE *fmsg = fopen(argv[5], "r");

        if (fkey == NULL || fmsg == NULL) {
            return 3;
        }

        read_picture(fin, &picture);

        code_message(&picture, fkey, fmsg);

        save_picture(fout, &picture);
        clear_picture(&picture);
    } else if(!strcmp(argv[1], "extract")){
        if(args < 5) {
            return 1;
        }
        FILE *fin = fopen(argv[2], "r");
        FILE *fkey = fopen(argv[3], "r");
        FILE *fmsg = fopen(argv[4], "w");

        read_picture(fin, &picture);

        decode_msg(&picture, fkey, fmsg);

        clear_picture(&picture);
    } else {
        return 1;
    }
    return 0;
}

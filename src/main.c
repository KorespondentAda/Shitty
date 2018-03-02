
#include <stdio.h>

#include "../include/bitmap.h"

#define IMAGEPATH "img/img03.bmp"

int main() {

    printf("BITMAPINFO size = %lu: \t%s\n", sizeof(BITMAPINFO), sizeof(BITMAPINFO) == 124 ? "ok" : "error");

    printf("Reading image <%s>... ", IMAGEPATH);
    BITMAP bitmap;
    switch (BITMAPCreate(&bitmap, IMAGEPATH)) {
        case 0: {
            printf("successful\n");
            break;
        }
        case 1: {
            printf("error: couldn't open image.\n");
            return 1;
        }
        case 2: {
            printf("error: couldn't close image.\n");
            return 2;
        }
        case 3: {
            printf("error: <%s> is not bitmap image.\n", IMAGEPATH);
            return 3;
        }
        case 4: {
            printf("error: reading info error.\n");
            return 4;
        }
        default: {
            printf("error: unknown error.\n");
            return -1;
        }
    }

    printf("About <%s>: \n", IMAGEPATH);
    if (BITMAPOutInfo(&bitmap)) {
        printf("Error");
        return -1;
    }

    return 0;
}

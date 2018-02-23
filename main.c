
#include <stdio.h>

#include "bmp.h"

#define IMAGEPATH "img/img03.bmp"

int main() {

    printf("BITMAPCOREHEADER size = %ld: \t%s\n", sizeof(BITMAPCOREHEADER), sizeof(BITMAPCOREHEADER) == 12 ? "ok" : "error");
    printf("BITMAPINFOHEADER size = %ld: \t%s\n", sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER) == 40 ? "ok" : "error");
    printf("BITMAPV4HEADER size = %ld: \t%s\n", sizeof(BITMAPV4HEADER), sizeof(BITMAPV4HEADER) == 108 ? "ok" : "error");
    printf("BITMAPV5HEADER size = %ld: \t%s\n", sizeof(BITMAPV5HEADER), sizeof(BITMAPV5HEADER) == 124 ? "ok" : "error");

    FILE * image_file = fopen(IMAGEPATH, "r");
    if (image_file == NULL) {
        printf("Can not open image file <%s>...\n", IMAGEPATH);
        return 0;
    }

    BITMAPFILEHEADER BMPHEADER;
    fread(&BMPHEADER.bfType,        sizeof(BMPHEADER.bfType),       1, image_file);
    fread(&BMPHEADER.bfSize,        sizeof(BMPHEADER.bfSize),       1, image_file);
    fread(&BMPHEADER.bfReserved1,   sizeof(BMPHEADER.bfReserved1),  1, image_file);
    fread(&BMPHEADER.bfReserved2,   sizeof(BMPHEADER.bfReserved2),  1, image_file);
    fread(&BMPHEADER.bfOffBits,     sizeof(BMPHEADER.bfOffBits),    1, image_file);

    printf("bfType\t\t%d\nbfSize\t\t%d\nbfReserved1\t%d\nbfReserved2\t%d\nbfOffBits\t%d\n", 
        BMPHEADER.bfType, BMPHEADER.bfSize, BMPHEADER.bfReserved1, BMPHEADER.bfReserved2, BMPHEADER.bfOffBits);

    printf("File %sclosed.\n", fclose(image_file) == 0 ? "" : "not :) ");
    return 0;
}

#include <stdio.h>

#include "bmp.h"

int main() {

    printf("BITMAPCOREHEADER size = %d: \t%s\n", sizeof(BITMAPCOREHEADER), sizeof(BITMAPCOREHEADER) == 12 ? "ok" : "error");
    printf("BITMAPINFOHEADER size = %d: \t%s\n", sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER) == 40 ? "ok" : "error");
    printf("BITMAPV4HEADER size = %d: \t%s\n", sizeof(BITMAPV4HEADER), sizeof(BITMAPV4HEADER) == 108 ? "ok" : "error");
    printf("BITMAPV5HEADER size = %d: \t%s\n", sizeof(BITMAPV5HEADER), sizeof(BITMAPV5HEADER) == 124 ? "ok" : "error");

    return 0;
}
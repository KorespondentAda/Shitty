
#include <stdio.h>

#include "bitmap.h"

#define IMAGEPATH "img/img08.bmp"

void BITMAPCreate(BITMAP * bitmap, const char * path);

int main() {

    printf("BITMAPINFO size = %ld: \t%s\n", sizeof(BITMAPINFO), sizeof(BITMAPINFO) == 124 ? "ok" : "error");

    BITMAP bitmap;
    BITMAPCreate(&bitmap, IMAGEPATH);
    BITMAPInfoPrint(bitmap);
    // Выделение памяти под изображение.
    RGBQUAD ** image = (RGBQUAD **)malloc(bitmap.BMPInfo.biHeight);
    int i;
    for (i = 0; i < bitmap.BMPInfo.biHeight; ++i)
        image[i] = (RGBQUAD *)malloc(bitmap.BMPInfo.biWidth);
    // Размер отступа.
    int linePadding = ((bitmap.BMPInfo.biWidth * (bitmap.BMPInfo.biBitCount / 8)) % 4) & 3;
    printf("line padding == %d\n", linePadding);
    
    return 0;
}

void BITMAPCreate(BITMAP * bitmap, const char * path) {
    FILE * bitmap_file = fopen(path, "r");
    if (bitmap_file == NULL) {
        printf("<%s>: Can't open image file...\n", path);
        return;
    }
    
    fread(&bitmap->BMPHeader.bfType,        sizeof(bitmap->BMPHeader.bfType),       1, bitmap_file);
    if (bitmap->BMPHeader.bfType != 0x4D42 && bitmap->BMPHeader.bfType != 0x424D) {
        printf("<%s>: File is not bitmap image...", path);
        return;
    }
    fread(&bitmap->BMPHeader.bfSize,        sizeof(bitmap->BMPHeader.bfSize),       1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved1,   sizeof(bitmap->BMPHeader.bfReserved1),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved2,   sizeof(bitmap->BMPHeader.bfReserved2),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfOffBits,     sizeof(bitmap->BMPHeader.bfOffBits),    1, bitmap_file);
    
    // Reading V-CORE
    fread(&bitmap->BMPInfo.biSize,          sizeof(bitmap->BMPInfo.biSize),         1, bitmap_file);
    fread(&bitmap->BMPInfo.biWidth,         sizeof(bitmap->BMPInfo.biWidth),        1, bitmap_file);
    fread(&bitmap->BMPInfo.biHeight,        sizeof(bitmap->BMPInfo.biHeight),       1, bitmap_file);
    fread(&bitmap->BMPInfo.biPlanes,        sizeof(bitmap->BMPInfo.biPlanes),       1, bitmap_file);
    fread(&bitmap->BMPInfo.biBitCount,      sizeof(bitmap->BMPInfo.biBitCount),     1, bitmap_file);
    
    // Reading V-3
    if (bitmap->BMPInfo.biSize >= 40) {
        fread(&bitmap->BMPInfo.biCompression,   sizeof(bitmap->BMPInfo.biCompression),      1, bitmap_file);
        fread(&bitmap->BMPInfo.biSizeImage,     sizeof(bitmap->BMPInfo.biSizeImage),        1, bitmap_file);
        fread(&bitmap->BMPInfo.biXPelsPerMeter, sizeof(bitmap->BMPInfo.biXPelsPerMeter),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biYPelsPerMeter, sizeof(bitmap->BMPInfo.biYPelsPerMeter),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biClrUsed,       sizeof(bitmap->BMPInfo.biClrUsed),          1, bitmap_file);
        fread(&bitmap->BMPInfo.biClrImportant,  sizeof(bitmap->BMPInfo.biClrImportant),     1, bitmap_file);
    }

    // Reading V-3 with color masks
    if (bitmap->BMPInfo.biSize >= 52) {
        fread(&bitmap->BMPInfo.biRedMask,       sizeof(bitmap->BMPInfo.biRedMask),      1, bitmap_file);
        fread(&bitmap->BMPInfo.biGreenMask,     sizeof(bitmap->BMPInfo.biGreenMask),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biBlueMask,      sizeof(bitmap->BMPInfo.biBlueMask),     1, bitmap_file);
    }

    // Reading V-3 with alpha masks
    if (bitmap->BMPInfo.biSize >= 56) {
        fread(&bitmap->BMPInfo.biAlphaMask,     sizeof(bitmap->BMPInfo.biAlphaMask),    1, bitmap_file);
    }

    // Reading V-4
    if (bitmap->BMPInfo.biSize >= 108) {
        fread(&bitmap->BMPInfo.biRedMask,       sizeof(bitmap->BMPInfo.biRedMask),      1, bitmap_file);
        fread(&bitmap->BMPInfo.biGreenMask,     sizeof(bitmap->BMPInfo.biGreenMask),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biBlueMask,      sizeof(bitmap->BMPInfo.biBlueMask),     1, bitmap_file);
        fread(&bitmap->BMPInfo.biAlphaMask,     sizeof(bitmap->BMPInfo.biAlphaMask),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biCSType,        sizeof(bitmap->BMPInfo.biCSType),       1, bitmap_file);
        fread(&bitmap->BMPInfo.biEndpoints,     sizeof(bitmap->BMPInfo.biEndpoints),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaRed,      sizeof(bitmap->BMPInfo.biGammaRed),     1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaGreen,    sizeof(bitmap->BMPInfo.biGammaGreen),   1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaBlue,     sizeof(bitmap->BMPInfo.biGammaBlue),    1, bitmap_file);
    }

    // Reading V-5
    if (bitmap->BMPInfo.biSize >= 124) {
        fread(&bitmap->BMPInfo.biIntent,        sizeof(bitmap->BMPInfo.biIntent),         1, bitmap_file);
        fread(&bitmap->BMPInfo.biProfileData,   sizeof(bitmap->BMPInfo.biProfileData),         1, bitmap_file);
        fread(&bitmap->BMPInfo.biProfileSize,   sizeof(bitmap->BMPInfo.biProfileSize),         1, bitmap_file);
        fread(&bitmap->BMPInfo.biReserved,      sizeof(bitmap->BMPInfo.biReserved),         1, bitmap_file);
    }

    fclose(bitmap_file);
}
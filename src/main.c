
#include <stdio.h>

#include "../include/bitmap.h"

#define IMAGEPATH "img/img05.bmp"

int BITMAPCreate(BITMAP * bitmap, const char * path);

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
        default: {
            printf("error: unknown error.\n");
            return -1;
        }
    }

    BITMAPFILEHEADER file_header = bitmap.BMPHeader;
    BITMAPINFO       info_header = bitmap.BMPInfo;
    
    printf("\n\t--BITMAPFILEHEADER--\nbfType\t\t%X\nbfSize\t\t%d\nbfReserved1\t%d\nbfReserved2\t%d\nbfOffBits\t%d\n\n", 
        file_header.bfType, file_header.bfSize, file_header.bfReserved1, file_header.bfReserved2, file_header.bfOffBits);
    /*
    printf("\t--BITMAPINFO--\nbiSize\t\t%d\nbiWidth\t\t%d\nbiHeight\t%d\nbiPlanes\t%d\nbiBitCount\t%d\n\n",
        BMPINFO.biSize, BMPINFO.biWidth, BMPINFO.biHeight, BMPINFO.biPlanes, BMPINFO.biBitCount);

    if (BMPINFO.biSize >= 40) {
        printf("biCompression\t%d\nbiSizeImage\t%d\nbiXPelsPerMeter\t%d\nbiYPelsPerMeter\t%d\nbiClrUsed\t%d\nbiClrImportant\t%d\n\n",
            BMPINFO.biCompression, BMPINFO.biSizeImage, BMPINFO.biXPelsPerMeter, BMPINFO.biYPelsPerMeter, BMPINFO.biClrUsed, BMPINFO.biClrImportant);
    }

    if (BMPINFO.biSize >= 52) {
        printf("biRedMask\t%d\nbiGreenMask\t%d\nbiBlueMask\t%d\n", BMPINFO.biRedMask, BMPINFO.biGreenMask, BMPINFO.biBlueMask);
    }

    if (BMPINFO.biSize >= 56) {
        printf("biAlphaMask\t%d\n", BMPINFO.biAlphaMask);
    }

    if (BMPINFO.biSize >= 108) {
        printf("biCSType\t%d\nbiEndpoints:\n\tRed:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\n\tGreen:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\n\tBlue:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\nbiGammaRed\t%d\nbiGammaGreen\t%d\nbiGammaBlue\t%d\n\n",
            BMPINFO.biCSType,   (int)BMPINFO.biEndpoints.ciexyzRed.ciexyzX, 
                                (int)BMPINFO.biEndpoints.ciexyzRed.ciexyzY, 
                                (int)BMPINFO.biEndpoints.ciexyzRed.ciexyzZ, 
                                (int)BMPINFO.biEndpoints.ciexyzGreen.ciexyzX, 
                                (int)BMPINFO.biEndpoints.ciexyzGreen.ciexyzY, 
                                (int)BMPINFO.biEndpoints.ciexyzGreen.ciexyzZ, 
                                (int)BMPINFO.biEndpoints.ciexyzBlue.ciexyzX, 
                                (int)BMPINFO.biEndpoints.ciexyzBlue.ciexyzY, 
                                (int)BMPINFO.biEndpoints.ciexyzBlue.ciexyzZ, 
            BMPINFO.biGammaRed, BMPINFO.biGammaGreen, BMPINFO.biGammaBlue);
    }

    if (BMPINFO.biSize >= 124) {
        printf("biIntent\t%d\nbiProfileData\t%d\nbiProfileSize\t%d\nbiReserved\t%d\n\n",
            BMPINFO.biIntent, BMPINFO.biProfileData, BMPINFO.biProfileSize, BMPINFO.biReserved);
    }
    */
    return 0;
}

int BITMAPCreate(BITMAP * bitmap, const char * path) {
    FILE * bitmap_file = fopen(path, "r");
    if (bitmap_file == NULL) 
        return 1;
    
    fread(&bitmap->BMPHeader.bfType,        sizeof(bitmap->BMPHeader.bfType),       1, bitmap_file);
    if (bitmap->BMPHeader.bfType != 0x4D42 && bitmap->BMPHeader.bfType != 0x424D)
        return 3;
    fread(&bitmap->BMPHeader.bfSize,        sizeof(bitmap->BMPHeader.bfSize),       1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved1,   sizeof(bitmap->BMPHeader.bfReserved1),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved2,   sizeof(bitmap->BMPHeader.bfReserved2),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfOffBits,     sizeof(bitmap->BMPHeader.bfOffBits),    1, bitmap_file);
    
    // Reading V-CORE
//  if (BMPINFO.biSize >= 12)
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

    if (fclose(bitmap_file)) 
        return 2;
    
    return 0;
}
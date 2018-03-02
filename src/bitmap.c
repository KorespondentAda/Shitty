
#include "../include/bitmap.h"
#include <stdio.h>

int BITMAPCreate(BITMAP * bitmap, const char * path) {
    FILE * bitmap_file = fopen(path, "r");
    if (bitmap_file == NULL) 
        return 1;
    
    if (BITMAPReadHeader(bitmap, bitmap_file))
        return 3;

    if (BITMAPReadInfo(bitmap, bitmap_file))
        return 4;

    if (fclose(bitmap_file)) 
        return 2;
    
    return 0;
}

int BITMAPReadHeader(BITMAP * bitmap, FILE * bitmap_file) {
    fread(&bitmap->BMPHeader.bfType,        sizeof(bitmap->BMPHeader.bfType),       1, bitmap_file);
    if (bitmap->BMPHeader.bfType != 0x4D42 && bitmap->BMPHeader.bfType != 0x424D)
        return 3; //It is not BMP image
    fread(&bitmap->BMPHeader.bfSize,        sizeof(bitmap->BMPHeader.bfSize),       1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved1,   sizeof(bitmap->BMPHeader.bfReserved1),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfReserved2,   sizeof(bitmap->BMPHeader.bfReserved2),  1, bitmap_file);
    fread(&bitmap->BMPHeader.bfOffBits,     sizeof(bitmap->BMPHeader.bfOffBits),    1, bitmap_file);
    return 0;
}

int BITMAPReadInfo(BITMAP * bitmap, FILE * bitmap_file) {
    // Reading V-CORE
    //if (BMPINFO.biSize >= 12)
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
        fread(&bitmap->BMPInfo.biCSType,        sizeof(bitmap->BMPInfo.biCSType),       1, bitmap_file);
        fread(&bitmap->BMPInfo.biEndpoints,     sizeof(bitmap->BMPInfo.biEndpoints),    1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaRed,      sizeof(bitmap->BMPInfo.biGammaRed),     1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaGreen,    sizeof(bitmap->BMPInfo.biGammaGreen),   1, bitmap_file);
        fread(&bitmap->BMPInfo.biGammaBlue,     sizeof(bitmap->BMPInfo.biGammaBlue),    1, bitmap_file);
    }

    // Reading V-5
    if (bitmap->BMPInfo.biSize >= 124) {
        fread(&bitmap->BMPInfo.biIntent,        sizeof(bitmap->BMPInfo.biIntent),       1, bitmap_file);
        fread(&bitmap->BMPInfo.biProfileData,   sizeof(bitmap->BMPInfo.biProfileData),  1, bitmap_file);
        fread(&bitmap->BMPInfo.biProfileSize,   sizeof(bitmap->BMPInfo.biProfileSize),  1, bitmap_file);
        fread(&bitmap->BMPInfo.biReserved,      sizeof(bitmap->BMPInfo.biReserved),     1, bitmap_file);
    }
    return 0;
}

int BITMAPOutInfo(BITMAP * bitmap) {
    BITMAPFILEHEADER head = bitmap->BMPHeader;
    BITMAPINFO info = bitmap->BMPInfo;

    // Block 1
    if (0 > printf("\n\t--BITMAPFILEHEADER--\nbfType\t\t0x%X\nbfSize\t\t%d\nbfReserved1\t%d\nbfReserved2\t%d\nbfOffBits\t%d\n", 
            head.bfType, head.bfSize, head.bfReserved1, head.bfReserved2, head.bfOffBits))
        return 1;

    // Block 2
    if (0 > printf("\n\t--BITMAPINFO--\nbiSize\t\t%llu\nbiWidth\t\t%lld\nbiHeight\t%lld\nbiPlanes\t%u\nbiBitCount\t%u\n", 
             info.biSize, info.biWidth, info.biHeight, info.biPlanes, info.biBitCount))
        return 2;
    
    // Block 3
    if (info.biSize >= 40) {
        if (0 > printf("biCompression\t%llu\nbiSizeImage\t%llu\nbiXPelsPerMeter\t%lld\nbiYPelsPerMeter\t%lld\nbiClrUsed\t%llu\nbiClrImportant\t%llu\n", 
                info.biCompression, info.biSizeImage, info.biXPelsPerMeter, info.biYPelsPerMeter, info.biClrUsed, info.biClrImportant))
            return 3;
    }

    // Block 4
    if (info.biSize >= 52) {
        if (0 > printf("biRedMask\t0x%08X\nbiGreenMask\t0x%08X\nbiBlueMask\t0x%08X\n", 
                info.biGreenMask, info.biRedMask, info.biBlueMask))
            return 4;
    }

    // Block 5
    if (info.biSize >= 56) {
        if (0 > printf("biAlphaMask\t0x%08X\n", 
                info.biAlphaMask))
            return 5;
    }

    // Block 6
    if  (info.biSize >= 108) {
        if (0 > printf("biCSType\t0x%08X\nbiEndpoints: \nRed:\tX\t%llu\n\tY\t%lld\n\tZ\t%lld\nGreen:\tX\t%lld\n\tY\t%lld\n\tZ\t%lld\nBlue:\tX\t%lld\n\tY\t%lld\n\tZ\t%lld\nbiGammaRed\t%llu\nbiGammaGreen\t%llu\nbiGammaBlue\t%llu\n", 
                info.biCSType, info.biEndpoints.ciexyzRed.ciexyzX, info.biEndpoints.ciexyzRed.ciexyzY, info.biEndpoints.ciexyzRed.ciexyzZ, 
                info.biEndpoints.ciexyzGreen.ciexyzX, info.biEndpoints.ciexyzGreen.ciexyzY, info.biEndpoints.ciexyzGreen.ciexyzZ, 
                info.biEndpoints.ciexyzBlue.ciexyzX, info.biEndpoints.ciexyzBlue.ciexyzY, info.biEndpoints.ciexyzBlue.ciexyzZ, 
                info.biGammaRed, info.biGammaGreen, info.biGammaBlue))
            return 6;
    }

    // Block 7
    if (info.biSize >= 124) {
        if (0 > printf("biIntent\t%llu\nbiProfileData\t%llu\nbiProfileSize\t%llu\nbiReserved\t%llu\n", 
                info.biIntent, info.biProfileData, info.biProfileSize, info.biReserved))
            return 7;
    }

    return 0;
}
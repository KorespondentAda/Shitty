
#include <stdio.h>

#include "bmp.h"

#define IMAGEPATH "img/img09.bmp"

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
    printf("\t--BITMAPFILEHEADER--\nbfType\t\t%d\nbfSize\t\t%d\nbfReserved1\t%d\nbfReserved2\t%d\nbfOffBits\t%d\n\n", 
        BMPHEADER.bfType, BMPHEADER.bfSize, BMPHEADER.bfReserved1, BMPHEADER.bfReserved2, BMPHEADER.bfOffBits);

    BITMAPINFO BMPINFO;
//  if (BMPINFO.biSize >= 12)
    fread(&BMPINFO.biSize,          sizeof(BMPINFO.biSize),         1, image_file);
    fread(&BMPINFO.biWidth,         sizeof(BMPINFO.biWidth),        1, image_file);
    fread(&BMPINFO.biHeight,        sizeof(BMPINFO.biHeight),       1, image_file);
    fread(&BMPINFO.biPlanes,        sizeof(BMPINFO.biPlanes),       1, image_file);
    fread(&BMPINFO.biBitCount,      sizeof(BMPINFO.biBitCount),     1, image_file);

    printf("\t--BITMAPINFO--\nbiSize\t\t%d\nbiWidth\t\t%d\nbiHeight\t%d\nbiPlanes\t%d\nbiBitCount\t%d\n\n",
        BMPINFO.biSize, BMPINFO.biWidth, BMPINFO.biHeight, BMPINFO.biPlanes, BMPINFO.biBitCount);

    if (BMPINFO.biSize >= 40) {
        fread(&BMPINFO.biCompression,   sizeof(BMPINFO.biCompression),      1, image_file);
        fread(&BMPINFO.biSizeImage,     sizeof(BMPINFO.biSizeImage),        1, image_file);
        fread(&BMPINFO.biXPelsPerMeter, sizeof(BMPINFO.biXPelsPerMeter),    1, image_file);
        fread(&BMPINFO.biYPelsPerMeter, sizeof(BMPINFO.biYPelsPerMeter),    1, image_file);
        fread(&BMPINFO.biClrUsed,       sizeof(BMPINFO.biClrUsed),          1, image_file);
        fread(&BMPINFO.biClrImportant,  sizeof(BMPINFO.biClrImportant),     1, image_file);

        printf("biCompression\t%d\nbiSizeImage\t%d\nbiXPelsPerMeter\t%d\nbiYPelsPerMeter\t%d\nbiClrUsed\t%d\nbiClrImportant\t%d\n\n",
            BMPINFO.biCompression, BMPINFO.biSizeImage, BMPINFO.biXPelsPerMeter, BMPINFO.biYPelsPerMeter, BMPINFO.biClrUsed, BMPINFO.biClrImportant);
    }
    
    if (BMPINFO.biSize >= 108) {
        fread(&BMPINFO.biRedMask,       sizeof(BMPINFO.biRedMask),      1, image_file);
        fread(&BMPINFO.biGreenMask,     sizeof(BMPINFO.biGreenMask),    1, image_file);
        fread(&BMPINFO.biBlueMask,      sizeof(BMPINFO.biBlueMask),     1, image_file);
        fread(&BMPINFO.biAlphaMask,     sizeof(BMPINFO.biAlphaMask),    1, image_file);
        fread(&BMPINFO.biCSType,        sizeof(BMPINFO.biCSType),       1, image_file);
        fread(&BMPINFO.biEndpoints,     sizeof(BMPINFO.biEndpoints),    1, image_file);
        fread(&BMPINFO.biGammaRed,      sizeof(BMPINFO.biGammaRed),     1, image_file);
        fread(&BMPINFO.biGammaGreen,    sizeof(BMPINFO.biGammaGreen),   1, image_file);
        fread(&BMPINFO.biGammaBlue,     sizeof(BMPINFO.biGammaBlue),    1, image_file);

        printf("biRedMask\t%d\nbiGreenMask\t%d\nbiBlueMask\t%d\nbiAlphaMask\t%d\nbiCSType\t%d\nbiEndpoints:\n\tRed:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\n\tGreen:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\n\tBlue:\n\t\tX\t%d\n\t\tY\t%d\n\t\tZ\t%d\nbiGammaRed\t%d\nbiGammaGreen\t%d\nbiGammaBlue\t%d\n\n",
            BMPINFO.biRedMask, BMPINFO.biGreenMask, BMPINFO.biBlueMask, BMPINFO.biAlphaMask, BMPINFO.biCSType, (int)BMPINFO.biEndpoints.ciexyzRed.ciexyzX, 
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
        fread(&BMPINFO.biIntent,          sizeof(BMPINFO.biIntent),         1, image_file);
        fread(&BMPINFO.biProfileData,          sizeof(BMPINFO.biProfileData),         1, image_file);
        fread(&BMPINFO.biProfileSize,          sizeof(BMPINFO.biProfileSize),         1, image_file);
        fread(&BMPINFO.biReserved,          sizeof(BMPINFO.biReserved),         1, image_file);

        printf("biIntent\t%d\nbiProfileData\t%d\nbiProfileSize\t%d\nbiReserved\t%d\n\n",
            BMPINFO.biIntent, BMPINFO.biProfileData, BMPINFO.biProfileSize, BMPINFO.biReserved);
    }

    printf("File %sclosed.\n", fclose(image_file) == 0 ? "" : "not :) ");
    return 0;
}
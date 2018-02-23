
#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef uint8_t     BYTE;
typedef uint16_t    WORD;
typedef uint32_t    DWORD;
typedef int32_t     LONG;
// TODO!
typedef long        FXPT2DOT30;

typedef struct tagCIEXYZ {
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct tagCIEXYZTRIPLE {
  CIEXYZ ciexyzRed;
  CIEXYZ ciexyzGreen;
  CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFO {
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;

    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;

    DWORD   biRedMask;
    DWORD   biGreenMask;
    DWORD   biBlueMask;
    DWORD   biAlphaMask;
    DWORD   biCSType;
    CIEXYZTRIPLE    biEndpoints;
    DWORD   biGammaRed;
    DWORD   biGammaGreen;
    DWORD   biGammaBlue;

    DWORD   biIntent;
    DWORD   biProfileData;
    DWORD   biProfileSize;
    DWORD   biReserved;
} BITMAPINFO;

typedef struct tagBITMAP {
    BITMAPFILEHEADER    BMPHeader;
    BITMAPINFO          BMPInfo;
} BITMAP;

#endif
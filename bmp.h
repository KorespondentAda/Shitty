
#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>

#define BI_RGB              0
#define BI_RLE8             1
#define BI_RLE4             2
#define BI_BITFIELDS        3
#define BI_JPEG             4
#define BI_PNG              5
#define BI_ALPHABITFIELDS   6

typedef uint8_t     BYTE;
typedef uint16_t    WORD;
typedef uint32_t    DWORD;
typedef int32_t     LONG;

typedef int        FXPT2DOT30;

typedef struct {
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
  CIEXYZ ciexyzRed;
  CIEXYZ ciexyzGreen;
  CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    DWORD   bcSize;
    WORD    bcWidth;
    WORD    bcHeight;
    WORD    bcPlanes;
    WORD    bcBitCount;
} BITMAPCOREHEADER; 

typedef struct {
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
} BITMAPINFOHEADER;

typedef struct {
    DWORD   bV4Size;
    LONG    bV4Width;
    LONG    bV4Height;
    WORD    bV4Planes;
    WORD    bV4BitCount;

    DWORD   bV4Compression; // or bV4V4Compression? check it, pls
    DWORD   bV4SizeImage;
    LONG    bV4XPelsPerMeter;
    LONG    bV4YPelsPerMeter;
    DWORD   bV4ClrUsed;
    DWORD   bV4ClrImportant;

    DWORD   bV4RedMask;
    DWORD   bV4GreenMask;
    DWORD   bV4BlueMask;
    DWORD   bV4AlphaMask;
    DWORD   bV4CSType;
    CIEXYZTRIPLE    bV4Endpoints;
    DWORD   bV4GammaRed;
    DWORD   bV4GammaGreen;
    DWORD   bV4GammaBlue
} BITMAPV4HEADER;

typedef struct {
    DWORD   bV5Size;
    LONG    bV5Width;
    LONG    bV5Height;
    WORD    bV5Planes;
    WORD    bV5BitCount;

    DWORD   bV5Compression;
    DWORD   bV5SizeImage;
    LONG    bV5XPelsPerMeter;
    LONG    bV5YPelsPerMeter;
    DWORD   bV5ClrUsed;
    DWORD   bV5ClrImportant;

    DWORD   bV5RedMask;
    DWORD   bV5GreenMask;
    DWORD   bV5BlueMask;
    DWORD   bV5AlphaMask;
    DWORD   bV5CSType;
    CIEXYZTRIPLE    bV5Endpoints;
    DWORD   bV5GammaRed;
    DWORD   bV5GammaGreen;
    DWORD   bV5GammaBlue;

    DWORD   bV5Intent;
    DWORD   bV5ProfileData;
    DWORD   bV5ProfileSize;
    DWORD   bV5Reserved;
} BITMAPV5HEADER;

typedef struct {
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;

typedef struct {
    BYTE    rgbtBlue;
    BYTE    rgbtGreen;
    BYTE    rgbtRed;
} RGBTRIPLE;

#endif

#ifndef __BITMAPDEF_HPP__
#define __BITMAPDEF_HPP__

#include <cstdint>

// Compression
#define BI_RGB              0
#define BI_RLE8             1
#define BI_RLE4             2
#define BI_BITFIELDS        3
#define BI_JPEG             4
#define BI_PNG              5
#define BI_ALPHABITFIELDS   6

// CSType
#define LCS_CALIBRATED_RGB      0x00000000
#define LCS_sRGB                0x73524742
#define LCS_WINDOWS_COLOR_SPACE 0x57696E20
#define PROFILE_LINKED          0x4C494E4B
#define PROFILE_EMBEDDED        0x4D424544

typedef uint8_t     BYTE;
typedef uint16_t    WORD;
typedef uint32_t    DWORD;
typedef int32_t     LONG;
typedef LONG        FXPT2DOT30;
typedef LONG        FXPT16DOT16;

struct CIEXYZ {
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
};

struct CIEXYZTRIPLE {
  CIEXYZ ciexyzRed;
  CIEXYZ ciexyzGreen;
  CIEXYZ ciexyzBlue;
};

struct BITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
};

struct BITMAPINFO {
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
};

struct RGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
};

struct RGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
};

#endif

#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include <cstdint>
#include <cstdio>
#include <fstream>

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

class Bitmap {
private:
    BITMAPFILEHEADER    header;
    BITMAPINFO          info;
    RGBQUAD **          image;
    
    int readHeader(std::ifstream & inStream);
    int readInform(std::ifstream & inStream);
    int readPictur(std::ifstream & inStream);

    int writeHeader(std::ifstream & outStream);
    int writeInform(std::ofstream & outStream);
    int writePictur(std::ifstream & outStream);
    
public:
    Bitmap();

    Bitmap(const bitmap & bm);
    Bitmap(bitmap && bm);

    Bitmap & operator=(const Bitmap & bm);
    Bitmap & operator=(Bitmap && bm);

    // Загрузка изображения из файла.
    // path - путь к изображению.
    int load(const string & path);
    // Сохранение изображения в файл.
    // path - путь к изображению.
    int save(const string & path);
    // Рисование прямоугольника.
    // (x; y) - координаты верхнего левого угла.
    // lineWidth - ширина линий.
    // lineColor - цвет линий.
    // isSolid - c заливкой или без.
    // solidColor - если isSolid == true, то цвет заливки, иначе - не использовать.
    int draw(int x, int y, int lineWidth, int lineColor, int isSolid, int solidColor);
    // Рисование рамки.
    // pattern - узор из набора констант (всякие фракталы, тип)
    // color - цвет рамки.
    // width - ширина рамки.
    int frame(int pattern, int color, int width);
    // Поворот части изображения.
    // (x, y) - координаты верхнего левого угла.
    // width - длина выбранной части.
    // height - ширина выбранной части.
    // angle - угол, кратный 90 градусам.
    int flip(int x, int y, int width, int height, int angle);

    ~Bitmap();
};

#endif // __BITMAP_HPP__
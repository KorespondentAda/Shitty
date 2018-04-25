
#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include "bitmapdef.h"

#include <cstdio>
#include <string>
#include <fstream>

class Bitmap {
private:
    BITMAPFILEHEADER    header;
    BITMAPINFO          inform;
    RGBTRIPLE **        picture;
    RGBTRIPLE *         palette;

    int readHeader(std::ifstream & inStream);
    int readInform(std::ifstream & inStream);
    int readPalette(std::ifstream & inStream);
    int readPicture(std::ifstream & inStream);
    
    int writeHeader(std::ofstream & outStream);
    int writeInform(std::ofstream & outStream);
    int writePalette(std::ofstream & outStream);
    int writePicture(std::ofstream & outStream);

    int checkType();
    int linePadding();
    int paletteSize();

    BYTE bitExtract(DWORD byte, DWORD mask);

public:
    Bitmap();

    Bitmap(const Bitmap & bm);
    Bitmap(Bitmap && bm);

    Bitmap & operator=(const Bitmap & bm);
    Bitmap & operator=(Bitmap && bm);
    
    int load(const std::string & path);
    int save(const std::string & path);
    
    int draw_pixel(LONG x, LONG y, RGBTRIPLE color);
    int draw_line(LONG x1, LONG y1, LONG x2, LONG y2, RGBTRIPLE color);

    int draw(int x, int y, int lineWidth, int lineColor, int isSolid, int solidColor);
    int frame(int pattern, int color, int width);
    int flip(int x, int y, int dx, int dy, int angle);
    int flip();
    
    void print_info();

    void test();
    
    ~Bitmap();
};

template <typename Type, size_t size>
void read(std::ifstream & inStream, Type & value) {
    inStream.read(reinterpret_cast<char *>(&value), size);
}
template <typename Type, size_t size>
void write(std::ofstream & outStream, Type value) {
    outStream.write(reinterpret_cast<char *>(&value), size);
}

template <typename Type>
void read(std::ifstream & inStream, Type & value) {
    inStream.read(reinterpret_cast<char *>(&value), sizeof(value));
}

template <typename Type>
void write(std::ofstream & outStream, Type value) {
    outStream.write(reinterpret_cast<char *>(&value), sizeof(value));
}

#endif // __BITMAP_HPP__
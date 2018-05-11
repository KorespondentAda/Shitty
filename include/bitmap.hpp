
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
    RGBTRIPLE pen_color;
    RGBTRIPLE brush_color;

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
    void draw_hor_line(LONG x1, LONG x2, LONG y);
    void draw_ver_line(LONG y1, LONG y2, LONG x);
    void draw_hor_line(LONG x1, LONG x2, LONG y, LONG width);
    void draw_ver_line(LONG y1, LONG y2, LONG x, LONG width);
public:
    Bitmap();

    Bitmap(const Bitmap & bm);
    Bitmap(Bitmap && bm);

    Bitmap & operator=(const Bitmap & bm);
    Bitmap & operator=(Bitmap && bm);
    
    int load(const std::string & path);
    int save(const std::string & path);
    
    void set_pen_color(RGBTRIPLE color);
    void set_brush_color(RGBTRIPLE color);

    void draw_pixel(LONG x, LONG y);
    void draw_pixel(LONG x, LONG y, RGBTRIPLE c);
    void draw_pixel(LONG x, LONG y, LONG r);

    void draw_line(LONG x1, LONG y1, LONG x2, LONG y2);
    void draw_line(LONG x1, LONG y1, LONG x2, LONG y2, LONG width);

    void draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2);
    void draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, LONG width);
    void draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, LONG width, bool filled);
    void draw_fill_rectangle(LONG x1, LONG y1, LONG x2, LONG y2);
	
    void fractal_1(LONG x1, LONG y1, LONG x2, LONG y2);
    void fractal_2(LONG x1, LONG y1, LONG x2, LONG y2);

    void flip();
    void flip(LONG x1, LONG y1, LONG x2, LONG y2);

    int frame(int pattern, int color, int width);
    
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

template <typename Type>
void swap(Type & a, Type & b) {
    Type temp = a;
    a = b;
    b = temp;
}

template <typename Type>
Type half(Type value) {
    return (value >> 1);
}

#endif // __BITMAP_HPP__


#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include "bitmapdef.hpp"

#include <cstdint>
#include <cstdio>
#include <fstream>

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
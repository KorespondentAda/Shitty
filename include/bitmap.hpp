
#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include "bitmapdef.hpp"

#include <cstdio>
#include <string>
#include <fstream>

class Bitmap {
private:
    BITMAPFILEHEADER    header;
    BITMAPINFO          inform;
    RGBQUAD **          image;
    
    int readHeader(std::ifstream & inStream);
    int readInform(std::ifstream & inStream);
    int readPictur(std::ifstream & inStream);

    int writeHeader(std::ofstream & outStream);
    int writeInform(std::ofstream & outStream);
    int writePictur(std::ofstream & outStream);

    int checkType(WORD bfType);
    BYTE bitExtract(BYTE byte, DWORD mask);

public:
    Bitmap();

    Bitmap(const Bitmap & bm);
    Bitmap(Bitmap && bm);

    Bitmap & operator=(const Bitmap & bm);
    Bitmap & operator=(Bitmap && bm);
    /**
     * \brief Загружает изображение из файла
     * 
     * \param[in] path - путь к файлу
     * \return 0, если загрузка прошла успешно
    */
    int load(const std::string & path);
    /**
     * \brief Сохраняет изображение в файл
     * 
     * \param[in] path - путь к файлу
     * \return 0, если сохранение прошло успешно
    */
    int save(const std::string & path);
    /**
     * \brief Рисует прямоугольник
     * 
     * \param[in] x - первая координата левого-верхнего угла
     * \param[in] y - вторая координата левого-верхнего угла
     * \param[in] lineWidth - ширина линий
     * \param[in] lineColor - цвет линий
     * \param[in] isSolid - флаг, требуется ли заливка для прямоугольика
     * \param[in] solidColor - цвет заливки, используется, если isSolid = true
     * \return 0, если рисование прошло успешно
    */
    int draw(int x, int y, int lineWidth, int lineColor, int isSolid, int solidColor);
    /**
     * \brief Рисует рамку изображения.
     * 
     * \param[in] pattern - узор рамки
     * \param[in] color - цвет рамки
     * \param[in] width - ширина рамки
     * \return 0, если рисование прошло успешно
    */
    int frame(int pattern, int color, int width);
    /**
     * \brief Поворот части изображения.
     * 
     * \param[in] x - абсцисса левого-верхнего угла
     * \param[in] y - ордината левого-верхнего угла
     * \param[in] width - ширина рамки
     * \param[in] height - ширина выбранной части
     * \param[in] angle - угол, кратный 90 градусам
     * \return 0, если поворот прошёл успешно
    */
    int flip(int x, int y, int width, int height, int angle);

    ~Bitmap();
};

template <typename Type>
void read(std::ifstream & inStream, Type & result) {
    inStream.read(reinterpret_cast<char*>(&result), sizeof(result));
}
 
#endif // __BITMAP_HPP__
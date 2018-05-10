
#include "../include/bitmap.hpp"

#include <cstring>

const RGBTRIPLE BLACK = { 0, 0, 0 };
const RGBTRIPLE WHITE = { 255, 255, 255 };
const RGBTRIPLE RED = { 0, 0, 255 };
const RGBTRIPLE GREEN = { 0, 255, 0 };
const RGBTRIPLE BLUE = { 255, 0, 0 };
const RGBTRIPLE YELLOW = { 0, 255, 255 };
const RGBTRIPLE PINK = { 255, 0, 255 };
const RGBTRIPLE SKY = { 255, 255, 0 };
const RGBTRIPLE BROWN = { 0, 0, 127 };

int main(/*int argc, char * argv[]*/) {
    Bitmap image;
    image.load("img/img08.bmp");
    RGBTRIPLE color = { 0, 0, 255 };
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            image.draw_pixel(5 + i, 5 + j, color);
    image.draw_pixel(100, 100, PINK, 30);
    image.draw_line(5, 5, 100, 50, RED);
    image.draw_line(8, 20, 100, 50, YELLOW, 7);
    image.draw_rectangle(15, 15, 100, 50, RED, 3);
    printf("%d %d %d\n", color.rgbtBlue, color.rgbtGreen, color.rgbtRed);
    image.flip();
    image.draw_ver_line(-10, 100, 30, BROWN, 4);
    image.draw_hor_line(10, 500, 90, SKY, 2);
    image.save("result.bmp");
    return 0;
}

// -l <filename>
// --load <filename>

// -s <filename>
// --save <filename>

// --flip

// --rectangle <x> <y> <width> <height> 

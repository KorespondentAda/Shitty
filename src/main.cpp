
#include "../include/bitmap.hpp"

#include <cstring>

const RGBTRIPLE BLACK = { 0, 0, 0 };
const RGBTRIPLE WHITE = { 255, 255, 255 };
const RGBTRIPLE RED = { 0, 0, 255 };
const RGBTRIPLE LIME = { 0, 255, 0 };
const RGBTRIPLE BLUE = { 255, 0, 0 };
const RGBTRIPLE YELLOW = { 0, 255, 255 };
const RGBTRIPLE PINK = { 255, 0, 255 };
const RGBTRIPLE SKY = { 255, 255, 0 };
const RGBTRIPLE BROWN = { 0, 0, 127 };

int main(/*int argc, char * argv[]*/) {
    Bitmap image;
    image.load("img/img08.bmp");

    //image.draw_pixel(100, 100, 30);
    /*
    image.set_pen_color(RED);
    image.draw_line(5, 5, 100, 50);
    image.set_pen_color(YELLOW);
    image.draw_line(8, 20, 100, 50, 7);
    image.set_pen_color(RED);
    image.draw_rectangle(15, 15, 100, 50, 3);
    //image.flip();
    image.set_pen_color(BROWN);
    image.draw_ver_line(-10, 100, 30, 4);
    image.set_pen_color(SKY);
    image.draw_hor_line(10, 500, 90, 2);
    image.set_pen_color(BLUE);
    image.set_brush_color(YELLOW);
    image.draw_rectangle(-70, 70, 100, 120, 5, true);
    */
    image.set_pen_color(PINK);
    image.set_brush_color(YELLOW);
    image.fractal_2(20, 20, 160, 160);

    /*
    image.draw_pixel(60, 40, 10);
    image.draw_pixel(160, 140, 10);
    */
    image.flip();
    image.save("result.bmp");
    return 0;
}

// -l <filename>
// --load <filename>

// -s <filename>
// --save <filename>

// --flip

// --rectangle <x> <y> <width> <height> 

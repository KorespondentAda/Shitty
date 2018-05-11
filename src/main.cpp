
#include "../include/bitmap.hpp"
#include "../include/colors.hpp"

#include <unistd.h>
#include <getopt.h>
#include <cstring>

int main(/*int argc, char * argv[]*/) {
    Bitmap image;
    image.load("img/img08.bmp");
    
    // default pen_color == BLACK; brush_color == WHITE
    image.draw_rectangle(30, 40, 100, 150, 7, true);

    // rotate piece of image
    image.flip(25, 35, 105, 155);

    image.set_brush_color(colors::LIME);
    image.fractal_2(130, 50, 210, 130);

    // rotate __POLOTNO__
    image.flip();

    image.save("result.bmp");
    return 0;
}
/*
    -h  --help
    -l  --load
        char * filename;
    -s  --save
        char * filename;
    --pen_color
        RGBTRIPLE color;
    --brush_color   
        RGBTRIPLE color;
    -p  --pixel
        LONG x;
        LONG y;
    --line
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
        LONG width;
    -r  --rectangle
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
        LONG width;
    --filled_rectangle
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
        LONG width;
    --circle
        LONG x;
        LONG y;
        LONG r;
        LONG width;
    --filled_circle
        LONG x;
        LONG y;
        LONG r;
        LONG width;
    -f  --flip
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
        LONG count;
*/
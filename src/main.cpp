
#include "../include/bitmap.hpp"

#include <cstring>

int main(int argc, char * argv[]) {
    Bitmap image;
    image.load("img/img08.bmp");
    image.print_info();
    RGBTRIPLE color = { 0, 0, 255 };
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            image.draw_pixel(5 + i, 5 + j, color);
    
    image.draw_line(5, 5, 100, 50, color);
    
    printf("%d %d %d\n", color.rgbtBlue, color.rgbtGreen, color.rgbtRed);
    image.save("result.bmp");
    return 0;
}

// -l <filename>
// --load <filename>

// -s <filename>
// --save <filename>

// --flip

// --rectangle <x> <y> <width> <height> 

#include "../include/bitmap.hpp"

int main(int argc, char * argv[]) {
    
    Bitmap bm = Bitmap();
    bm.load(argv[1]);
    bm.save("meow.bmp");

    return 0;
}
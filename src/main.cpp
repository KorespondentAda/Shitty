
#include "../include/bitmap.hpp"

int main(int argc, char * argv[]) {
    
    Bitmap bm = Bitmap();
    bm.load(argv[1]);
    bm.test();
    bm.save("meow.bmp");
    
    for (int i = 0; i < argc; ++i) {
        
    }
    return 0;
}

// -l <filename>
// --load <filename>

// -s <filename>
// --save <filename>

// --flip

// --rectangle <x> <y> <width> <height> 
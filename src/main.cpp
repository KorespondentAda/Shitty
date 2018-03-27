
#include "../include/bitmap.hpp"
#include <string>

const std::string path = "./img/img10.bmp";

int main(int argc, char * argv[]) {
    
    Bitmap bm = Bitmap();
    bm.load(argv[1]);
    bm.save("./img/output.bmp");    
    return 0;
}
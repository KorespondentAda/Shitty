
#include "bitmap.hpp"

int Bitmap::readHeader(std::ifstream & inStream) {

}

int Bitmap::readInform(std::ifstream & inStream) {

}

int Bitmap::writeHeader(std::ifstream & outStream) {
    
}

int Bitmap::writeInform(std::ofstream & outStream) {

}

int Bitmap::load(const string & path) {
    
    std::ifstream inStream(path);
    if (!inStream.is_open())
        return 1;
    
    readHeader(inStream);
    readInform(inStream);
    readPictur(inStream);

    inStream.close();
    
    return 0;
}

int Bitmap::save(const string & path) {

    std::ofstream outStream(path);
    if (!outStream.is_open())
        return 1;
    
    writeHeader(outStream);
    writeInform(outStream);
    writePictur(outStream);
    
    outStream.close();
    
    return 0;
}
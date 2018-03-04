
#include "bitmap.hpp"

int Bitmap::readHeader(std::ifstream & inStream) {
    read(inStream, header.bfType);
    if (checkType(header.bfType))
        return 3;
    read(inStream, header.bfSize);
    read(inStream, header.bfReserved1);
    read(inStream, header.bfReserved2);
    read(inStream, header.bfOffBits);
    return 0;
}

int Bitmap::readInform(std::ifstream & inStream) {
    read(inStream, inform.biSize);
    read(inStream, inform.biWidth);
    read(inStream, inform.biHeight);
    read(inStream, inform.biPlanes);
    read(inStream, inform.biBitCount);
    if (inform.biSize >= 40) {
        read(inStream, inform.biCompression);
        read(inStream, inform.biSizeImage);
        read(inStream, inform.biXPelsPerMeter);
        read(inStream, inform.biYPelsPerMeter);
        read(inStream, inform.biClrUsed);
        read(inStream, inform.biClrImportant);
    }
    if (inform.biSize >= 52) {
        read(inStream, inform.biRedMask);
        read(inStream, inform.biGreenMask);
        read(inStream, inform.biBlueMask);
    }
    if (inform.biSize >= 56) {
        read(inStream, inform.biAlphaMask);
    }
    if (inform.biSize >= 108) {
        read(inStream, inform.biCSType);
        read(inStream, inform.biEndpoints);
        read(inStream, inform.biGammaRed);
        read(inStream, inform.biGammaGreen);
        read(inStream, inform.biGammaBlue);
    }
    if (inform.biSize >= 124) {
        read(inStream, inform.biIntent);
        read(inStream, inform.biProfileData);
        read(inStream, inform.biProfileSize);
        read(inStream, inform.biReserved);
    }
    return 0;
}

int Bitmap::readPictur(std::ifstream & inStream) {
    image = new RGBQUAD *[inform.biHeight];
    for (int i = 0; i < inform.biHeight; ++i) 
        image[i] = new RGBQUAD[inform.biWidth];
    
    WORD bytesPerPixel = inform.biBitCount >> 3;
    BYTE buffer[bytesPerPixel];
    for (int i = 0; i < inform.biHeight; ++i) 
        for (int j = 0; j < inform.biWidth; ++j) {
            read(fileStream, buffer);
            image[i][j].rgbBlue     = bitExtract(buffer, inform.biRedMask);
            image[i][j].rgbGreen    = bitExtract(buffer, inform.biGreenMask);
            image[i][j].rgbRed      = bitExtract(buffer, inform.biBlueMask);
            image[i][j].rgbReserved = bitExtract(buffer, inform.biAlphaMask);
        }
}

int Bitmap::writeHeader(std::ifstream & outStream) {
}

int Bitmap::writeInform(std::ofstream & outStream) {
}

int Bitmap::writePictur(std::ofstream & outStream) {
}

int Bitmap::checkType(WORD bfType) {
    return (bfType == 0x4D42 || bfType == 0x424D);
}

BYTE Bitmap::bitExtract(BYTE byte, DWORD mask) {
    if (mask == 0) {
        return 0;
    } 
    DWORD   maskBuffer = mask,
    int     maskPadding = 0;
    while (!(maskBufer & 1)) {
        maskBufer >>= 1;
        ++maskPadding;
    }
    return (byte & mask) >> maskPadding;
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
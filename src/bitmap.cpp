
#include "../include/bitmap.hpp"

Bitmap::Bitmap() {
}

int Bitmap::readHeader(std::ifstream & inStream) {
    read(inStream, header.bfType);
    if (!checkType())
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
    /*
    pictur = new RGBQUAD *[inform.biHeight];
    for (int i = 0; i < inform.biHeight; ++i) 
        pictur[i] = new RGBQUAD[inform.biWidth];
    */
    /* To debug
    WORD bytesPerPixel = inform.biBitCount >> 3;
    BYTE buffer[bytesPerPixel];
    for (int i = 0; i < inform.biHeight; ++i) 
        for (int j = 0; j < inform.biWidth; ++j) {
            read(inStream, buffer);
            image[i][j].rgbBlue     = bitExtract(buffer, inform.biRedMask);
            image[i][j].rgbGreen    = bitExtract(buffer, inform.biGreenMask);
            image[i][j].rgbRed      = bitExtract(buffer, inform.biBlueMask);
            image[i][j].rgbReserved = bitExtract(buffer, inform.biAlphaMask);
        }*/
    return 0;
}

int Bitmap::writeHeader(std::ofstream & outStream) {
    write(outStream, header.bfType);
    write(outStream, header.bfSize);
    write(outStream, header.bfReserved1);
    write(outStream, header.bfReserved2);
    write(outStream, header.bfOffBits);
    return 0;
}

int Bitmap::writeInform(std::ofstream & outStream) {
    write(outStream, inform.biSize);
    write(outStream, inform.biWidth);
    write(outStream, inform.biHeight);
    write(outStream, inform.biPlanes);
    write(outStream, inform.biBitCount);
    if (inform.biSize >= 40) {
        write(outStream, inform.biCompression);
        write(outStream, inform.biSizeImage);
        write(outStream, inform.biXPelsPerMeter);
        write(outStream, inform.biYPelsPerMeter);
        write(outStream, inform.biClrUsed);
        write(outStream, inform.biClrImportant);
    }
    if (inform.biSize >= 52) {
        write(outStream, inform.biRedMask);
        write(outStream, inform.biGreenMask);
        write(outStream, inform.biBlueMask);
    }
    if (inform.biSize >= 56) {
        write(outStream, inform.biAlphaMask);
    }
    if (inform.biSize >= 108) {
        write(outStream, inform.biCSType);
        write(outStream, inform.biEndpoints);
        write(outStream, inform.biGammaRed);
        write(outStream, inform.biGammaGreen);
        write(outStream, inform.biGammaBlue);
    }
    if (inform.biSize >= 124) {
        write(outStream, inform.biIntent);
        write(outStream, inform.biProfileData);
        write(outStream, inform.biProfileSize);
        write(outStream, inform.biReserved);
    }
    return 0;
}

int Bitmap::writePictur(std::ofstream & outStream) {
    return 0;
}

int Bitmap::checkType() {
    return (header.bfType == 0x4D42 || header.bfType == 0x424D);
}

BYTE Bitmap::bitExtract(BYTE byte, DWORD mask) {
    if (mask == 0) {
        return 0;
    } 
    DWORD   maskBuffer = mask;
    int     maskPadding = 0;
    while (!(maskBuffer & 1)) {
        maskBuffer >>= 1;
        ++maskPadding;
    }
    return (byte & mask) >> maskPadding;
}

int Bitmap::load(const std::string & path) {
    
    std::ifstream inStream(path, std::ifstream::binary);
    if (!inStream.is_open())
        return 1;
    
    readHeader(inStream);
    readInform(inStream);
    //readPictur(inStream);

    inStream.close();
    
    return 0;
}

int Bitmap::save(const std::string & path) {

    std::ofstream outStream(path, std::ofstream::binary);
    if (!outStream.is_open())
        return 1;
    
    writeHeader(outStream);
    writeInform(outStream);
    writePictur(outStream);

    outStream.close();
    
    return 0;
}

Bitmap::~Bitmap() {
    /*
    if (!pictur)
        return;
    for (int i = 0; i < inform.biHeight; ++i) 
        delete[] pictur[i];
    delete[] pictur;
    */
}
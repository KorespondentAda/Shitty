
#include "../include/bitmap.hpp"

#include <cstdint>
#include <cstring>

Bitmap::Bitmap() {
    memset(&header, 0x00, sizeof(BITMAPFILEHEADER));
    memset(&inform, 0x00, sizeof(BITMAPINFO));
}

int Bitmap::readHeader(std::ifstream & inStream) {
    read(inStream, header.bfType);
    if (!checkType())
        throw std::runtime_error("Unsupported bfType");
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

int Bitmap::readPalette(std::ifstream & inStream) {
    
    int _paletteSize = paletteSize();
    palette = new RGBQUAD[_paletteSize];
    
    for (int i = 0; i < _paletteSize / 4; ++i) {
        read(inStream, palette[i].rgbBlue);
        read(inStream, palette[i].rgbGreen);
        read(inStream, palette[i].rgbRed);
        read(inStream, palette[i].rgbReserved);
    }

    return 0;
}

int Bitmap::readPicture(std::ifstream & inStream) {
    pictur = new RGBQUAD *[inform.biHeight];
    for (int i = 0; i < inform.biHeight; ++i) 
        pictur[i] = new RGBQUAD[inform.biWidth];
    if (inform.biBitCount != 8) 
        throw std::runtime_error("Unsupported biBitCount");
    
    int padding = linePadding();
    BYTE buffer;
    for (int i = 0; i < inform.biHeight; ++i) {
        for (int j = 0; j < inform.biWidth; ++j) {
            read(inStream, buffer);
            pictur[i][j].rgbBlue = pictur[i][j].rgbGreen = pictur[i][j].rgbRed = pictur[i][j].rgbReserved = buffer;
            /*
            pictur[i][j].rgbBlue     = bitExtract(buffer, inform.biRedMask);
            pictur[i][j].rgbGreen    = bitExtract(buffer, inform.biGreenMask);
            pictur[i][j].rgbRed      = bitExtract(buffer, inform.biBlueMask);
            pictur[i][j].rgbReserved = bitExtract(buffer, inform.biAlphaMask);
            */
        }
        inStream.seekg(padding, std::ios_base::cur);
    }   
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

int Bitmap::writePalette(std::ofstream & outStream) {
    
    int _paletteSize = paletteSize();
    
    for (int i = 0; i < _paletteSize / 4; ++i) {
        write(outStream, palette[i].rgbBlue);
        write(outStream, palette[i].rgbGreen);
        write(outStream, palette[i].rgbRed);
        // If not CORE-V
        write(outStream, palette[i].rgbReserved);
    }

    return 0;
}

int Bitmap::writePicture(std::ofstream & outStream) {
    int padding = linePadding();
    
    for (int i = 0; i < inform.biHeight; ++i) {
        for (int j = 0; j < inform.biWidth; ++j)
            write(outStream, pictur[i][j].rgbBlue);
        for (int j = 0; j < padding; ++j)
            write(outStream, (BYTE)0x00);
        
    }
    return 0;
}

int Bitmap::checkType() {
    return (header.bfType == 0x4D42 || header.bfType == 0x424D);
}

int Bitmap::linePadding() {
    // maybe we can do it faster?
    return ((4 - ((inform.biWidth * (inform.biBitCount >> 3)) % 4)) & 3);
}

int Bitmap::paletteSize() {
    return (header.bfOffBits - inform.biSize - 14);
    // return (inform.biClrUsed * 4);
}

BYTE Bitmap::bitExtract(DWORD byte, DWORD mask) {
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
        throw std::runtime_error("Can not open file: " + path);
    
    readHeader(inStream);
    readInform(inStream);
    readPalette(inStream);
    readPicture(inStream);

    inStream.close();
    
    return 0;
}

int Bitmap::save(const std::string & path) {
    
    std::ofstream outStream(path, std::ofstream::binary);
    if (!outStream.is_open())
         throw std::runtime_error("Can not open file: " + path);

    writeHeader(outStream);
    writeInform(outStream);
    writePalette(outStream);
    writePicture(outStream);

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


void Bitmap::test() {
    printf("Size        = %d\n", inform.biSize);
    printf("OffBits     = %d\n", header.bfOffBits);
    printf("Width       = %d\n", inform.biWidth);
    printf("BitCount    = %d\n", inform.biBitCount);
    printf("Padding     = %d\n", linePadding());
    printf("Palette     = %d\n", paletteSize());
}
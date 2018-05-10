
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
    palette = new RGBTRIPLE[_paletteSize];
    for (int i = 0; i < _paletteSize / 4; ++i) {
        read(inStream, palette[i].rgbtBlue);
        read(inStream, palette[i].rgbtGreen);
        read(inStream, palette[i].rgbtRed);
    }
    return 0;
}

int Bitmap::readPicture(std::ifstream & inStream) {
    if (inform.biBitCount != 24)
        std::runtime_error("Unsupported biBitCount");
    picture = new RGBTRIPLE *[inform.biHeight];
    for (int i = 0; i < inform.biHeight; ++i) 
        picture[i] = new RGBTRIPLE[inform.biWidth];
    int padding = linePadding();
    for (int i = 0; i < inform.biHeight; ++i) {
        for (int j = 0; j < inform.biWidth; ++j) {
            read(inStream, picture[i][j].rgbtBlue);
            read(inStream, picture[i][j].rgbtGreen);
            read(inStream, picture[i][j].rgbtRed);
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
        write(outStream, palette[i].rgbtBlue);
        write(outStream, palette[i].rgbtGreen);
        write(outStream, palette[i].rgbtRed);
    }

    return 0;
}

int Bitmap::writePicture(std::ofstream & outStream) {
    int padding = linePadding();
    
    for (int i = 0; i < inform.biHeight; ++i) {
        for (int j = 0; j < inform.biWidth; ++j) {
            write(outStream, picture[i][j].rgbtBlue);
            write(outStream, picture[i][j].rgbtGreen);
            write(outStream, picture[i][j].rgbtRed);
        }
        for (int j = 0; j < padding; ++j)
            write(outStream, BYTE(0x00));
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
    DWORD   maskBuffer  = mask;
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

void Bitmap::draw_pixel(LONG x, LONG y, RGBTRIPLE color) {
    if (x < 0 || y < 0 || x >= inform.biWidth || y >= inform.biHeight)
        return;
    // throw std::runtime_error("point is not inside of picture");
    picture[inform.biHeight - y - 1][x] = color;
}

void Bitmap::draw_hor_line(LONG x1, LONG x2, LONG y, RGBTRIPLE color) {
    if (y < 0 || y >= inform.biHeight)
        return;
    if (x1 > x2) 
        swap(x1, x2);
    if (x2 < 0 || x1 >= inform.biWidth)
        return;
    if (x1 < 0)
        x1 = 0;
    if (x2 >= inform.biWidth)
        x2 = inform.biWidth - 1;
    for (int i = x1; i <= x2; ++i)
        draw_pixel(i, y, color);
}

void Bitmap::draw_ver_line(LONG y1, LONG y2, LONG x, RGBTRIPLE color) {
    if (x < 0 || x >= inform.biWidth)
        return;
    if (y1 > y2)
        swap(y1, y2);
    if (y2 < 0 || y1 >= inform.biHeight)
        return;
    if (y1 < 0)
        y1 = 0;
    if (y2 >= inform.biHeight)
        y2 = inform.biHeight - 1;
    for (int i = y1; i <= y2; ++i)
        draw_pixel(x, i, color); 
}

void Bitmap::draw_hor_line(LONG x1, LONG x2, LONG y, RGBTRIPLE color, LONG width) {
    for (int i = -half(width); i < half(width + 1); ++i)
        draw_hor_line(x1, x2, y + i, color);
}

void Bitmap::draw_ver_line(LONG y1, LONG y2, LONG x, RGBTRIPLE color, LONG width) {
    for (int i = -half(width); i < half(width + 1); ++i)
        draw_ver_line(y1, y2, x + i, color);
}

void Bitmap::draw_pixel(LONG x, LONG y, RGBTRIPLE color, LONG r) {
    for (LONG i = -r; i < r; ++i)
        for (LONG j = -r; j < r; ++j) 
            if (i * i + j * j <= r * r)
                draw_pixel(x + i, y + j, color);
}

void Bitmap::draw_line(LONG x1, LONG y1, LONG x2, LONG y2, RGBTRIPLE color) {
    LONG dx = x2 - x1 + 1;
    LONG dy = y2 - y1 + 1;
    double a = (double)dy / dx;
    double b = (double)y1 - a * x1;
    for (LONG x = x1; x <= x2; ++x) {
        LONG y = a * x + b;
        draw_pixel(x, y, color);
    }
    for (LONG y = y1; y <= y2; ++y) {
        LONG x = (y - b) / a;
        draw_pixel(x, y, color);
    }
}
void Bitmap::draw_line(LONG x1, LONG y1, LONG x2, LONG y2, RGBTRIPLE color, LONG r) {
    LONG dx = x2 - x1;
    LONG dy = y2 - y1;
    double a = (double)dy / dx;
    double b = (double)y1 - a * x1;
    for (LONG x = x1; x <= x2; ++x) {
        LONG y = a * x + b;
        draw_pixel(x, y, color, r);
    }
    for (LONG y = y1; y <= y2; ++y) {
        LONG x = (y - b) / a;
        draw_pixel(x, y, color, r);
    }
}

void Bitmap::draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, RGBTRIPLE color) {
    draw_hor_line(x1, x2, y1, color);
    draw_hor_line(x1, x2, y2, color);
    draw_ver_line(y1, y2, x1, color);
    draw_ver_line(y1, y2, x2, color);
}

void Bitmap::draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, RGBTRIPLE color, LONG width) {
    draw_hor_line(x1, x2, y1, color, width);
    draw_hor_line(x1, x2, y2, color, width);
    draw_ver_line(y1, y2, x1, color, width);
    draw_ver_line(y1, y2, x2, color, width);
}

void Bitmap::flip() {
	RGBTRIPLE ** newPicture = new RGBTRIPLE *[inform.biWidth];
	for (LONG index = 0; index < inform.biWidth; ++index)
		newPicture[index] = new RGBTRIPLE[inform.biHeight];	
	for (LONG i = 0; i < inform.biWidth; ++i) 
		for (LONG j = 0; j < inform.biHeight; ++j)
			newPicture[i][j] = picture[j][inform.biWidth - i - 1];		
	for (LONG i = 0; i < inform.biHeight; ++i)
		delete[] picture[i];
	delete[] picture;
	picture = newPicture;
	swap(inform.biWidth, inform.biHeight);
}

void Bitmap::print_info() {
    printf("< < < Bitmap information > > >\n");
    printf("Bitmap HEADER:\n");
    printf("\tbfType        : %d\n", header.bfType);
    printf("\tbfSize        : %d\n", header.bfSize);
    printf("\tbfReserved1   : %d\n", header.bfReserved1);
    printf("\tbfReserved2   : %d\n", header.bfReserved2);
    printf("\tbfOffBits     : %d\n", header.bfOffBits);
    printf("Bitmap INFO:\n");
}

Bitmap::~Bitmap() {
    if (picture) {
        for (LONG i = 0; i < inform.biHeight; ++i)
            delete[] picture[i];
        delete[] picture;
    }
    if (palette)
        delete[] palette;
}


void Bitmap::test() {
    printf("Size        = %x\n", inform.biSize);
    printf("OffBits     = %d\n", header.bfOffBits);
    printf("Width       = %d\n", inform.biWidth);
    printf("BitCount    = %d\n", inform.biBitCount);
    printf("Padding     = %d\n", linePadding());
    printf("Palette     = %d\n", paletteSize());
}

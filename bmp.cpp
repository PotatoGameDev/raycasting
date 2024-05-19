#include "bmp.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace potato_raycasting {

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t fileType{0x4D42}; // "BM"
    uint32_t fileSize{0};
    uint16_t reserved1{0};

    uint16_t reserved2{0};
    uint32_t offsetData{0};
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bitCount{0};
    uint32_t compression{0};
    uint32_t sizeImage{0};
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};
#pragma pack(pop)

struct BMPColorHeader {
    uint32_t redMask{0x00ff0000};
    uint32_t greenMask{0x0000ff00};
    uint32_t blueMask{0x000000ff};
    uint32_t alphaMask{0xff000000};
    uint32_t colorSpaceType{0x73524742}; // sRGB
    uint32_t unused[16]{0};
};
// Function to read a BMP file and convert to uint32_t format AARRGGBB.
void readBMPAndConvert(const std::string &filename,
                       std::vector<uint32_t> &out_pixels, int &width,
                       int &height) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Failed to open the file!");
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.fileType != 0x4D42) { // BMP signature
        throw std::runtime_error("Nota BMP file");
    }

    if (infoHeader.bitCount != 24 || infoHeader.compression != 0) {
        throw std::runtime_error("Unsupported BMP format; this reader only "
                                 "supports uncompressed 24-bit BMP files.");
    }

    // Move file pointer to the start of pixel data
    file.seekg(fileHeader.offsetData, std::ios::beg);

    width = infoHeader.width;
    height = infoHeader.height;
    // BMP data is padded to have rows aligned on a 4-byte boundary
    int rowStride = (infoHeader.width * 3 + 3) & ~3;

    out_pixels.resize(width * height);
    std::vector<uint8_t> row(rowStride);

    // Read pixel data from the bottom row to the top row
    for (int y = height - 1; y >= 0; --y) {
        file.read(reinterpret_cast<char *>(row.data()), row.size());
        for (int x = 0; x < width; ++x) {
            // Convert each BGR byte block to uint32_t format AARRGGBB (assuming
            // alpha value to be 255)
            uint8_t b = row[x * 3 + 0];
            uint8_t g = row[x * 3 + 1];
            uint8_t r = row[x * 3 + 2];
            uint32_t color =
                (255 << 24) | (r << 16) | (g << 8) | b; // Shift and place
            out_pixels[y * width + x] =
                color; // Assign the formatted color to the output pixel array
        }
    }
}

} // namespace potato_raycasting

//
// Created by Benjam on 22-05-21.
//

#include <stdexcept>
#include <GL/glew.h>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include "BMPTexture.h"
#include "../../../../IO/IOException.h"

#define BMP_HEADER_SIZE                 54

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Math4BG
{
    struct BMPHeader
    {
        // Header
        uint16_t fileType = 0x4D42;          // BM = { 'B' 'M' }
        uint32_t fileSize = 0;               // size of the file (in bytes)
        uint32_t reserved = 0;               // reserved for creation application id
        uint32_t dataAddress = 0;             // start position of pixel data (bytes from the beginning of the file)

        // Info Header
        uint32_t size = 40;                     // info header size (40)
        int32_t width = 0;                      // width of bitmap in pixels
        int32_t height = 0;                     // width of bitmap in pixels
        uint16_t planes = 1;                    // amount of planes, always 1

        uint16_t bitCount = 0;                  // bits per pixel
        uint32_t compression = 0;               // type of compression
        uint32_t imageSize = 0;                 // 0 - for uncompressed images

        int32_t pixelPerMeterWidth = 0;         // pixels per meter in width
        int32_t pixelsPerMeterHeight = 0;         // pixels per meter in height
        uint32_t colorsUsed = 0;               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bitCount
        uint32_t colorsImportant = 0;
    };

    BMPTexture::BMPTexture(const std::string &path, unsigned int type) :
    Texture(type)
    {
        unsigned char* data = LoadBMP(path);

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);*/


        delete[] data;
    }

    unsigned char* BMPTexture::LoadBMP(const std::string &imagePath)
    {
        //BMPHeader header;
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned char* data;
        FILE* file = fopen(imagePath.c_str(), "rb");

        if(!file)
        {
            std::stringstream ss;
            ss << "The image " << imagePath << " could not be loaded!";
            throw IOException(ss.str());
        }

        if(fread((char*)&header, 1, BMP_HEADER_SIZE, file) != BMP_HEADER_SIZE || header[0] != 'B' || header[1] != 'M')// != 0x4D42)
        {
            std::stringstream ss;
            ss << "The image " << imagePath << " is not a valid BMP file!";
            throw IOException(ss.str());
        }

        dataPos = *(int*) &(header[0x0A]);
        imageSize = *(int*) &(header[0x22]);
        m_width = *(int*) &(header[0x12]);
        m_height = *(int*) &(header[0x16]);

        if(imageSize == 0)
            imageSize = m_width * m_height * 3;

        if(dataPos == 0)
            dataPos = BMP_HEADER_SIZE;

        data = new unsigned char[imageSize];

        fread(data, 1, imageSize, file);
        fclose(file);

        //---//

        return data;
    }
}
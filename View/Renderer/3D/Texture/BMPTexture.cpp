//
// Created by Benjam on 22-05-21.
//

#include <stdexcept>
#include <GL/glew.h>
#include "BMPTexture.h"

#define BMP_HEADER_SIZE                 54

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Math4BG
{
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
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned char* data;
        FILE* file = fopen(imagePath.c_str(), "rb");

        if(!file)
            throw std::runtime_error("The image could not be loaded!");

        if(fread(header, 1, BMP_HEADER_SIZE, file) != BMP_HEADER_SIZE || header[0] != 'B' || header[1] != 'M')
            throw std::runtime_error("The image is not a valid BMP file!");

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
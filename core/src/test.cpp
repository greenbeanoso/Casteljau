#include "core/render.h"
    
#include <iostream>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


namespace core
{


glm::vec3 Test::getPosition()
{
    return glm::vec3(
        1.0f,
        2.0f,
        3.0f
    );
    
}



void Test::createImage()
{
    constexpr int width = 256;
    constexpr int height = 256;


    unsigned char pixels[width * height * 3];


    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;


            pixels[index + 0] = x;
            pixels[index + 1] = y;
            pixels[index + 2] = 128;
        }
    }


    stbi_write_png(
        "test.png",
        width,
        height,
        3,
        pixels,
        width * 3
    );


    std::cout
        << "core: generated test.png\n";
}


}
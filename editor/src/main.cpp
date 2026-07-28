#include <iostream>

#include "core/render.h"


int main()
{

    std::cout
        << "Editor start\n";


    auto pos = core::Test::getPosition();


    std::cout
        << "Core position: "
        << pos.x << ", "
        << pos.y << ", "
        << pos.z
        << "\n";


    core::Test::createImage();


    std::cout
        << "Editor finished\n";


    return 0;
}
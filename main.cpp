#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include <graphics.hpp>

const int width = 640;
const int height = 480;

int main( int argc, char** argv )
{
    uwe::Context context{width, height};

    context.dump_renderer_info();

    context.run();

    return 0;
}
#include "WarpPipe.h"
#include <iostream>

WarpPipe::WarpPipe(int x, int y , QString picture) : Brick(x,y, picture)
{
}

WarpPipe::~WarpPipe()
{
    std::cout << ("WarpPipe deleted\n");
}

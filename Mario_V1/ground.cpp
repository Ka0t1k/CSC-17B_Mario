#include "ground.h"
#include <iostream>

Ground::Ground(int x, int y , QString picture) : Brick(x,y, picture)
{
}

Ground::~Ground()
{
    std::cout << ("Ground deleted\n");
}

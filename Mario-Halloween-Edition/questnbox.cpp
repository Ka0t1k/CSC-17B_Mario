#include "questnbox.h"
#include <iostream>



QuestnBox::QuestnBox(int x, int y , QString picture) : Brick(x,y, picture)
{
}

QuestnBox::~QuestnBox()
{
    std::cout << ("Questionbox deleted\n");
}

#include "bomb.h"
#include <iostream>

Bomb::Bomb(int x, int y) : Brick(x,y)
{
    this->setSprite(QString(":images/Bomb_Left.png"));
    this->rect = QRect(x, y+5, getSprite().width()/3, getSprite().height());
}

Bomb::~Bomb(){
    std::cout << "Bomb deleted";
}

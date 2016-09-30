#include "smash.h"

Smash::Smash(int x, int y) : Brick(x,y)
{
    this->sprite = QPixmap(":images/Smash.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height() / 3));
}

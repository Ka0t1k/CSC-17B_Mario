#include "piranhaplant.h"



PiranhaPlant::PiranhaPlant(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/PiranhaPlant.png");
    this->stopSprite = QPixmap(":images/PiranhaPlant_die.png");
    this->rect = QRect(x, y, moveLSprite.width(), moveLSprite.height());
    this->isMovingL = true;
}

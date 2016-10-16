#include "tube.h"


Tube::Tube(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)

{
    setPixmap(QPixmap(":images/Warp.png"));

}

int Tube::type() const
{
    return Type;
}



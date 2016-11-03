#include "tube.h"

#include <QPen>
#include <QDebug>


Tube::Tube(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)

{
    setPixmap(QPixmap(":images/Warp.png"));
    //setTransformOriginPoint(boundingRect().center());
}
int Tube::type() const
{
    return Type;
}

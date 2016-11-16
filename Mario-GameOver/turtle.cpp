#include "turtle.h"
#include <QPainter>

Turtle::Turtle(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame6()

{
    setFlag(ItemClipsToShape);
    mPixmap6 = QPixmap(":images/turtle.png");

}

void Turtle::nextFrame6(){

    mCurrentFrame6 += 72;
    if (mCurrentFrame6 >= 1420 ) {
        mCurrentFrame6 = 0;

    }
}

QRectF Turtle::boundingRect() const {
    return QRectF(0,0,68,60);

}

void Turtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap6, mCurrentFrame6, 0,68, 60);
    setTransformOriginPoint(boundingRect().center());
}

int Turtle::type() const {
    return Type;
}

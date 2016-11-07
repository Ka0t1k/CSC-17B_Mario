#include "turtle.h"
#include <QPainter>
Turtle::Turtle(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame6()

{
    setFlag(ItemClipsToShape);
    mPixmap6 = QPixmap(":images/turtle.png");
    setTransformOriginPoint(boundingRect().center());
    //startTimer( 100 );

}

void Turtle::nextFrame6(){

    mCurrentFrame6 += 72;
    if (mCurrentFrame6 >= 1420 ) {
        mCurrentFrame6 = 0;
        //mPos.setX( mPos.x() + 5);
    }
}

QRectF Turtle::boundingRect() const {
    return QRectF(0,0,68,60);

}

void Turtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap6, mCurrentFrame6, 0,68, 60);
    setTransformOriginPoint(boundingRect().center());
}

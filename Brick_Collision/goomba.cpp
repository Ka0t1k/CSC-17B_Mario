#include "goomba.h"
#include <QPainter>

Goomba::Goomba(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame3()

{
    setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/goombas.png");


}

void Goomba::nextFrame3(){

    mCurrentFrame3 += 54;
    if (mCurrentFrame3 >= 862 ) {
        mCurrentFrame3 = 0;

    }
}

QRectF Goomba::boundingRect() const {
    return QRectF(0,0,52,50);

}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,52, 50);
    setTransformOriginPoint(boundingRect().center());
}



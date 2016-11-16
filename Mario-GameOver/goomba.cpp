#include "goomba.h"
#include <QPainter>

Goomba::Goomba(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame3()

{
    setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/goombanew.png");


}

void Goomba::nextFrame3(){

    mCurrentFrame3 += 84;
    if (mCurrentFrame3 >= 1322 ) {
        mCurrentFrame3 = 0;

    }
}

QRectF Goomba::boundingRect() const {
    return QRectF(0,0,80,53);

}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,80, 53);
    setTransformOriginPoint(boundingRect().center());
}


int Goomba::type() const {
  return Type;
}

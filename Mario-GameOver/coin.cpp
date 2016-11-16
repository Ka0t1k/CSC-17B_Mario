#include "coin.h"
#include <QPainter>
#include<QList>

Coin::Coin(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame2()
{
    setFlag(ItemClipsToShape);
    mPixmap2 = QPixmap(":images/coin.png");

}

void Coin::nextFrame2(){

    mCurrentFrame2 += 38;
    if (mCurrentFrame2 >= 300 ) {
        mCurrentFrame2 = 0;
    }
}

QRectF Coin::boundingRect() const {
    return QRectF(0,0,39,41);

}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap2, mCurrentFrame2, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
}


int Coin::type() const {
  return Type;
}

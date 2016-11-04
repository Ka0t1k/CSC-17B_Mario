#include "coin.h"
#include <QDebug>
#include "coin.h"
#include <QDebug>
#include <QPainter>
//#include <QTimerEvent>


Coin::Coin(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame2()
{
    setFlag(ItemClipsToShape);
    mPixmap2 = QPixmap(":images/coin.png");
    setTransformOriginPoint(boundingRect().center());
    //startTimer( 100 );
}

void Coin::nextFrame2(){

    mCurrentFrame2 += 41;
    if (mCurrentFrame2 >= 120 ) {
        mCurrentFrame2 = 0;
    }
}

QRectF Coin::boundingRect() const {
    return QRectF(0,0,45,62);

}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap2, mCurrentFrame2, 0,41, 62);
    setTransformOriginPoint(boundingRect().center());
}

/*
QPoint Coin::pos() const{

    return mPos;
}
*/

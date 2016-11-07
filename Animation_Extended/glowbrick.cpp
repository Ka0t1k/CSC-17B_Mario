#include"glowbrick.h"
#include <QPainter>

GlowBrick::GlowBrick(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame5()

{
    setFlag(ItemClipsToShape);
    mPixmap5 = QPixmap(":images/brick.png");
    setTransformOriginPoint(boundingRect().center());
    //startTimer( 100 );

}

void GlowBrick::nextFrame5(){

    mCurrentFrame5 += 50;
    if (mCurrentFrame5 >= 799 ) {
        mCurrentFrame5 = 0;
        //mPos.setX( mPos.x() + 5);
    }
}

QRectF GlowBrick::boundingRect() const {
    return QRectF(0,0,50,50);

}

void GlowBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap5, mCurrentFrame5, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
}

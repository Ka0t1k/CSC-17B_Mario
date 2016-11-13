#include "flag.h"
#include <QPainter>

Flag::Flag(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame8()

{
    setFlag(ItemClipsToShape);
    mPixmap8 = QPixmap(":images/mflag.png");

}

void Flag::nextFrame8(){

    mCurrentFrame8 += 322;
    if (mCurrentFrame8 >= 5439 ) {
        mCurrentFrame8 = 0;

    }
}

QRectF Flag::boundingRect() const {
    return QRectF(0,0,115,84);

}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap8, mCurrentFrame8, 0,115, 84);
    setTransformOriginPoint(boundingRect().center());
}

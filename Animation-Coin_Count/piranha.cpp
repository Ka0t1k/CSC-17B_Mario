#include"piranha.h"
#include <QPainter>

Piranha::Piranha(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame7()

{
    setFlag(ItemClipsToShape);
    mPixmap7 = QPixmap(":images/piranha.png");

}

void Piranha::nextFrame7(){

    mCurrentFrame7 += 387;
    if (mCurrentFrame7 >= 9286 ) {
        mCurrentFrame7 = 0;

    }
}

QRectF Piranha::boundingRect() const {
    return QRectF(0,0,130,165);

}

void Piranha::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap7, mCurrentFrame7, 0,130, 165);
    setTransformOriginPoint(boundingRect().center());
}

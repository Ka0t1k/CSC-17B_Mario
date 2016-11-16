#include "stretch.h"
#include <QPainter>

Stretch::Stretch(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame9()

{
    setFlag(ItemClipsToShape);
    mPixmap9 = QPixmap(":images/ustretch.png");

}

void Stretch::nextFrame9(){

    mCurrentFrame9 += 141;
    if (mCurrentFrame9 >= 8180 ) {
        mCurrentFrame9 = 0;

    }
}

QRectF Stretch::boundingRect() const {
    return QRectF(0,0,135,112);

}

void Stretch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap9, mCurrentFrame9, 0,135, 112);
    setTransformOriginPoint(boundingRect().center());
}

int Stretch::type() const {
    return Type;
}

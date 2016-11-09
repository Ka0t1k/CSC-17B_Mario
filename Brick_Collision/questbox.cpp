#include "questbox.h"
#include <QPainter>

QuestBox::QuestBox(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame4()

{
    setFlag(ItemClipsToShape);
    mPixmap4 = QPixmap(":images/questbox.png");

}

void QuestBox::nextFrame4(){

    mCurrentFrame4 += 50;
    if (mCurrentFrame4 >= 800 ) {
        mCurrentFrame4 = 0;
        //mPos.setX( mPos.x() + 5);
    }
}

QRectF QuestBox::boundingRect() const {
    return QRectF(0,0,50,50);

}

void QuestBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap4, mCurrentFrame4, 0,50, 50);
    setTransformOriginPoint(boundingRect().center());
}

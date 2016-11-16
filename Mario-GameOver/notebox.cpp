#include "notebox.h"
#include <QPainter>

NoteBox::NoteBox(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame10()

{
    setFlag(ItemClipsToShape);
    mPixmap10 = QPixmap(":images/notebox.png");

}

void NoteBox::nextFrame10(){

    mCurrentFrame10 += 65;
    if (mCurrentFrame10 >= 518 ) {
        mCurrentFrame10 = 0;

    }
}

QRectF NoteBox::boundingRect() const {
    return QRectF(0,0,63,63);

}

void NoteBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap10, mCurrentFrame10, 0,63, 63);
    setTransformOriginPoint(boundingRect().center());
}

#ifndef GOOMBA_H
#define GOOMBA_H

#include <QGraphicsItem>
#include <QPixmap>


class Goomba : public QGraphicsItem
{
public:
    Goomba(QGraphicsItem *parent = 0);
    void nextFrame3();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint pos() const;

private:

    int mCurrentFrame3;
    QPixmap mPixmap3;

};
#endif // GOOMBA_H

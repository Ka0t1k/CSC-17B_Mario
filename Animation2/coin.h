#ifndef COIN_H
#define COIN_H

#include <QGraphicsItem>
#include <QPixmap>

class Coin : public QGraphicsItem
{
public:
     Coin(QGraphicsItem *parent = 0);
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint pos() const;

private:

    int mCurrentFrame2;
    QPixmap mPixmap2;

    QPoint mPos;

};

#endif // COIN_H

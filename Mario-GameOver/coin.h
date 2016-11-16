#ifndef COIN_H
#define COIN_H

#include <QGraphicsItem>
#include <QPixmap>

class Coin : public QGraphicsItem
{

public:
    enum { Type = UserType + 1 };
    Coin(QGraphicsItem *parent = 0);
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int mCurrentFrame2;
    QPixmap mPixmap2;

};

#endif // COIN_H

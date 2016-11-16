#ifndef GIANTGOOMBA_H
#define GIANTGOOMBA_H
#include <QGraphicsItem>
#include <QPixmap>

class GiantGoomba : public QGraphicsItem
{
public:
    GiantGoomba(QGraphicsItem *parent = 0);
    enum { Type = UserType + 9 };
    int type() const;
    void nextFrame12();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame12;
    QPixmap mPixmap12;
};
#endif // GIANTGOOMBA_H

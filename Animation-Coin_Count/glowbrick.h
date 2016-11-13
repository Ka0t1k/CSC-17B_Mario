#ifndef GLOWBRICK_H
#define GLOWBRICK_H
#include <QGraphicsItem>
#include <QPixmap>


class GlowBrick : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };
    GlowBrick(QGraphicsItem *parent = 0);
    void nextFrame5();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int mCurrentFrame5;
    QPixmap mPixmap5;

};
#endif // GLOWBRICK_H

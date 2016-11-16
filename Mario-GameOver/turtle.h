#ifndef TURTLE_H
#define TURTLE_H
#include <QGraphicsItem>
#include <QPixmap>

class Turtle : public QGraphicsItem
{
public:
    Turtle(QGraphicsItem *parent = 0);
    enum { Type = UserType + 6 };
    int type() const;
    void nextFrame6();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame6;
    QPixmap mPixmap6;

};
#endif // TURTLE_H

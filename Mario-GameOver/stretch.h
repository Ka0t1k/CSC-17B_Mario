#ifndef STRETCH_H
#define STRETCH_H
#include <QGraphicsItem>
#include <QPixmap>

class Stretch : public QGraphicsItem
{
public:
    Stretch(QGraphicsItem *parent = 0);
    enum { Type = UserType + 7 };
    int type() const;
    void nextFrame9();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame9;
    QPixmap mPixmap9;
};
#endif // STRETCH_H

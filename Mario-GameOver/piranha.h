#ifndef PIRANHA_H
#define PIRANHA_H
#include <QGraphicsItem>
#include <QPixmap>

class Piranha : public QGraphicsItem
{
public:
    Piranha(QGraphicsItem *parent = 0);
    enum { Type = UserType + 8 };
    int type() const;
    void nextFrame7();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame7;
    QPixmap mPixmap7;

};
#endif // PIRANHA_H

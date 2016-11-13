#ifndef FLAG_H
#define FLAG_H
#include <QGraphicsItem>
#include <QPixmap>

class Flag : public QGraphicsItem
{
public:
    Flag(QGraphicsItem *parent = 0);
    void nextFrame8();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame8;
    QPixmap mPixmap8;
};
#endif // FLAG_H

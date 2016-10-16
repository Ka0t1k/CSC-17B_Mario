#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPixmap>

class Player : public QGraphicsItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);
    int direction() const;
    void addDirection(int direction);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int m_direction;
    int mCurrentFrame;
    QPixmap mPixmap;

};

#endif // PLAYER_H


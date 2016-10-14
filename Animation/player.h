#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);
    int direction() const;
    void addDirection(int direction);
    void nextFrame();
    QRectF boundingRect() const;

private:
    int m_direction;
    int mCurrentFrame;




};

#endif // PLAYER_H

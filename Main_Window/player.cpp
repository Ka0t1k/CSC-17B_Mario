#include "player.h"

#include <QPen>
//#include <QDebug>

Player::Player(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , m_direction(0)
{
    setPixmap(QPixmap(":images/Mario"));
    setTransformOriginPoint(boundingRect().center());
}

int Player::direction() const
{
    return m_direction;
}

void Player::addDirection(int direction)
{
    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}






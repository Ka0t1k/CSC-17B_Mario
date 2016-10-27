#include "player.h"
#include <QDebug>
#include <QPainter>

Player::Player(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    ,m_direction(0),mCurrentFrame()
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/mario_walk_2.png");
    setTransformOriginPoint(boundingRect().center());
}


int Player::direction() const
{
    return m_direction;

}

void Player::nextFrame(){
    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191 ) {
        mCurrentFrame = 0;
    }
}

QRectF Player::boundingRect() const {
    return QRectF(0,0,45,62);

}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,45, 62);
    setTransformOriginPoint(boundingRect().center());
}



void Player::addDirection(int direction){

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            //QTransform matrix flips the image to face the other direction if left key is pressed
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else//moving right restore normal state by assigning an empty Qtransform object which is an idetntity matrix
            setTransform(QTransform());
    }
}


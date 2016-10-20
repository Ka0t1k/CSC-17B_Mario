#ifndef COINPRITE_H
#define COINPRITE_H

#include <QPoint>
#include <QPixmap>

class QPainter;

class CoinSprite
{
public:

    CoinSprite();
    void draw( QPainter* painter);
    QPoint pos() const;
    void nextFrame();

private:

    QPixmap* mSpriteImage;
    int mCurrentFrame;
    QPoint mPos;


};

#endif // COINPRITE_H

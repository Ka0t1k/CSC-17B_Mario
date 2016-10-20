#ifndef BOMBSPRITE_H
#define BOMBSPRITE_H

#include <QPoint>
#include <QPixmap>

class QPainter;

class BombSprite
{
public:

   BombSprite();
    void draw( QPainter* painter);
    QPoint pos() const;
    void nextFrame();

private:

    QPixmap* mSpriteImage;
    int mCurrentFrame;
    QPoint mPos;


};

#endif // BOMBSPRITE_H

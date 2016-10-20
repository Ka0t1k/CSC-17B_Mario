#ifndef MARIOSPRITE_H
#define MARIOSPRITE_H

#include <QPoint>
#include <QPixmap>

class QPainter;

class MarioSprite
{
public:

    MarioSprite();
    void draw( QPainter* painter);
    QPoint pos() const;
    void nextFrame();

private:

    QPixmap* mSpriteImage;
    int mCurrentFrame;
    QPoint mPos;


};

#endif // MARIOSPRITE_H

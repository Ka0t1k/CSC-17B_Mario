#ifndef TURTLEPRITE_H
#define TURTLEPRITE_H

#include <QPoint>
#include <QPixmap>

class QPainter;

class TurtleSprite
{
public:

   TurtleSprite();
    void draw( QPainter* painter);
    QPoint pos() const;
    void nextFrame();

private:

    QPixmap* mSpriteImage;
    int mCurrentFrame;
    QPoint mPos;


};

#endif // TURTLEPRITE_H

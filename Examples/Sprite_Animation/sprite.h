#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QPoint>

class Sprite
{

public:
    Sprite();

    void draw( QPainter* painter);

    QPoint pos() const;

    void changeDir();

    void nextFrame();

private:

    QList<QPixmap> mLeftSprite;
    QList<QPixmap> mRightSprite;
    QList<QPixmap> *mCurrentSprite;
    int mCurrentFrame;
    QPoint mPos;
    int mXDir;
};

#endif // SPRITE_H

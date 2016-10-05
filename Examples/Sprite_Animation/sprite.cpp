#include "sprite.h"
#include <QDebug>

Sprite::Sprite()
    :mCurrentFrame(0),mPos(0,100),mXDir(1)
{
    mLeftSprite.append( QPixmap(":left_1.png"));
    mLeftSprite.append( QPixmap(":left_2.png"));
    mLeftSprite.append( QPixmap(":left_3.png"));
    mLeftSprite.append( QPixmap(":left_4.png"));
    mLeftSprite.append( QPixmap(":left_5.png"));
    mLeftSprite.append( QPixmap(":left_6.png"));

    mRightSprite.append( QPixmap(":right_1.png"));
    mRightSprite.append( QPixmap(":right_2.png"));
    mRightSprite.append( QPixmap(":right_3.png"));
    mRightSprite.append( QPixmap(":right_4.png"));
    mRightSprite.append( QPixmap(":right_5.png"));
    mRightSprite.append( QPixmap(":right_6.png"));

    mCurrentSprite = &mRightSprite;

}

void Sprite::draw( QPainter* painter)
{
    painter->drawPixmap(mPos,(*mCurrentSprite)[mCurrentFrame]);
}

void Sprite::nextFrame()
{
    mCurrentFrame = ++mCurrentFrame % 6;
    mPos.setX( mPos.x() +  mXDir * 10 );
}

QPoint Sprite::pos() const
{
    return mPos;
}

void Sprite::changeDir()
{
    mXDir = -mXDir;
    mCurrentFrame = 0;
    if( mXDir < 0 ) {
        mCurrentSprite = &mLeftSprite;
    } else {
        mCurrentSprite = &mRightSprite;
    }
}



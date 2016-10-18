#include "mariosprite.h"

#include <QPainter>

MarioSprite::MarioSprite():mPos(0,300),mCurrentFrame(0){
    mSpriteImage = new QPixmap(":mario_walk.png");
}

void MarioSprite::draw( QPainter* painter){

    painter->drawPixmap ( mPos.x(),mPos.y(), *mSpriteImage, mCurrentFrame, 0, 39,0 );
}

QPoint MarioSprite::pos() const{

    return mPos;
}

void MarioSprite::nextFrame(){
    mCurrentFrame += 43;
    if (mCurrentFrame >= 901 )
        mCurrentFrame = 0;
    mPos.setX( mPos.x() + 10);
}

#include "bombsprite.h"

#include <QPainter>

BombSprite::BombSprite():mPos(0,200),mCurrentFrame(0){
    mSpriteImage = new QPixmap(":Bomb.png");
}

void BombSprite::draw( QPainter* painter){

    painter->drawPixmap ( mPos.x(),mPos.y(), *mSpriteImage, mCurrentFrame, 0,53,0 );
}

QPoint BombSprite::pos() const{

    return mPos;
}


void BombSprite::nextFrame(){
    mCurrentFrame += 52;
    if (mCurrentFrame >= 104 )
        mCurrentFrame = 0;
    mPos.setX( mPos.x()+7);
}

#include "mariosprite.h"

#include <QPainter>

MarioSprite::MarioSprite():mPos(100,300),mCurrentFrame(0){
    mSpriteImage = new QPixmap(":mario_walk.png");
}

void MarioSprite::draw( QPainter* painter){

    painter->drawPixmap ( mPos.x(),mPos.y(), *mSpriteImage, mCurrentFrame, 0, 43,100 );
}

QPoint MarioSprite::pos() const{

    return mPos;
}

//following variable keeps track which
//frame to show from sprite sheet
void MarioSprite::nextFrame(){
    mCurrentFrame += 57;
    if (mCurrentFrame >= 1176 )
        mCurrentFrame = 0;
    mPos.setX( mPos.x() + 10);
}

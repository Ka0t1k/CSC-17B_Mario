#include "turtlesprite.h"

#include <QPainter>

TurtleSprite::TurtleSprite():mPos(0,200),mCurrentFrame(0){
    mSpriteImage = new QPixmap(":t2.png");
}

void TurtleSprite::draw( QPainter* painter){

    painter->drawPixmap ( mPos.x(),mPos.y(), *mSpriteImage, mCurrentFrame, 0,40,0 );
}

QPoint TurtleSprite::pos() const{

    return mPos;
}


void TurtleSprite::nextFrame(){
    mCurrentFrame += 70;
    if (mCurrentFrame >= 104 )
        mCurrentFrame = 0;
    mPos.setX( mPos.x()+7);
}

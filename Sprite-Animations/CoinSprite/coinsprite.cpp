#include "coinsprite.h"

#include <QPainter>

CoinSprite::CoinSprite():mPos(0,200),mCurrentFrame(0){
    mSpriteImage = new QPixmap(":coin.png");
}

void CoinSprite::draw( QPainter* painter){

    painter->drawPixmap ( mPos.x(),mPos.y(), *mSpriteImage, mCurrentFrame, 0, 39,0 );
}

QPoint CoinSprite::pos() const{

    return mPos;
}

//following variable keeps track which
//frame to show from sprite sheet
void CoinSprite::nextFrame(){
    mCurrentFrame += 41;
    if (mCurrentFrame >= 120 )
        mCurrentFrame = 0;
    mPos.setX( mPos.x()+ 5);
}

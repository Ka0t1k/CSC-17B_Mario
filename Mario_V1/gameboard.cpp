#include "gameboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include "model.h"
#include "view.h"

GameBoard::GameBoard(Model *m, View *v) : QObject()
{
    this->model = m;
    this->view = v;
    this->view->setControl(this);
    gameStarted = true;
    xRelatif = -100;
    yRelatif = 0;
    iterBackground=0;
    timerId = startTimer(15);
}

int Gold::currentFrame = 0;
int Smash::currentFrame = 0;
int Flame::currentFrame = 0;
int Bomb::currentFrame = 0;
int Brick::speed = 4; // Make  faster/slower
//----------------------------------------------------------------------------------------------------------------//

GameBoard::~GameBoard()
{
    killTimer(timerId);
}

//----------------------------------------------------------------------------------------------------------------//


void GameBoard::timerEvent(QTimerEvent *)
{

    flameAnim();
    splashScreen();
    movementMario();
    getModel()->brickOrganization();
    goldAnim();
    smashAnim();
    GameOver();
    view->repaint();
}


void GameBoard::stopGame()
{
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();

    if(getIsJumping()){
        if(getIsAttacking()){
            for(int i=0;i<7;++i){xRelatif += 1;}
            //xRelatif += 7;
        }
        else
            for(int i=0;i<4;++i){xRelatif += 1;}
        //xRelatif+=4;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200); //How high mario can jump
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
        if(intersectTopMario(0)){
            xRelatif=0;
            yRelatif=0;
            startJumpY=model->getMario()->getRect().y();
            setIsJumping(false);
        }
    }

    if(intersectBottomMario(0)){
        xRelatif=0;
        yRelatif=0;
        startJumpY=model->getMario()->getRect().y();
        setIsJumping(false);
        moveXMario(y);

        if(getIsAttacking()){
            if(getModel()->getMario()->getIsLittle())
                getModel()->getSmash()->move(model->getMario()->getRect().x() - 60, model->getMario()->getRect().y() - 25);
            else
                getModel()->getSmash()->move(model->getMario()->getRect().x() - 50, model->getMario()->getRect().y());
            getModel()->getSmash()->setShow(true);
            Smash::currentFrame = 0;
            setIsAttacking(false);
        }

        if(getIsMovingR() && tempMove == 1){
            for(int i=0;i<57;i++){model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() + 1);}
            if (model->getMario()->getCurrentFrame() >= 1190 )
                model->getMario()->setCurrentFrame(0);
            tempMove = 0;
        }
        else if(getIsMovingR())
            tempMove++;
        else if(getIsMovingL() && tempMove == 1){
            for(int i=0;i<57;i++){model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() - 1);}
            if (model->getMario()->getCurrentFrame() <= 0 )
                model->getMario()->setCurrentFrame(1191);
            tempMove = 0;
        }
        else if(getIsMovingL())
            tempMove++;
        else
            model->getMario()->setCurrentFrame(0);
    }

    if((!intersectBottomMario(0) && !getIsJumping())){
        yRelatif=(-0.02*(xRelatif*xRelatif));
        for(int i=0;i<4;++i){xRelatif += 1;}
        //xRelatif+=4;
        if(getIsAttacking()){
            for(int i=0;i<7;++i){xRelatif += 1;}
            //xRelatif += 7;
        }
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
}

void GameBoard::movementMushroom(int i)
{
    int x=model->getMushroom()->at(i)->getRect().x();
    if(model->getMushroom()->at(i)->getMoveCount()>0){

        model->getMushroom()->at(i)->setmoveCount(model->getMushroom()->at(i)->getMoveCount() - 1);
        if(moveMap  ){
            if(getModel()->getMushroom()->at(i)->getUp())
                model->getMushroom()->at(i)->move(x-Brick::speed, model->getMushroom()->at(i)->getRect().y() - 1);
            else
                model->getMushroom()->at(i)->move(x-Brick::speed, model->getMushroom()->at(i)->getRect().y() + 1);
        }
        else {
            if(getModel()->getMushroom()->at(i)->getUp())
                model->getMushroom()->at(i)->move(x, model->getMushroom()->at(i)->getRect().y() - 1);
            else
                model->getMushroom()->at(i)->move(x, model->getMushroom()->at(i)->getRect().y() + 1);
        }
    }
    else
        moveBrick(x ,model->getMushroom()->at(i));
}

void GameBoard::moveBrick(int x ,Brick * b)
{
    int speed;
    if(moveMap )
        speed=Brick::speed ;
    else
        speed = 0;


    if(intersectBottomBrick(b)){
        if(b->getMoveX()){
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2, b->getRect().y());
            if( intersectLeftBrick(b) || b->getRect().x()<3)
                b->setMoveX(true);
        }
        b->setYR(0);
        b->setXR(0);
        b->setStartY(b->getRect().y());
    }
    else{
        b->setYR(-0.02*(b->getXR()*b->getXR()));
        b->setXR(b->getXR()+3);
        int y = b->getStartY()- b->getYR();
        if(b->getMoveX()){
            b->move(x-speed+2, y);
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2,y);
            if( intersectLeftBrick(b))
                b->setMoveX(true);
        }
    }
}

//How far mario walks before screen starts moving
void GameBoard::moveXMario(int y)
{
    int x=model->getMario()->getRect().x();

    if(!intersectLeftMario(0) && model->getMario()->getRect().x()>=2 && getIsMovingL() )
        x -= Brick::speed;
    else if( !intersectRightMario(0) && model->getMario()->getRect().x()<=350  && getIsMovingR())
        x += Brick::speed;
    if( !intersectRightMario(0)&& model->getMario()->getRect().x()>=350  && getIsMovingR() ){
        moveMap=true;
    }
    else
        moveMap=false;
    model->getMario()->move(x,y);
}

//----------------------------------------------------------------------------------------------------------------//

bool GameBoard::intersectTopMario(int i)
{
    if(i<model->getGround()->size() || i<model->getSafes()->size()){
        if(!model->getGround()->empty() && i<model->getGround()->size()){
            if(model->getMario()->intersectTop(model->getGround()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getMario()->intersectTop(model->getSafes()->at(i)->getRect())){
                if(model->getSafes()->at(i)->getCapacity()){
                    if(model->getSafes()->at(i)->getCapacity() == 2){
                        model->createMushroom(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y(), true);
                        model->getSafes()->at(i)->setCapacity(1);
                    }
                }else
                    model->getSafes()->at(i)->setDestroyed(true);
                return true;
            }
        }
        intersectTopMario(i+1);
    }
    else
        return false;
}

bool GameBoard::intersectBottomMario(int i)
{
    if(i<model->getGround()->size()
            || i<model->getSafes()->size()
            || i<model->getPiranhaPlant()->size()
            || i<model->getBomb()->size()){
        if(!model->getGround()->empty() && i<model->getGround()->size()){
            if(model->getMario()->intersectBottom(model->getGround()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getMario()->intersectBottom(model->getSafes()->at(i)->getRect())){
                if(getIsAttacking()){
                    if(model->getSafes()->at(i)->getCapacity()){
                        if(model->getSafes()->at(i)->getCapacity() == 2){
                            model->createMushroom(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y(), false);
                            model->getSafes()->at(i)->setCapacity(1);
                        }
                    }else
                        model->getSafes()->at(i)->setDestroyed(true);
                }
                return true;
            }
        }
        if(!model->getPiranhaPlant()->empty() && i<model->getPiranhaPlant()->size()){
            if(model->getMario()->intersectBottom(model->getPiranhaPlant()->at(i)->getRect())){
                attackPiranhaPlant(i);
                return true;
            }
        }
        if(!model->getBomb()->empty() && i<model->getBomb()->size()){
            if(model->getMario()->intersectBottom(model->getBomb()->at(i)->getRect()) ){
                intersectYBombMario(i);
                return true;
            }
        }
        intersectBottomMario(i+1);
    }
    else
        return false;
}

bool GameBoard::intersectLeftMario(int i)
{
    if(i<model->getGround()->size()
            || i<model->getSafes()->size()
            || i<model->getPiranhaPlant()->size()
            || i<model->getBomb()->size()){
        if(!model->getGround()->empty() && i<model->getGround()->size()){
            if(model->getMario()->intersectLeft(model->getGround()->at(i)->getRect()))
                return true;
        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getMario()->intersectLeft(model->getSafes()->at(i)->getRect()))
                return true;
        }
        if(!model->getPiranhaPlant()->empty() && i<model->getPiranhaPlant()->size()){
            if(model->getMario()->intersectLeft(model->getPiranhaPlant()->at(i)->getRect())){
                intersectPiranhaPlantMario(i);
                return true;
            }
        }
        if(!model->getBomb()->empty() && i<model->getBomb()->size()){
            if(model->getMario()->intersectLeft(model->getBomb()->at(i)->getRect()))
                return true;
        }
        intersectLeftMario(i+1);
    }
    else
        return false;
}

bool GameBoard::intersectRightMario(int i)
{
    if(i<model->getGround()->size()
            || i<model->getSafes()->size()
            || i<model->getPiranhaPlant()->size()
            || i<model->getBomb()->size()){
        if(!model->getGround()->empty() && i<model->getGround()->size() ){
            if(model->getMario()->intersectRight(model->getGround()->at(i)->getRect()))
                return true;

        }
        if(!model->getSafes()->empty() && i<model->getSafes()->size()){
            if(model->getMario()->intersectRight(model->getSafes()->at(i)->getRect()))
                return true;
        }
        if(!model->getPiranhaPlant()->empty() && i<model->getPiranhaPlant()->size()){
            if(model->getMario()->intersectRight(model->getPiranhaPlant()->at(i)->getRect())){
                intersectPiranhaPlantMario(i);
                return true;
            }
        }
        if(!model->getBomb()->empty() && i<model->getBomb()->size()){
            if(model->getMario()->intersectRight(model->getBomb()->at(i)->getRect()))
                return true;
        }
        intersectRightMario(i+1);
    }
    else
        return false;
}

//Make coins vanish once collected
void GameBoard::intersectGoldMario(int i)
{
    if(model->getMario()->intersect(model->getGold()->at(i)->getRect())){
        model->getGold()->at(i)->setDestroyed(true);
        model->getMario()->setGoldNumber(model->getMario()->getGoldNumber()+1);
    }
}

//Make Mario get hurt by the flame. Can't kill flame
void GameBoard::intersectFlameMario(int i)
{
    if(model->getMario()->intersect(model->getFlame()->at(i)->getRect()) && !model->getMario()->getUntouchable()){
        model->getMario()->setIsLittle(true);
        model->getMario()->setLife(model->getMario()->getLife()-1);
        Brick::speed = 6;
    }
}

//Make Mario get hurt when he gets hit by an enemy
void GameBoard::intersectXBombMario(int i)
{
    if( !model->getMario()->getUntouchable()
            && !getIsAttacking()
            && !model->getBomb()->at(i)->isDestroyed()
            &&( model->getBomb()->at(i)->intersectRight(model->getMario()->getRect())||model->getBomb()->at(i)->intersectLeft(model->getMario()->getRect()))){

        if( !model->getMario()->getIsMovingR()&& !model->getMario()->getIsMovingL())
            model->getBomb()->at(i)->setMoveX(!model->getBomb()->at(i)->getMoveX());
        if(getModel()->getMario()->getIsMovingR() && !model->getBomb()->at(i)->getMoveX())
            model->getBomb()->at(i)->setMoveX(!model->getBomb()->at(i)->getMoveX());
        else if(getModel()->getMario()->getIsMovingL() && model->getBomb()->at(i)->getMoveX())
            model->getBomb()->at(i)->setMoveX(!model->getBomb()->at(i)->getMoveX());

        //Make Mario Little if he is hit
        model->getMario()->setIsLittle(true);
        model->getMario()->setLife(model->getMario()->getLife()-1);
        Brick::speed = 6;
    }
}

//Make mario able to stand on top of enemies and kill them
void GameBoard::intersectYBombMario(int i)
{
    if(!getModel()->getMario()->getIsMovingL()
            && !getModel()->getMario()->getIsMovingR()
            && !model->getBomb()->at(i)->isDestroyed()){
        getModel()->getMario()->move(getModel()->getBomb()->at(i)->getRect().x(), getModel()->getMario()->getRect().y());
    }
    if(!model->getBomb()->at(i)->isDestroyed() && getIsAttacking())
    {
        getModel()->getSmash()->move(model->getBomb()->at(i)->getRect().x() - 50, model->getBomb()->at(i)->getRect().y() - 50);
        getModel()->getSmash()->setShow(true);
        Smash::currentFrame = 0;
        getModel()->getBomb()->at(i)->setSprite(QString(":images/Bomb_Die.png"));
        model->getBomb()->at(i)->setDestroyed(true);
    }
}

//Make Mario big when he gets mushroom
void GameBoard::intersectMushroomMario(int i)
{
    if(model->getMario()->intersect(model->getMushroom()->at(i)->getRect())){
        model->getMushroom()->at(i)->setDestroyed(true);
        model->getMario()->setIsLittle(false);
        model->getMario()->setLife(model->getMario()->getLife() + 1);
        Brick::speed = 6;
    }
}

bool GameBoard::intersectBottomBrick(Brick * m)
{
    for(int i = 0; i<model->getGround()->size(); i++){
        if(m->intersectBottom(model->getGround()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectBottom(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectLeftBrick(Brick * m)
{
    for(int i = 0; i<model->getGround()->size(); i++){
        if(m->intersectLeft(model->getGround()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectRightBrick(Brick * m)
{
    for(int i = 0; i<model->getGround()->size(); i++){
        if(m->intersectRight(model->getGround()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectRight(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

void GameBoard::intersectPiranhaPlantMario(int i)
{
    if(!model->getMario()->getUntouchable()
            && !model->getPiranhaPlant()->at(i)->isDead()){
        model->getMario()->setIsLittle(true);
        model->getMario()->setLife(model->getMario()->getLife()-1);
        Brick::speed = 6;
    }
}

void GameBoard::attackPiranhaPlant(int i)
{
    if(!getModel()->getPiranhaPlant()->at(i)->isDead()
            && model->getMario()->getIsAttacking()){
        getModel()->getPiranhaPlant()->at(i)->setDead(true);
        model->getPiranhaPlant()->at(i)->setIsMovingL(false);
        getModel()->getSmash()->move(model->getPiranhaPlant()->at(i)->getRect().x() - 50, model->getPiranhaPlant()->at(i)->getRect().y() - 50);
        getModel()->getSmash()->setShow(true);
        Smash::currentFrame = 0;

    }
}


//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::splashScreen()
{
    if(getModel()->getSplashScreen()->getType() == SplashScreenType::Intro){
        int x=model->getSplashScreen()->getRect().x();
        int y=model->getSplashScreen()->getRect().y();
        y--;
        if(model->getSplashScreen()->getRect().bottom() > 0 && model->getSplashScreen()->getIsSplashScreen())
            model->getSplashScreen()->move(x, y);
        else
            model->getSplashScreen()->setIsSplashScreen(false);
    }
}
//Animation
//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::goldAnim()
{
    if(tempGold == 20){
        Gold::currentFrame += 40;
        if (Gold::currentFrame >= 120)
            Gold::currentFrame = 0;
        tempGold = 0;
    }
    else
        tempGold++;
}

void GameBoard::smashAnim(){
    if(tempSmash == 6){
        Smash::currentFrame += 66;
        if (Smash::currentFrame >= 200){
            Smash::currentFrame = 0;
            getModel()->getSmash()->setShow(false);
        }
        tempSmash = 0;
    }
    else
        tempSmash++;
}

void GameBoard::bombAnim(int i)
{
    if(tempBomb == 15){
        Bomb::currentFrame += 52;
        if (Bomb::currentFrame >= 156)
            Bomb::currentFrame = 1;
        tempBomb = 0;
    }
    else
        tempBomb++;
    int x=model->getBomb()->at(i)->getRect().x();
    if(!model->getBomb()->at(i)->isDestroyed()){
        moveBrick(x ,model->getBomb()->at(i));
        intersectXBombMario( i);
        if(model->getBomb()->at(i)->getMoveX())
            getModel()->getBomb()->at(i)->setSprite(QString(":images/Bomb_Right.png"));
        else
            getModel()->getBomb()->at(i)->setSprite(QString(":images/Bomb_Left.png"));
        model->getBomb()->at(i)->setSrcRect(QRect(Bomb::currentFrame, 0, model->getBomb()->at(i)->getRect().width(), model->getBomb()->at(i)->getRect().height()));
    }
    else{
        model->getBomb()->at(i)->setSrcRect(QRect(0, 0, model->getBomb()->at(i)->getRect().width(), model->getBomb()->at(i)->getRect().height()));

    }
}

void GameBoard::flameAnim()
{

    if(tempFlame == 10){
        Flame::currentFrame += 58;
        if (Flame::currentFrame >= 520)
            Flame::currentFrame = 3;
        tempFlame = 0;
    }
    else
        tempFlame++;
    for(int i = 0; i<model->getFlame()->size(); i++){
        int x=model->getFlame()->at(i)->getRect().x();
        moveBrick(x ,model->getFlame()->at(i));
        model->getFlame()->at(i)->setSrcRect(QRect(Flame::currentFrame, 0, model->getFlame()->at(i)->getRect().width(), model->getFlame()->at(i)->getRect().height()));   
        view->update(model->getFlame()->at(i)->getSrcRect());}
}

void GameBoard::BackgroundAnim(int i)
{
    if(iterBackground == 2){
        model->getBackground()->at(i)->moveBrick();
        iterBackground=0;
    }
    else{
        iterBackground++;
    }
}

void GameBoard::movementPiranhaPlant(int i)
{
    if(model->getPiranhaPlant()->at(i)->getIsMovingL()){
        if(model->getPiranhaPlant()->at(i)->getMoveCount() > 0){
            model->getPiranhaPlant()->at(i)->setmoveCount(model->getPiranhaPlant()->at(i)->getMoveCount() - 2);
            model->getPiranhaPlant()->at(i)->move(model->getPiranhaPlant()->at(i)->getRect().x(), model->getPiranhaPlant()->at(i)->getRect().y() - 2);
        }
        else if(model->getPiranhaPlant()->at(i)->getMoveCount() > - 120){
            model->getPiranhaPlant()->at(i)->setmoveCount(model->getPiranhaPlant()->at(i)->getMoveCount() - 2);
            model->getPiranhaPlant()->at(i)->move(model->getPiranhaPlant()->at(i)->getRect().x(), model->getPiranhaPlant()->at(i)->getRect().y() + 2);
        }
        else{
            model->getPiranhaPlant()->at(i)->setmoveCount(120);
        }
    }
}

bool GameBoard::GameOver(){
    if(getModel()->getMario()->getLife() < 0 || getModel()->getMario()->getRect().y() > 500){
        getModel()->getInsert()->setShow(true);
        insertTime = 0;
        if(getModel()->getSplashScreen()->getType() != SplashScreenType::GAME_OVER){
            getModel()->createGameOver(220, 100);
            getModel()->getSplashScreen()->setType(SplashScreenType::GAME_OVER);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}

bool GameBoard::Completed(){
    if(getModel()->getMario()->getGoldNumber() >= 200){
        if(getModel()->getSplashScreen()->getType() != SplashScreenType::COMPLETED){
            getModel()->createCompleted(360, 120);
            getModel()->getSplashScreen()->setType(SplashScreenType::COMPLETED);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}


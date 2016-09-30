#include "view.h"
#include <QPainter>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <tuple>
#include "model.h"
#include "paintvisitor.h"

View::View(QWidget *parent): QWidget(parent)
{}

View::~View()
{
    std::cout << ("View deleted\n");
}


void View::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
   PaintVisitor *pVisitor = new PaintVisitor(&painter);

    for(int i = control->getModel()->getCounter()->indexOf(control->getModel()->getCounter()->first()); i<control->getModel()->getCounter()->size(); i++){
        if(control->getMoveMap()){
            control->getModel()->getCounter()->at(i)->moveBrick();
        }
    }



        for(int i = control->getModel()->getBackground()->indexOf(control->getModel()->getBackground()->first()); i<control->getModel()->getBackground()->size(); i++){
  if(control->getMoveMap())
            control->BackgroundAnim(i);         
                control->getModel()->getBackground()->at(i)->accept(pVisitor);

      }

    for(int i = 0; i<control->getModel()->getMushroom()->size(); i++){
        control->intersectMushroomMario(i);
        control->movementMushroom(i);
        control->getModel()->getMushroom()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getPiranhaPlant()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getPiranhaPlant()->at(i)->move(control->getModel()->getPiranhaPlant()->at(i)->getRect().x() - Brick::speed, control->getModel()->getPiranhaPlant()->at(i)->getRect().y());
        control->movementPiranhaPlant(i);
        control->getModel()->getPiranhaPlant()->at(i)->accept(pVisitor);
    }


    for(int i = 0; i<control->getModel()->getGround()->size(); i++){
    if(control->getMoveMap())
            control->getModel()->getGround()->at(i)->moveBrick();
        control->getModel()->getGround()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getSafes()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getSafes()->at(i)->moveBrick();
        control->getModel()->getSafes()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getGold()->size(); i++){
        control->intersectGoldMario(i);
        if(control->getMoveMap())
           control->getModel()->getGold()->at(i)->moveBrick();
        control->getModel()->getGold()->at(i)->setSrcRect(QRect(Gold::currentFrame, 0, control->getModel()->getGold()->at(i)->getRect().width(), control->getModel()->getGold()->at(i)->getRect().height()));
        control->getModel()->getGold()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFlame()->size(); i++){
        control->intersectFlameMario(i);
        //control->flameAnim(i);
      control->getModel()->getFlame()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getBomb()->size(); i++){
        if(control->getModel()->getBomb()->at(i)->isDestroyed() && control->getMoveMap())
            control->getModel()->getBomb()->at(i)->moveBrick();
        control->bombAnim(i);
        control->getModel()->getBomb()->at(i)->accept(pVisitor);
    }

    if(control->getModel()->getSmash()->getShow()){
        control->getModel()->getSmash()->setSrcRect(QRect(0, Smash::currentFrame, control->getModel()->getSmash()->getRect().width(), control->getModel()->getSmash()->getRect().height()));
        control->getModel()->getSmash()->accept(pVisitor);
    }

    if(control->getModel()->getMario()->getIsLittle()){
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 25, control->getModel()->getMario()->getMoveRSprite().height() - 30));
        control->getModel()->getMario()->setSrcRect(QRect(control->getModel()->getMario()->getCurrentFrame()+6, 0, control->getModel()->getMario()->getRect().width()+25, control->getModel()->getMario()->getRect().height()+27));
    }
    else{
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 45, control->getModel()->getMario()->getMoveRSprite().height() - 7));
        control->getModel()->getMario()->setSrcRect(QRect(control->getModel()->getMario()->getCurrentFrame()+6, 1, control->getModel()->getMario()->getRect().width(), control->getModel()->getMario()->getRect().height()));
    }

    control->getModel()->getMario()->accept(pVisitor);

    if(control->getModel()->getInsert()->getShow())
        control->getModel()->getInsert()->accept(pVisitor);

    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 0, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 17, 0, true));
    QString goldText = QString::number(control->getModel()->getMario()->getGoldNumber());
    painter.drawText(control->getModel()->getHeader()->getGoldPosition(), goldText);

    painter.save();
    if(control->getModel()->getMario()->getUntouchable())
        painter.setOpacity(0.4);
    else
        painter.setOpacity(1);

    for(int i = 0 ; i < control->getModel()->getMario()->getLife() ; i++){

    }
    painter.restore();

    if(control->GameOver()){
        painter.fillRect(QRect(0, 0, Model::Length, Model::Height), QBrush(QColor(0, 0, 0, 230))); // Create a Semi transparent color 0,0,0 is black, the last value is how transparent
    }
    else if(control->Completed())
        painter.fillRect(QRect(0, 0, Model::Length, Model::Height), QBrush(QColor(0, 0, 0, 230)));

    if(control->getModel()->getSplashScreen()->getIsSplashScreen()){
        control->getModel()->getSplashScreen()->accept(pVisitor);
    }

}

//-------------------------------------------------------------------------------------------------------------------//

//Mario Control
void View::keyPressEvent(QKeyEvent *event)
{
    if(!control->GameOver()){
        if(event->key() == Qt::Key_Right)
            control->setIsMovingR(true);
        else if(event->key() == Qt::Key_Left)
            control->setIsMovingL(true);
        else if(event->key() == Qt::Key_Down && control->getIsJumping())
            control->setIsAttacking(true);
        else if(event->key() == Qt::Key_Space && control->intersectBottomMario(0)){
            control->setIsJumping(true);
            control->setXRelatif(-100);
        }
        else
            event->ignore();
    }
    else if(event->key() == Qt::Key_Enter){

    }

    if (event->key() == Qt::Key_Escape)
    {
        control->stopGame();
        qApp->exit();
    }

}

//----------------------------------------------------------------------------------------------------------------//

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right )
        control->setIsMovingR(false);
    else if(event->key() == Qt::Key_Left )
        control->setIsMovingL(false);
    else
        event->ignore();
}

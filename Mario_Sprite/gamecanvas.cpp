#include "gamecanvas.h"
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>

GameCanvas::GameCanvas( QWidget* parent ):QWidget( parent ){

    m_mario = new MarioSprite();
    startTimer( 100 );
}

GameCanvas::~GameCanvas(){
    delete m_mario;
}

void GameCanvas::paintEvent(QPaintEvent *){
    QPainter painter(this);
    m_mario->draw( &painter );
}

void GameCanvas::timerEvent(QTimerEvent *){
    m_mario->nextFrame();    
    repaint();
}

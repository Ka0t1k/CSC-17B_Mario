#include "gamecanvas.h"
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>

GameCanvas::GameCanvas( QWidget* parent ):QWidget( parent ){

    m_bomb = new BombSprite();
    startTimer( 100 );
}

GameCanvas::~GameCanvas(){
    delete m_bomb;
}

void GameCanvas::paintEvent(QPaintEvent *){
    QPainter painter(this);
    m_bomb->draw( &painter );
}

void GameCanvas::timerEvent(QTimerEvent *){
    m_bomb->nextFrame();
    repaint();
}

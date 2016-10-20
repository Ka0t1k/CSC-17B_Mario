#include "gamecanvas.h"
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>

GameCanvas::GameCanvas( QWidget* parent ):QWidget( parent ){

    m_coin = new CoinSprite();
    startTimer( 100 );
}

GameCanvas::~GameCanvas(){
    delete m_coin;
}

void GameCanvas::paintEvent(QPaintEvent *){
    QPainter painter(this);
    m_coin->draw( &painter );
}

void GameCanvas::timerEvent(QTimerEvent *){
    m_coin->nextFrame();
    repaint();
}

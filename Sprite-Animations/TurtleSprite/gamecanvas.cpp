#include "gamecanvas.h"
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>

GameCanvas::GameCanvas( QWidget* parent ):QWidget( parent ){

    m_turtle = new TurtleSprite();
    startTimer( 100 );
}

GameCanvas::~GameCanvas(){
    delete m_turtle;
}

void GameCanvas::paintEvent(QPaintEvent *){
    QPainter painter(this);
    m_turtle->draw( &painter );
}

void GameCanvas::timerEvent(QTimerEvent *){
    m_turtle->nextFrame();
    repaint();
}

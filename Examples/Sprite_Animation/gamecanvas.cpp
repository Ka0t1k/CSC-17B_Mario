    #include "gamecanvas.h"
    #include <QPainter>
    #include <QDebug>
    #include <QTimerEvent>
    
    GameCanvas::GameCanvas( QWidget* parent )
        :QWidget( parent )
    {
        mSprite = new Sprite();
       startTimer( 100 );
   }
   
   GameCanvas::~GameCanvas()
   {
       delete mSprite;
   }
   
   void GameCanvas::paintEvent(QPaintEvent */*event*/)
   {
       QPainter painter(this);
       QBrush brush(Qt::SolidPattern);
       brush.setColor(Qt::white);
       //painter.setBrush( brush );
       painter.fillRect(this->rect(),brush);
       mSprite->draw( &painter);
   
   }
   
   void GameCanvas::timerEvent(QTimerEvent *event)
   {
       mSprite->nextFrame();
      if( mSprite->pos().x() < 0 || mSprite->pos().x() + 100 >= rect().width() ){
          mSprite->changeDir();
       }
       repaint();
   }

#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QWidget>

#include "turtlesprite.h"

class GameCanvas : public QWidget
{
    Q_OBJECT

public:
    GameCanvas( QWidget* parent= 0 );
    ~GameCanvas();
    void paintEvent(QPaintEvent *painter);
    void timerEvent(QTimerEvent *);

public slots:



private:
    TurtleSprite* m_turtle;
};

#endif // GAMECANVAS_H

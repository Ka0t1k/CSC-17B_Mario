#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QWidget>

#include "mariosprite.h"

class GameCanvas : public QWidget
{
    Q_OBJECT

public:
    GameCanvas( QWidget* parent= 0 );
    ~GameCanvas();


public slots:

    void paintEvent(QPaintEvent *painter);
    void timerEvent(QTimerEvent *);

private:
    MarioSprite* m_mario;
};

#endif // GAMECANVAS_H

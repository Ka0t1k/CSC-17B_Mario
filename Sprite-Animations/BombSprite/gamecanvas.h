#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QWidget>

#include "bombsprite.h"

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
    BombSprite* m_bomb;
};

#endif // GAMECANVAS_H

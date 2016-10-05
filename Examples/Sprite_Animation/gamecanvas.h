#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QWidget>
#include "sprite.h"

class GameCanvas : public QWidget
{
    Q_OBJECT

public:
    GameCanvas( QWidget* parent= 0 );

    ~GameCanvas();

public slots:

    void paintEvent(QPaintEvent *event);

    void timerEvent(QTimerEvent *);

private:

    Sprite* mSprite;
};

#endif // GAMECANVAS_H

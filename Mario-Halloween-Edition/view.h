#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include <QDebug>

#include "safe.h"
#include "ground.h"
#include "mario.h"
#include "gold.h"
#include "view.h"
#include "gameboard.h"
#include "bomb.h"
#include "mushroom.h"
#include "questnbox.h"

class GameBoard;

class View : public QWidget
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
     ~View();
    void setControl(GameBoard *control){ this->control = control; }

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    GameBoard *control;
    int marioSize;
    //int timerId;
    QTimer *autoMoveTimer;
};

#endif // VIEW_H

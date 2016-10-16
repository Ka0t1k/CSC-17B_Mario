#ifndef TITLE_H
#define TITLE_H

#include "mainwindow.h"
class View;

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);
signals:
    void quitGame();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;
};

#endif // TITLE_H

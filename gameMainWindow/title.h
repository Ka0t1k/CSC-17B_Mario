#ifndef TITLE_H
#define TITLE_H

#include "mainwindow.h"
class View;

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);
private:
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
};

#endif // TITLE_H

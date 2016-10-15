#include "title.h"

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    background = new QGraphicsPixmapItem(QPixmap(":images/title.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));
    //border = new QGraphicsPixmapItem(QPixmap(":images/border.png"));

    logo->setPos(330,50);
    logo->setScale(0.8);

    addItem(background);
    addItem(logo);
    //addItem(border);

    view->setScene(this);
}

#include "title.h"

Title::Title(QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap(":images/title.png"));
    QGraphicsPixmapItem *logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));
    logo->setPos(330,30);
    logo->setScale(0.8);
    scene->addItem(background);
    scene->addItem(logo);
    this->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Title::showEvent(QShowEvent *){
    this->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
}

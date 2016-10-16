#include "view.h"

View::View(){
    bgm = new QMediaPlaylist;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::showEvent(QShowEvent *){
    //fitInView(scene()->sceneRect(), Qt::IgnoreAspectRatio);
    //fitInView(scene()->itemsBoundingRect(), Qt::IgnoreAspectRatio);
}

void View::sceneSet(QMediaPlaylist *music, QGraphicsScene *scene){
    bgm = music;
    setScene(scene);
    emit sceneChanged();
}

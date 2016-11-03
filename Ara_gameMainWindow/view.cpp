#include "view.h"

View::View(){
    bgm = new QMediaPlaylist;
    this->setSceneRect(0,0,1280,720);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::sceneSet(QMediaPlaylist *music, QGraphicsScene *scene){
    this->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    bgm = music;
    setScene(scene);
    emit sceneChanged();
}

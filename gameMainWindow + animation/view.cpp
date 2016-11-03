#include "view.h"

View::View(){
    bgm = new QMediaPlaylist;
    //this->setFixedSize(1280,720);
    this->setSceneRect(0,0,1280,720);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
}

void View::sceneSet(QMediaPlaylist *music, QGraphicsScene *scene){
    this->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    bgm = music;
    setScene(scene);
    emit sceneChanged();
}

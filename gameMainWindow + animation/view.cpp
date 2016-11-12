#include "view.h"

View::View(){
    this->setSceneRect(0,0,1280,720);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::sceneSet(QGraphicsScene *scene){
    this->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    setScene(scene);
    emit sceneChanged();
}

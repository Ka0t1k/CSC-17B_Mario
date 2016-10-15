#include "view.h"
#include <iostream>

View::View(){
    setSceneRect(0,0,1280,720);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::showEvent(QShowEvent *){
    //fitInView(scene()->sceneRect(), Qt::IgnoreAspectRatio);
    fitInView(scene()->itemsBoundingRect(), Qt::IgnoreAspectRatio);
}

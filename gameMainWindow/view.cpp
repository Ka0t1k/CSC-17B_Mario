#include "view.h"

View::View(){
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::showEvent(QShowEvent *){
    //fitInView(scene()->sceneRect(), Qt::IgnoreAspectRatio);
    fitInView(scene()->itemsBoundingRect(), Qt::IgnoreAspectRatio);
}

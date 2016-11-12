#ifndef VIEW_H
#define VIEW_H

#include "mainwindow.h"

class View : public QGraphicsView{
    Q_OBJECT
signals:
    void sceneChanged();
public:
    View();
    void sceneSet(QGraphicsScene *);

};

#endif // VIEW_H

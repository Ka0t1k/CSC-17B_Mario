#ifndef VIEW_H
#define VIEW_H

#include "mainwindow.h"

class View : public QGraphicsView{
    Q_OBJECT
protected:
    void showEvent(QShowEvent *);
signals:
    void sceneChanged();
public:
    View();
    void sceneSet(QMediaPlaylist *, QGraphicsScene *);
    QMediaPlaylist *bgm;

};

#endif // VIEW_H

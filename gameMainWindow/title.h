#ifndef TITLE_H
#define TITLE_H

#include "mainwindow.h"

class Title : public QGraphicsView{
    Q_OBJECT
public:
    Title(QWidget *parent = 0);
protected:
    void showEvent(QShowEvent *);
private:
    QGraphicsScene *scene;
};

#endif // TITLE_H

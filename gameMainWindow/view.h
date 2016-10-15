#ifndef VIEW_H
#define VIEW_H

#include "mainwindow.h"

class View : public QGraphicsView{
protected:
    void showEvent(QShowEvent *);
public:
    View();
};

#endif // VIEW_H

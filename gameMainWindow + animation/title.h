#ifndef TITLE_H
#define TITLE_H

#include "mainwindow.h"
#include "myscene.h"
class View;
class placeHolderScene;

class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);
signals:
    void quitGame();
    void playSound(QString);
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    AnimatedGraphicsItem *background;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;
    QMediaPlaylist *playlist;
    QPropertyAnimation *animation;
    MyScene *scene;
};

#endif // TITLE_H

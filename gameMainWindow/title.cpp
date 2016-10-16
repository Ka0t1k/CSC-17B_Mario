#include "title.h"
#include <iostream>

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    background = new QGraphicsPixmapItem(QPixmap(":/images/title.png"));
    cursor = new QGraphicsPixmapItem(QPixmap(":/images/cursor.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));

    QFont font("Times", 40, QFont::PreferOutline, true);
    start = new QGraphicsTextItem;
    start->setPlainText("S t a r t  G a m e");
    start->setDefaultTextColor(Qt::black);
    start->setFont(font);
    start->setPos((width - start->boundingRect().width()) / 2, height - 250);

    quit = new QGraphicsTextItem;
    quit->setPlainText("Q u i t  G a m e");
    quit->setDefaultTextColor(Qt::black);
    quit->setFont(font);
    quit->setPos((width - quit->boundingRect().width()) / 2, height - 200);

    cursor->setPos((width - start->boundingRect().width()) / 2 - cursor->boundingRect().width(), height - 250);
    logo->setPos((width - logo->boundingRect().width()) / 2, 50);

    addItem(background);
    addItem(logo);
    addItem(cursor);
    addItem(start);
    addItem(quit);

    this->setFocus();
    view->setScene(this);
}

void Title::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up){
        if(selection == 0){
            selection++;
            cursor->moveBy(0,50);
        } else{
            selection--;
            cursor->moveBy(0,-50);
        }
    }
    if(event->key() == Qt::Key_Down){
        if(selection == 1){
            selection--;
            cursor->moveBy(0,-50);
        } else{
            selection++;
            cursor->moveBy(0,50);
        }
    }
    if(event->key() == Qt::Key_Z){
        if(selection == 0){

        }
        if(selection == 1){
            emit quitGame();
        }
    }
}

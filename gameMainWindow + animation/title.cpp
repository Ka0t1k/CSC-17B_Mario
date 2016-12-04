#include "title.h"

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();

    //ARA
    /*
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/Title.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    selectSFX = new QSoundEffect();
    selectSFX->setSource(QUrl("qrc:/music/Select.wav"));
    */
    background = new AnimatedGraphicsItem;
    background->setPixmap(QPixmap(":/images/background.png"));
    foreground = new QGraphicsPixmapItem(QPixmap(":/images/title.png"));
    cursor = new QGraphicsPixmapItem(QPixmap(":/images/cursor.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));

    animation = new QPropertyAnimation(background, "pos");
    animation->setLoopCount(-1);
    animation->setDuration(150000);
    animation->setStartValue(QPoint(-width,0));
    animation->setEndValue(QPoint(0,0));
    animation->start();

    QFont font("MV Boli", 30, QFont::Bold);
    start = new QGraphicsTextItem;
    start->setPlainText("S t a r t  G a m e");
    start->setDefaultTextColor(Qt::black);
    start->setFont(font);
    start->setPos((width - start->boundingRect().width()) / 2, height - 275);

    quit = new QGraphicsTextItem;
    quit->setPlainText("Q u i t  G a m e");
    quit->setDefaultTextColor(Qt::black);
    quit->setFont(font);
    quit->setPos((width - quit->boundingRect().width()) / 2, height - 275 + start->boundingRect().height());

    cursor->setPos((width - start->boundingRect().width()) / 2 - cursor->boundingRect().width(), (height - 275 + start->boundingRect().height() / 4));
    logo->setPos((width - logo->boundingRect().width()) / 2, height / 12);
    addItem(background);
    addItem(foreground);
    addItem(logo);
    addItem(cursor);
    addItem(start);
    addItem(quit);

    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);
}

void Title::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up){
        if(selection == 0){
            selection++;
            cursor->moveBy(0,start->boundingRect().height());
        } else{
            selection--;
            cursor->moveBy(0,-start->boundingRect().height());
        }
        emit playSound("select");
    }
    if(event->key() == Qt::Key_Down){
        if(selection == 1){
            selection--;
            cursor->moveBy(0,-start->boundingRect().height());
        } else{
            selection++;
            cursor->moveBy(0,start->boundingRect().height());
        }
        emit playSound("select");
    }
    if(event->key() == Qt::Key_Z){
        if(selection == 0){
            scene = new MyScene(scroll);
            viewer->sceneSet(scene);
        }
        if(selection == 1){
            qApp->exit();
        }
    }
}

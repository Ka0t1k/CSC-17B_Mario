#include <QApplication>
#include <QDateTime>
#include <QGraphicsView>
#include <QSplashScreen>
#include <QMediaPlayer>
#include <QScrollBar>
#include "myscene.h"
#include<QTimer>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //QMediaPlayer * music = new QMediaPlayer();
   // music->setMedia(QUrl("qrc:/audio/ThemeSong.mp3"));
    //music->play();

    //qsrand(QDateTime::currentMSecsSinceEpoch());
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/mariosplash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight, Qt::white);
    //MainWindow Mainwin;

    QGraphicsView view;

    //view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar* pos= view.horizontalScrollBar();
    MyScene scene(pos);
    view.setScene(&scene);
    view.setFixedSize(QSize(1280, 720));

    pos->setValue((int) 1);

    QTimer::singleShot(50,splash,SLOT(close()));
    QTimer::singleShot(50,&view,SLOT(show()));

    return a.exec();
}


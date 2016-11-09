#include <QApplication>
#include <QDateTime>
#include <QGraphicsView>
#include <QSplashScreen>
#include <QMediaPlayer>
#include "myscene.h"
#include<QTimer>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/audio/ThemeSong.mp3"));
    music->play();

    //qsrand(QDateTime::currentMSecsSinceEpoch());
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/mariosplash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight, Qt::white);
    //MainWindow Mainwin;

    MyScene scene;
    QGraphicsView view;

    //view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setScene(&scene);
    view.setFixedSize(scene.sceneRect().size().toSize());

    //Mainwin.setWindowTitle("Mario");
    //Mainwin.setCentralWidget(&view);
   // Mainwin.setFixedSize(1280,720);

    QTimer::singleShot(5000,splash,SLOT(close()));
    QTimer::singleShot(5000,&view,SLOT(show()));
    //Mainwin.show();


    return a.exec();
}


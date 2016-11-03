#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon"));
    //QSplashScreen *splash = new QSplashScreen;
    //splash->setPixmap(":/image/splash.png");
    //splash->show();

    MainWindow mainWin;
    mainWin.setSize();
    mainWin.show();

    //splash->finish(&mainWin);
    //delete splash;

    return a.exec();
}

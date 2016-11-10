#include "ara_sound_manager.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ara_Sound_Manager w;
    //w.show();
    //w.playSoundEffect("theme");
    return a.exec();
}

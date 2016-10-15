#include "ara_sound_manager.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ara_Sound_Manager w;

    //w.playSoundEffect("coin");

    w.playSoundEffect("mario_jump");
    w.show();
    return a.exec();
}

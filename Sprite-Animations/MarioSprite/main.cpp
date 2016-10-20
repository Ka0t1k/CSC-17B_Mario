#include <QApplication>
#include "gamecanvas.h"

int main( int argc, char* argv[] )
{
    QApplication app( argc,argv);

    GameCanvas game;
    game.show();

    return app.exec();
}
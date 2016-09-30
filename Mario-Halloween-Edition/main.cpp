#include "gameboard.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMediaPlayer>
#include "model.h"
#include "view.h"

void center(QWidget &widget)
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setMedia(QUrl("qrc:/music/ThemeSong.mp3"));
            music->play();


    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    //Length
    x = (screenWidth - Model::Length) / 6;
    //Height
    y = (screenHeight - Model::Height) / 2;

    widget.setGeometry(x, y, Model::Length, Model::Height);
    widget.setFixedSize(Model::Length, Model::Height);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Model m;
    View v;
    GameBoard window(&m, &v);
    v.setWindowTitle("Team Mario RCC");
    v.show();
    center(v);
    return app.exec();
}

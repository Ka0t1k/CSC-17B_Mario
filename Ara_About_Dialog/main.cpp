#include "about_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    About_Dialog w;

    w.show();

    return a.exec();
}

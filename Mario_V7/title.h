#ifndef TITLE_H
#define TITLE_H
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include "mainwindow.h"
#include "myscene.h"
#include <QMessageBox>
#include "database.h"

class View;
class LoginWindow;
class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);
   // bool regUsr(Query);
    //bool chkUsr(Query);
    Connection createConnection();
signals:
    void quitGame();
    void playSound(QString);
protected:
    //void keyPressEvent(QKeyEvent *event);

private slots:
     void login();
     void newUser();
     void developerLogin();
     void on_radioButton_toggled(bool checked);
private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    Connection DBase;
    AnimatedGraphicsItem *background;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;
    QMediaPlaylist *playlist;
    QPropertyAnimation *animation;
    QScrollBar *scroll;
    MyScene *scene;
    QPushButton *loginButton;
    QPushButton *newUserButton;
    QPushButton *developerButton;
    LoginWindow *loginWindow;
    QLineEdit * userLine;
    QLineEdit * passLine;
    QLabel *userName;
    QLabel *radioText;

    QLabel *password;
    QRadioButton *radioButton;
    QSqlDatabase db;

};

#endif // TITLE_H

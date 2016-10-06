#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStyle>
#include "settings.h"
#include "title.h"
class Settings;
class Title;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
    void setSize();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void returnTitle();
    void save();
    void load();
    void settings();
    void fullScreen(bool);
    void alterScreen();
    void volumeAdjust(int);
    void about();
private:
    void createActions();
    void createMenus();
    enum { maxState = 10 };
    Title *title;
    Settings *setting;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QAction *returnAction;
    QAction *emptyAction;
    QAction *saveStateAction[maxState];
    QAction *loadStateAction[maxState];
    QAction *quitAction;
    QAction *fullScreenAction;
    QAction *settingsAction;
    QAction *aboutAction;
    QMenu *fileMenu;
    QMenu *saveSubMenu;
    QMenu *loadSubMenu;
    QMenu *viewMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QMediaPlayer *music;
};

#endif // MAINWINDOW_H

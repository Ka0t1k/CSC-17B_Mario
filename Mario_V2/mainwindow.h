#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>
#include <QSoundEffect>
#include <QSpacerItem>
#include <QSpinBox>
#include <QSplashScreen>
#include <QStatusBar>
#include <QStyle>

#include "ara_sound_manager.h"
#include "about_dialog.h"

#include "settings.h"
#include "title.h"
#include "view.h"


class About_Dialog;
class Settings;
class Title;
class View;

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
    void bgmAdjust(int);
    void sfxAdjust(int);
    void showAbout();
private:
    void createActions();
    void createMenus();
    void createScene();
    enum { maxState = 10 };
    Settings *setting;
    About_Dialog *about;

    Title *title;
    View *view;

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

    Ara_Sound_Manager *soundManager;

signals:
    void playSound(QString);


};



#endif // MAINWINDOW_H

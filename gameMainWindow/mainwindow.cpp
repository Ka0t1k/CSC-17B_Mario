#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(){
    createActions();
    createMenus();
    createScene();
    setCentralWidget(view);
}

void MainWindow::closeEvent(QCloseEvent *){
    setting->writeSettings();
}

void MainWindow::createActions(){
    returnAction = new QAction(tr("&Return to Title"), this);
    returnAction->setShortcut(tr("Ctrl+R"));
    returnAction->setStatusTip(tr("Return to the title screen"));
    connect(returnAction, SIGNAL(triggered()), this, SLOT(returnTitle()));

    for(int i=0;i<maxState;++i){
        saveStateAction[i] = new QAction("-Empty-", this);
        loadStateAction[i] = new QAction("-Empty-", this);
    }

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    fullScreenAction = new QAction(tr("Full Screen"), this);
    fullScreenAction->setShortcut(tr("F11"));
    fullScreenAction->setStatusTip(tr("Fullscreen View"));
    connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(alterScreen()));

    settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setStatusTip(tr("Change Game Settings"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settings()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    music = new QMediaPlayer();
    setting = new Settings(this);
    connect(setting, SIGNAL(volumeAdjust(int)), this, SLOT(volumeAdjust(int)));
    connect(setting, SIGNAL(fullScreen(bool)), this, SLOT(fullScreen(bool)));
    setting->readSettings();
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(returnAction);
    saveSubMenu = fileMenu->addMenu(tr("&Save"));
    loadSubMenu = fileMenu->addMenu(tr("&Load"));
    for(int i=0;i<maxState;i++){
        saveSubMenu->addAction(saveStateAction[i]);
        loadSubMenu->addAction(loadStateAction[i]);
    }
    fileMenu->addAction(quitAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(fullScreenAction);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(settingsAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

    //menuBar()->setNativeMenuBar(false);
}

void MainWindow::createScene(){
    view = new View;
    connect(view, SIGNAL(sceneChanged()), this, SLOT(setMusic()));

    title = new Title(view);
    connect(title, SIGNAL(quitGame()), this, SLOT(close()));
}

void MainWindow::setSize(){
    this->setFixedSize(1280,720);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

void MainWindow::returnTitle(){

}

void MainWindow::save(){

}

void MainWindow::load(){

}

void MainWindow::settings(){
    setting->setState();
    setting->show();
}

void MainWindow::fullScreen(bool screen){
    if(screen){
        //setWindowFlags(Qt::FramelessWindowHint);
        this->showFullScreen();
    } else {
        this->showNormal();;
    }
}

void MainWindow::alterScreen(){
    setting->alterState();
}

void MainWindow::setMusic(){
    music->setPlaylist(view->bgm);
    music->play();
}

void MainWindow::volumeAdjust(int volume){
    music->setVolume(volume);
}

void MainWindow::showAbout(){
    about = new About_Dialog;
    about->exec();
}

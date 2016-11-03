#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSlider>
#include<QMessageBox>
#include <QSpinBox>
#include<QHBoxLayout>
#include "dialog.h"
#include <QMediaPlayer>
#include<QApplication>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/music/ThemeSong.mp3"));
    player->play();

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","A super Mario Game!");

}

void MainWindow::on_actionVolume_triggered()
{

       QWidget *window = new QWidget;
       window->setWindowTitle("Volume");

       QSpinBox *spinBox = new QSpinBox;
       QSlider *Volume = new QSlider(Qt::Horizontal,this);
       spinBox->setRange(0, 100);
       Volume->setRange(0, 100);

       QObject::connect(spinBox, SIGNAL(valueChanged(int)),Volume, SLOT(setValue(int)));
       QObject::connect(Volume, SIGNAL(valueChanged(int)),spinBox, SLOT(setValue(int)));

       spinBox->setValue(35);

       QHBoxLayout *layout = new QHBoxLayout;
       layout->addWidget(spinBox);
       layout->addWidget(Volume);
       window->setLayout(layout);

       window->show();


}


int MainWindow::volume() const
{

}

void MainWindow::setVolume(int volume)
{

}

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);

}

void Dialog::on_sliderProgress_sliderMoved(int position)
{
player->setPosition(position);
}



void Dialog::on_pushButton_clicked()
{

player->setMedia(QUrl("qrc:/music/ThemeSong.mp3"));
player->play();

}

void Dialog::on_pushButton_2_clicked()
{
player->stop();
}

void Dialog::on_positionChanged(qint64 position)
{
ui->sliderProgress->setValue(position);
}

void Dialog::on_durationChanged(qint64 position)
{
ui->sliderProgress->setMaximum(position);
}

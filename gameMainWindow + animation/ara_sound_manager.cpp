#include "ara_sound_manager.h"
#include "ui_ara_sound_manager.h"

//if we use a sound manager object for the level/enemy sounds then it should
//limit the amount of runtime resources
//not sure how much it will affect load times.
Ara_Sound_Manager::Ara_Sound_Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ara_Sound_Manager)
{
    ui->setupUi(this);

    this->select = new QSoundEffect;
    select->setSource(QUrl("qrc:/sounds/audio/Select.wav"));
    select->setLoopCount(0);
    select->setVolume(.25f);


    this->coin = new QSoundEffect;
    coin->setSource(QUrl("qrc:/sounds/audio/smw_coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);
    //coin->play();

    this->mario_jump = new QSoundEffect;
    mario_jump->setSource(QUrl("qrc:/sounds/audio/smw_jump.wav"));
    mario_jump->setLoopCount(0);
    mario_jump->setVolume(.25f);
    //mario_jump->play();

    this->mario_death = new QSoundEffect;
    mario_death->setSource(QUrl("qrc:/sounds/audio/smw_lost_a_life.wav"));
    mario_death->setLoopCount(0);
    mario_death->setVolume(.20f);
    //mario_death->play();

    this->mario_mushroom = new QSoundEffect;



    this->soundPlayer = new QMediaPlayer;
    soundPlayer->setVolume(80);
    //soundPlayer->play();


}

Ara_Sound_Manager::~Ara_Sound_Manager()
{
    delete ui;
}

void Ara_Sound_Manager::playSoundEffect(QString which){

    if(which == "mario_jump"){
        this->mario_jump->play();
    }
    else if(which == "mario_death"){
        this->mario_death->play();
    }
    else if(which == "coin"){
        this->coin->play();
    }
    else if(which == "select"){
        this->select->play();
    }
    else if(which == "theme"){
        soundPlayer->setMedia(QUrl("qrc:/sounds/audio/ThemeSong.mp3"));
        soundPlayer->play();
    }
    else if(which == "title"){

    }

}


void Ara_Sound_Manager::setBGMVolume(int volume){
    this->soundPlayer->setVolume(volume);
}
void Ara_Sound_Manager::setSFXVolume(int volume){
    qreal qVolume = volume;
    qVolume /=100;

    this->mario_jump->setVolume(qVolume);
    this->mario_death->setVolume(qVolume);
    this->mario_mushroom->setVolume(qVolume);
    this->coin->setVolume(qVolume);
    this->select->setVolume(qVolume);

}



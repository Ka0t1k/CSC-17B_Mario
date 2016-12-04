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
    select->setSource(QUrl("qrc:/audio/Select.wav"));
    select->setLoopCount(0);
    select->setVolume(.25f);

    this->coin = new QSoundEffect;
    coin->setSource(QUrl("qrc:/audio/smw_coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);

    this->mario_jump = new QSoundEffect;
    mario_jump->setSource(QUrl("qrc:/audio/smw_jump.wav"));
    mario_jump->setLoopCount(0);
    mario_jump->setVolume(.25f);

    this->mario_death = new QSoundEffect;
    mario_death->setSource(QUrl("qrc:/audio/smw_lost_a_life.wav"));
    mario_death->setLoopCount(0);
    mario_death->setVolume(.25f);

    this->levelClear = new QSoundEffect;
    levelClear->setSource(QUrl("qrc:/audio/levelClear.mp3"));
    levelClear->setLoopCount(0);
    levelClear->setVolume(.25f);

    this->ghost = new QSoundEffect;
    ghost->setSource(QUrl("qrc:/audio/ghost.mp3"));
    ghost->setLoopCount(0);
    ghost->setVolume(.25f);

    this->mario_mushroom = new QSoundEffect;


    this->level1 = new QMediaPlayer;
    level1->setMedia(QUrl("qrc:/audio/level1.mp3"));

    this->soundPlayer = new QMediaPlayer;
    soundPlayer->setMedia(QUrl("qrc:/audio/ThemeSong.mp3"));

}

Ara_Sound_Manager::~Ara_Sound_Manager()
{
    delete ui;
}

void Ara_Sound_Manager::playSoundEffect(QString which){

    if(which == "mario_jump"){
        mario_jump->play();
    }
    else if(which == "mario_death"){
        mario_death->play();
    }
    else if(which == "coin"){
        coin->play();
    }
    else if(which == "select"){
        select->play();
    }
    else if(which == "theme"){
        level1->stop();
        soundPlayer->play();
    }
    else if(which == "title"){

    }
    else if(which == "level1"){
        soundPlayer->stop();
        level1->play();
    }
    else if(which == "level_clear"){
        levelClear->play();
    }
    else if(which == "ghost"){
        ghost->play();
    }

}


void Ara_Sound_Manager::setBGMVolume(int volume){
    this->soundPlayer->setVolume(volume);
    this->level1->setVolume(volume);
}
void Ara_Sound_Manager::setSFXVolume(int volume){
    qreal qVolume = volume;
    qVolume /=100;

    this->mario_jump->setVolume(qVolume);
    this->mario_death->setVolume(qVolume);
    this->mario_mushroom->setVolume(qVolume);
    this->coin->setVolume(qVolume);
    this->select->setVolume(qVolume);
    this->levelClear->setVolume(qVolume);
}



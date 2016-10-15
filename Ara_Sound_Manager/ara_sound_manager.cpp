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


    this->coin = new QSoundEffect;
    coin->setSource(QUrl("qrc:/sound/smw_coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);
    //coin->play();

    this->mario_jump = new QSoundEffect;
    mario_jump->setSource(QUrl("qrc:/sound/smw_jump.wav"));
    mario_jump->setLoopCount(0);
    mario_jump->setVolume(.25f);
    //mario_jump->play();

    this->mario_death = new QSoundEffect;
    mario_death->setSource(QUrl("qrc:/sound/smw_lost_a_life.wav"));
    mario_death->setLoopCount(10);
    mario_death->setVolume(.20f);
    //mario_death->play();

    this->levelTrack = new QMediaContent(QUrl::fromLocalFile(":/sound/smw_course_clear.wav"));
    this->soundPlayer = new QMediaPlayer;
    soundPlayer->setMedia(QUrl("qrc:/sound/smw_course_clear.wav"));
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


}

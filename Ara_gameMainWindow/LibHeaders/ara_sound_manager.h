#ifndef ARA_SOUND_MANAGER_H
#define ARA_SOUND_MANAGER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>


namespace Ui {
class Ara_Sound_Manager;
}

class Ara_Sound_Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Ara_Sound_Manager(QWidget *parent = 0);
    ~Ara_Sound_Manager();

    template <class T>
    void connectSound(T *);

private:
    Ui::Ara_Sound_Manager *ui;

    QSoundEffect * mario_jump, * mario_death, * mario_mushroom, * coin;


    QMediaContent * levelTrack;
    QMediaPlayer * soundPlayer;

public slots:
    void playSoundEffect(QString);


};

template <class T>
void Ara_Sound_Manager::connectSound(T * theClass){
    this->connect(theClass, SIGNAL(playSound(QString)), this, SLOT(playSoundEffect(QString)));
}

#endif // ARA_SOUND_MANAGER_H

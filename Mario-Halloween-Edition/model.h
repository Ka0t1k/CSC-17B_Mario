#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>

#include "splashscreen.h"
#include "header.h"
#include "background.h"
#include "mushroom.h"
#include "bomb.h"
#include "flame.h"
#include "piranhaplant.h"
#include "smash.h"
#include "insert.h"


class Safe;
class QuestnBox;
class Ground;
class Mario;
class Brick;
class Gold;
class WarpPipe;


class Model
{
public:
    Model();
    ~Model();
    void createBrick(QList<QChar> ,int ,int );
    void brickOrganization();
    inline Mario *getMario(){ return mario; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    Header *getHeader(){ return header; }
    QList<Brick*> *getCounter(){ return counter; }
    inline QList<Safe*> *getSafes(){ return safes; }

    inline QList<Ground*> *getGround(){ return ground; }
    inline QList<WarpPipe*> *getWarpPipe(){ return warppipe; }
    inline QList<QuestnBox*> *getQuestnBox(){ return questnbox; }
    inline QList<Background*> *getBackground(){ return background; }
    inline QList<Mushroom*> *getMushroom(){ return mushroom; }
    inline QList<Gold*> *getGold(){ return coin; }
    inline QList<Flame*> *getFlame(){ return flames; }
    inline QList<Bomb*> *getBomb(){ return bomb; }
    inline QList<PiranhaPlant*> *getPiranhaPlant(){ return piranhaPlant; }
    inline Smash *getSmash(){ return smash; }
    inline Insert *getInsert(){ return insert; }
    inline int getSpeed(){ return speed; }
    inline void setSpeed(int speed){ this->speed = speed; }
    void createMushroom(int, int, bool);
    bool getBombBool(){ return bombBool; }
    void setBombBool(bool value){ this->bombBool = value; }
    void createGameOver(int x, int y);
    void createInsert(int x, int y, QString image);
    void createCompleted(int x, int y);
    static int const brickSize = 50;
    static int const Height = 500;
    static int const Length = 1000;
    static int const NbrBrickVisible = 20;

private:
    QList<Safe*> *safes;
    QList<Mushroom*> *mushroom;
    QList<Ground*> *ground;
    QList<WarpPipe*> *warppipe;
    QList<QuestnBox*> *questnbox;
    QList<Brick*> *counter;
    QList<Background*> *background;
    QList<Gold*> *coin;
    QList<Flame*> *flames;
    QList<PiranhaPlant*> *piranhaPlant;
    QList<Bomb *> *bomb;
    Mario *mario;
    SplashScreen *splashScreen;
    Header *header;  
    Smash *smash;
    Insert *insert;

    QList<QChar> line1;
    QList<QChar> line2;
    QList<QChar> line3;
    QList<QChar> line4;
    QList<QChar> line5;
    QList<QChar> line6;
    int backgroundCount=0;
    int mapPosition = 6;
    int speed = 4;
    bool bombBool;

};

#endif // MODEL_H

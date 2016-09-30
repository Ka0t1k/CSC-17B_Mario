#include "model.h"
#include "brick.h"
#include "gold.h"
#include <mario.h>
#include <safe.h>
#include <ground.h>
#include <warppipe.h>
#include <QuestnBox.h>
#include "bomb.h"
#include <splashscreen.h>
#include <header.h>
#include "flame.h"
#include "smash.h"

#include "insert.h"
#include <QDebug>

Model::Model()
{
    this->background = new QList<Background *>;
    this->ground = new QList<Ground *>;
    this->warppipe = new QList<WarpPipe *>;
    this->safes = new QList<Safe*>;
    this->questnbox = new QList<QuestnBox*>;
    this->mushroom = new QList<Mushroom *>;
    this->coin = new QList<Gold *>;
    this->flames = new QList<Flame *>;
    this->splashScreen = new SplashScreen(330, 170, ":images/Mario_Logo.png");
    this->bomb =new QList<Bomb *>;
    this->background = new QList<Background *>;
    this->header = new Header();
    this->counter = new QList<Brick*> ;
    this->piranhaPlant = new QList<PiranhaPlant *>;
    this->mario = new Mario(200, 340);
    this->smash = new Smash(0,0);
    this->insert = new Insert(0,0, "");


    QFile file(":ModelMap.txt");

    if(file.open(QIODevice::ReadOnly)){
            QTextStream in (&file);
            while(!in.atEnd()){
                QString stock = in.readLine();
                if (stock.left(6)=="LINE_a"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line1.append(stock.at(i));
                        }
                    }
                }
                else if (stock.left(6)=="LINE_b"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line2.append(stock.at(i));
                        }
                    }
                }
                else if (stock.left(6)=="LINE_c"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line3.append(stock.at(i));
                        }
                    }
                }
                else if (stock.left(6)=="LINE_d"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line4.append(stock.at(i));
                        }
                    }
                }
                else if (stock.left(6)=="LINE_e"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line5.append(stock.at(i));
                        }
                    }
                }
                else if (stock.left(6)=="LINE_f"){
                    for(int i=0;i<stock.size();++i){
                        if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                            line6.append(stock.at(i));
                        }
                    }
                }
            }
            file.close();
        }

    for (int i=0; i<NbrBrickVisible; i++){
        Ground *k= new Ground (i*brickSize, Height-brickSize, QString(":images/Ground_Bottom.png"));
        ground->append(k);
        Ground  *k2= new Ground (i*brickSize, Height-2*brickSize, QString(":images/Ground_Main.png"));
        ground->append(k2);
    }
    for (int i=0; i<NbrBrickVisible; i++){
        Brick *b=new Brick(i*brickSize,Height+brickSize);
        counter->append(b);
    }
    for (int i=0; i<2; i++){
        Background* b = new Background(i*Model::Length, 0);
        background->append(b);
    }
}

//--------------------------------------------------------------------------------------------------------//

Model::~Model()
{
    ground->clear();
    delete ground;
    warppipe->clear();
    delete warppipe;
    questnbox->clear();
    delete questnbox;
    safes->clear();
    delete safes;    
    counter->clear();
    delete counter;
    background->clear();
    delete background;
    mushroom->clear();
    delete mushroom;
    bomb->clear();
    delete bomb;
    delete flames;
    coin->clear();
    delete coin;
    delete mario;
    delete splashScreen;
    piranhaPlant->clear();
    delete piranhaPlant;
}

//-----------------------------------------------------------------------------------------------------------------//

void Model::createBrick(QList<QChar> l ,int num ,int x){
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '1'){
        Ground  *k= new Ground(x+brickSize,Height-num*brickSize, QString(":images/Ground_Bottom.png"));
        ground->append(k);
        return;
    }
    else if(myChar == '2'){
        Safe* t= new Safe(x+brickSize, Height-num*brickSize);
        safes->append(t);
        return;
    }
    else if(myChar == '3'){
        Gold* g= new Gold(x+brickSize, Height-num*brickSize);
        coin->append(g);
        return;
    }
    else if(myChar == '4'){
        Bomb* d= new Bomb(x+brickSize, Height-num*brickSize);
        d->setMoveX(false);
        bomb->append(d);
        return;
    }
    else if(myChar == '5'){
        Flame* f = new Flame(x+brickSize, Height-num*brickSize);
        f->setMoveX(false);
        flames->append(f);
        return;
    }
    else if(myChar == '6'){
        Safe* t= new Safe(x+brickSize, Height-num*brickSize);
        t->setCapacity(2);
        safes->append(t);
        return;
    }
    else if(myChar == '7'){
        Ground  *k= new Ground (x+brickSize,Height-num*brickSize , QString(":images/Ground_Main.png"));
        ground->append(k);
        return;
    }
    else if(myChar == '8'){
        Ground  *k= new Ground (x+brickSize,Height-num*brickSize , QString(":images/Ground_Right.png"));
        ground->append(k);
        return;
    }
    else if(myChar == '9'){
        Ground  *k= new Ground (x+brickSize,Height-num*brickSize , QString(":images/Ground_Left.png"));
        ground->append(k);
        return;
    }  
    else if(myChar == 'a'){
        PiranhaPlant *k= new PiranhaPlant(x+brickSize,Height-num*brickSize);
        piranhaPlant->append(k);
        qDebug() << "Je Debug";
        return;
    }
    else if(myChar == 'v'){
        Ground  *v= new Ground (x+brickSize,Height-num*brickSize , QString(":images/Warp.png"));
        ground->append(v);
        return;
    }
    else if(myChar == 'q'){
        Ground  *q= new Ground (x+brickSize,Height-num*brickSize , QString(":images/Question.png"));
        ground->append(q);
        return;
    }
}

//----------------------------------------------------------------------------------------------------------------//

void Model::brickOrganization()
{
    for(int i = 0; i<background->size(); i++){
        if(background->at(i)->getRect().x() < - background->at(i)->getRect().width() + 2){
            background->removeAt(i);
            Background* b = new Background(1000,0);
            background->append(b);
        }
    }
    if(counter->last()->getRect().x()<((NbrBrickVisible)*brickSize)){
        Brick *b=new Brick(counter->last()->getRect().x()+brickSize,Height+brickSize);
        createBrick(line1,1,counter->last()->getRect().x());
        createBrick(line2,2,counter->last()->getRect().x());
        createBrick(line3,3,counter->last()->getRect().x());
        createBrick(line4,4,counter->last()->getRect().x());
        createBrick(line5,5,counter->last()->getRect().x());
        createBrick(line6,6,counter->last()->getRect().x());
        counter->append(b);
        mapPosition++;
    }

    if (counter->first()->getRect().x()<=-brickSize){
        counter->removeAt(counter->indexOf(counter->first()));
    }

    for(int i = 0; i<ground->size(); i++){
        if (ground->at(i)->getRect().x()<=-brickSize || ground->at(i)->isDestroyed()){
            ground->removeAt(i);
        }
    }

    for(int i = 0; i<safes->size(); i++){
        if (safes->at(i)->getRect().x()<=-brickSize || safes->at(i)->isDestroyed()){
            safes->removeAt(i);
        }
    }

    for(int i = 0; i<coin->size(); i++){
        if (coin->at(i)->getRect().x()<=-brickSize || coin->at(i)->isDestroyed()){
            coin->removeAt(i);
        }
    }

    for(int i = 0; i<mushroom->size(); i++){
        if (mushroom->at(i)->getRect().x()<=-brickSize || mushroom->at(i)->isDestroyed()){
            mushroom->removeAt(i);
        }
    }

    for(int i = 0; i<flames->size(); i++){
        if (flames->at(i)->getRect().x()<=-brickSize || flames->at(i)->isDestroyed()){
            flames->removeAt(i);
        }
    }

    for(int i = 0; i<bomb->size(); i++){
        if (bomb->at(i)->getRect().x()<=-brickSize ){
            bomb->removeAt(i);            \
        }
    }

}

void Model::createMushroom(int x, int y, bool up){
    Mushroom *m = new Mushroom(x+9, y+10, up);
    m->setYR(0);
    m->setXR(0);
    m->setStartY(m->getRect().y() + 50);
    mushroom->append(m);
}

void Model::createGameOver(int x, int y){
    this->splashScreen = new SplashScreen(x, y, ":images/gameover.png");
}

void Model::createCompleted(int x, int y){
    this->splashScreen = new SplashScreen(x, y, ":images/level_complete.png");
}

void Model::createInsert(int x, int y, QString image){
    this->insert = new Insert(x, y, image);
}

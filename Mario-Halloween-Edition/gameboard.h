#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QObject>
#include "safe.h"
#include "ground.h"
#include "mario.h"
#include "model.h"


class View;


class GameBoard : QObject
{
    Q_OBJECT

public:
    GameBoard(Model *m, View *v);
    ~GameBoard();
    void stopGame();
    void movementMario();
    void moveXMario(int );
    void movementBackground();
    void movementMushroom(int );

    void moveBrick(int ,Brick *);
    void movementPiranhaPlant(int );

    void movementMap(int );
    void splashScreen();
    bool GameOver();
    bool Completed();

    bool intersectBottomMario(int );
    bool intersectTopMario(int );
    bool intersectRightMario(int );
    bool intersectLeftMario(int );
    void intersectGoldMario(int );
    void intersectMushroomMario(int );
    void intersectYBombMario(int );
    void intersectXBombMario(int );
    void intersectFlameMario(int );
    bool intersectBottomBrick(Brick *);
    bool intersectRightBrick(Brick *);
    bool intersectLeftBrick(Brick *);
    void intersectPiranhaPlantMario(int i);

    void attackPiranhaPlant(int i);
    void goldAnim();
    void flameAnim();
    void smashAnim();
    void bombAnim(int );
    void BackgroundAnim(int );
    void fantom();

    inline bool getIsMovingR(){ return getModel()->getMario()->getIsMovingR(); }
    inline bool getIsMovingL(){ return getModel()->getMario()->getIsMovingL(); }
    inline bool getIsJumping(){ return getModel()->getMario()->getIsJumping(); }
    inline bool getIsAttacking(){ return getModel()->getMario()->getIsAttacking(); }
    inline void setIsMovingR(bool is){ getModel()->getMario()->setIsMovingR(is); }
    inline void setIsMovingL(bool is){ getModel()->getMario()->setIsMovingL(is); }
    inline void setIsJumping(bool is){ getModel()->getMario()->setIsJumping(is); }
    inline void setIsAttacking(bool is){ getModel()->getMario()->setIsAttacking(is); }
    inline void setIsGameOver(bool is){ this->isGameOver = is; }
    inline bool getIsGameOVer(){ return isGameOver; }
    bool getMoveMap(){return moveMap;}
    inline std::tuple<> getAllObjects();
    inline Model *getModel(){ return this->model; }
    inline qreal getOpacity(){ return opacity; }
    inline void setOpacity(qreal opacity){this->opacity = opacity; }
    inline int getXRelatif(){ return xRelatif; }
    inline void setXRelatif(int x){this->xRelatif = x; }

private:
    void timerEvent(QTimerEvent *event);

    Model *model;
    View *view;
    bool gameStarted;
    int xRelatif;
    int yRelatif;
    int startJumpY;
    int iterBackground;
    int tempMove = 0;
    int marioSize;
    int tempBomb = 0;

    int tempGold = 0;
    int tempFlame = 0;
    int tempSmash = 0;
    qreal opacity = 1;
    bool isLittle;
    bool isGameOver = false;
    bool moveMap=false;

    int insertTime = 0;
    int timerId=0;
};
#endif // GAMEBOARD_H

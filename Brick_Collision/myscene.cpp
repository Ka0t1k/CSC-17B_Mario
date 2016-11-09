#include "myscene.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "coin.h"
#include "backgrounditem.h"
#include "castle.h"
#include "goomba.h"
#include "questbox.h"
#include "glowbrick.h"
#include "turtle.h"
#include "piranha.h"


MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
  , m_velocity(7)
  , m_skippedMoving(0)
  , m_groundLevel(0)
  , m_minX(0)//minimum x coordinate of world
  , m_maxX(0)//maximum x coordinate of world
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(200)
  , m_fieldWidth(8000)//width of the virtual world
  , m_player()
  , m_sky(0)
  , m_Scene(0)
  , m_coins(0)
  , h_castle()
  , m_goomba()
  , m_questbox()
  , m_glowbrick()
  , m_turtle()
  ,m_piranha()
  ,m_platform()

{
    initPlayField();

    //timer emits a timeout signal every 20 milliseconds
    //Then we connect that signal to the scene's slot called movePlayer()
    //Pressing the arrow keys starts the timer
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    jumpSound = new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/audio/jump.mp3"));

    coinSound = new QMediaPlayer();
    coinSound->setMedia(QUrl("qrc:/audio/coin.mp3"));

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &MyScene::jumpFactorChanged, this, &MyScene::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &MyScene::jumpStatusChanged);
}

void MyScene::keyPressEvent(QKeyEvent *event)
{

    if (event->isAutoRepeat())  //First check if the key event was triggered because of an auto repeat
            return;             // Meaning that you are holding down the key. Qt will continuously deliver the key press event

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(-1);
        checkTimer();
        break;
    case Qt::Key_Space:
        if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
            m_jumpAnimation->start();

            if (jumpSound->state() == QMediaPlayer::PlayingState){
               jumpSound->setPosition(0);
           }
           else if (jumpSound->state() == QMediaPlayer::StoppedState){
               jumpSound->play();
           }

            //m_timer.start();
        }
        break;
    default:
        break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(-1);
        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(1);
        checkTimer();
        break;
        //    case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}

void MyScene::movePlayer()
{
    checkColliding();
    m_player->nextFrame();

    int direction = m_player->direction();     //Cache the player's current direction in a local variable to avoid multiple calls of direction()
    if (0 == direction)                       //check whether the player is moving at all. If they aren't, we exit the function
        return;


    QGraphicsItem* platform = collidingPlatforms();
//    qDebug() << " platform: "<< m_platform;
//    qDebug() << "Collding platform: " << platform;
//    //can not walk into platform
//    if(!m_platform && platform) {
//        return;
//    }
    const qreal y =(m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    //previously walking on platform, if there is no platform, step down
    if(!m_platform && !platform ) {
            qDebug() << "change pos1";
             m_player->setPos(m_player->pos().x(),y);
        }


    const int dx = direction * m_velocity; //we calculate the shift the player item should get and store it in dx.
                                          //The distance the player should move every 20 milliseconds is defined by the member variable m_velocity,expressed in pixels
                                         //Multiplied by the direction (which could only be 1 or -1 at this point), we get a shift of the player by 4 pixels to the right or to the left.

    qreal newPos = m_realPos + dx;     //Based on this shift, we calculate the new x position of the player and store it in newPos.
    if (newPos < m_minX)              //check whether that new position is inside the range of m_minX and m_maxX, two member variables that are already calculated and set up properly at this point
        newPos = m_minX;
    else if (newPos > m_maxX)       //if the new position is not equal to the actual position, which is stored in m_realPos, we proceed by assigning the new position as the current one
        newPos = m_maxX;
    if (newPos == m_realPos)      //Otherwise, we exit the function since there is nothing to move.
        return;
    m_realPos = newPos;

    const int rightBorder = 970 - m_player->boundingRect().width(); //How far the character can move before view moves
    const int leftBorder = 250;

    if (direction > 0) {

        if (m_realPos > m_fieldWidth - (width() - rightBorder)) {
            m_player->moveBy(dx, 0);
        } else {
            if (m_realPos - m_skippedMoving < rightBorder) {   //If the position of the character in "view coordinates", calculated by m_realPos – m_skippedMoving,
                m_player->moveBy(dx, 0);                      //is smaller than rightBorder, then move the character by calling moveBy()
            } else {
                m_skippedMoving += dx;                       //The m_skippedMoving element is the difference between the view's x coordinate and the virtual world's x coordinate
            }
        }
    } else {
        if (m_realPos < leftBorder && m_realPos >= m_minX) {

            m_player->moveBy(dx, 0);
        } else {
            if (m_realPos - m_skippedMoving > leftBorder) {
                m_player->moveBy(dx, 0);
            } else {
                m_skippedMoving = qMax(0, m_skippedMoving + dx);
            }
        }

    }

    /*
    MOVE THE BACKGROUND
    ff is the minimum shift (0 * shift, which equals 0) and the maximum shift (1 * shift, which equals shift).
    The calculation reads: If we subtract the width of the view (width()) from the virtual field's width m_fieldWidth, we have the area
    where the player isn't moved by (m_player->moveBy()) because in that range only thebackground should move.
    How often the moving of the player was skipped is saved in m_skippedMoving. So by
    dividing m_skippedMoving through m_fieldWidth – width(), we get the needed factor.
    */

    qreal ff = qMin(1.0, m_skippedMoving/(m_fieldWidth - width()));

    m_sky->setPos(-(m_sky->boundingRect().width() - width()) * ff, 0);

    m_coins->setPos( 1300+(m_coins->boundingRect().width()  - width()) * ff * 5.06, m_coins->y());
    m_coins2->setPos(1300+(m_coins2->boundingRect().width() - width()) * ff * 5.06, m_coins2->y());
    m_coins3->setPos(1300+(m_coins3->boundingRect().width() - width()) * ff * 5.06, m_coins3->y());
    m_coins4->setPos(1300+(m_coins4->boundingRect().width() - width()) * ff * 5.06, m_coins4->y());
    m_coins5->setPos(1350+(m_coins5->boundingRect().width() - width()) * ff * 5.06, m_coins5->y());
    m_coins6->setPos(1400+(m_coins6->boundingRect().width() - width()) * ff * 5.06, m_coins6->y());
    m_coins7->setPos(1400+(m_coins7->boundingRect().width() - width()) * ff * 5.06, m_coins7->y());
    m_coins8->setPos(1350+(m_coins8->boundingRect().width() - width()) * ff * 5.06, m_coins8->y());
    m_coins9->setPos(1400+(m_coins9->boundingRect().width() - width()) * ff * 5.06, m_coins9->y());
    m_coins10->setPos(1500+(m_coins10->boundingRect().width() - width()) * ff * 5.06, m_coins10->y());
    m_coins11->setPos(1500+(m_coins11->boundingRect().width() - width()) * ff * 5.06, m_coins11->y());
    m_coins12->setPos(1500+(m_coins12->boundingRect().width() - width()) * ff * 5.06, m_coins12->y());
    m_coins13->setPos(1500+(m_coins13->boundingRect().width() - width()) * ff * 5.06, m_coins13->y());
    m_coins14->setPos(1550+(m_coins14->boundingRect().width() - width()) * ff * 5.06, m_coins14->y());
    m_coins15->setPos(1600+(m_coins15->boundingRect().width() - width()) * ff * 5.06, m_coins15->y());
    m_coins16->setPos(1500+(m_coins16->boundingRect().width() - width()) * ff * 5.06, m_coins16->y());
    m_coins17->setPos(1550+(m_coins17->boundingRect().width() - width()) * ff * 5.06, m_coins17->y());
    m_coins18->setPos(1600+(m_coins18->boundingRect().width() - width()) * ff * 5.06, m_coins18->y());
    m_coins19->setPos(1700+(m_coins19->boundingRect().width() - width()) * ff * 5.06, m_coins19->y());
    m_coins20->setPos(1700+(m_coins20->boundingRect().width() - width()) * ff * 5.06, m_coins20->y());
    m_coins21->setPos(1700+(m_coins21->boundingRect().width() - width()) * ff * 5.06, m_coins21->y());
    m_coins22->setPos(1700+(m_coins22->boundingRect().width() - width()) * ff * 5.06, m_coins22->y());
    m_coins23->setPos(1750+(m_coins23->boundingRect().width() - width()) * ff * 5.06, m_coins23->y());
    m_coins24->setPos(1800+(m_coins24->boundingRect().width() - width()) * ff * 5.06, m_coins24->y());
    m_coins25->setPos(1750+(m_coins25->boundingRect().width() - width()) * ff * 5.06, m_coins25->y());
    m_coins26->setPos(1800+(m_coins26->boundingRect().width() - width()) * ff * 5.06, m_coins26->y());

    m_goomba->setPos(600+(m_goomba->boundingRect().width() - width()) * ff * 5.06, m_goomba->y());
    m_Scene->setPos(-(m_Scene->boundingRect().width() - width()) * ff, m_Scene->y());
    m_flag->setPos(6700+(m_flag->boundingRect().width() - width()) * ff * 5.5, m_flag->y());
    m_castle->setPos(7230+(m_castle->boundingRect().width() - width()) * ff * 6.9, m_castle->y());
    h_castle->setPos(7230+(h_castle->boundingRect().width() - width()) * ff * 6.9, h_castle->y());
/*
    m_cluster9->setPos(2000+(m_cluster9->boundingRect().width() - width()) * ff * 7.41, m_cluster9->y());
    m_cluster8->setPos(2050+(m_cluster8->boundingRect().width() - width()) * ff * 7.01, m_cluster8->y());
    m_cluster7->setPos(2089+(m_cluster7->boundingRect().width() - width()) * ff * 6.62, m_cluster7->y());
    m_cluster6->setPos(2134+(m_cluster6->boundingRect().width() - width()) * ff * 6.29, m_cluster6->y());
    m_cluster5->setPos(2182+(m_cluster5->boundingRect().width() - width()) * ff * 6.0, m_cluster5->y());
    m_cluster4->setPos(2228+(m_cluster4->boundingRect().width() - width()) * ff * 5.73, m_cluster4->y());
    m_cluster3->setPos(2276+(m_cluster3->boundingRect().width() - width()) * ff * 5.49, m_cluster3->y());
    m_cluster2->setPos(2322+(m_cluster2->boundingRect().width() - width()) * ff * 5.26, m_cluster2->y());
*/
    m_glowbrick->setPos(592+(m_glowbrick->boundingRect().width() - width()) * ff * 5.06, m_glowbrick->y());
    m_glowbrick2->setPos(545+(m_glowbrick2->boundingRect().width() - width()) * ff * 5.06, m_glowbrick2->y());
    m_glowbrick3->setPos(498+(m_glowbrick3->boundingRect().width() - width()) * ff * 5.06, m_glowbrick3->y());
    m_glowbrick4->setPos(451+(m_glowbrick4->boundingRect().width() - width()) * ff * 5.06, m_glowbrick4->y());
    m_glowbrick5->setPos(1000+(m_glowbrick5->boundingRect().width() - width()) * ff * 5.06, m_glowbrick5->y());
    m_glowbrick6->setPos(1000+(m_glowbrick6->boundingRect().width() - width()) * ff * 5.06, m_glowbrick6->y());
    m_glowbrick7->setPos(1047+(m_glowbrick7->boundingRect().width() - width()) * ff * 5.06, m_glowbrick7->y());
    m_glowbrick8->setPos(1094+(m_glowbrick8->boundingRect().width() - width()) * ff * 5.06, m_glowbrick8->y());
    m_glowbrick9->setPos(1141+(m_glowbrick9->boundingRect().width() - width()) * ff * 5.06, m_glowbrick9->y());
    m_glowbrick10->setPos(1188+(m_glowbrick10->boundingRect().width() - width()) * ff * 5.06, m_glowbrick10->y());
    m_glowbrick11->setPos(1188+(m_glowbrick11->boundingRect().width() - width()) * ff * 5.06, m_glowbrick11->y());
    m_glowbrick12->setPos(404+(m_glowbrick12->boundingRect().width() - width()) * ff * 5.06, m_glowbrick12->y());
    m_glowbrick13->setPos(1335+(m_glowbrick13->boundingRect().width() - width()) * ff * 5.06, m_glowbrick13->y());
    m_glowbrick14->setPos(1535+(m_glowbrick14->boundingRect().width() - width()) * ff * 5.06, m_glowbrick14->y());
    m_glowbrick15->setPos(1735+(m_glowbrick15->boundingRect().width() - width()) * ff * 5.06, m_glowbrick15->y());
    m_glowbrick16->setPos(2800+(m_glowbrick16->boundingRect().width() - width()) * ff * 5.06, m_glowbrick16->y());
    m_glowbrick17->setPos(2706+(m_glowbrick17->boundingRect().width() - width()) * ff * 5.06, m_glowbrick17->y());
    m_glowbrick18->setPos(2610+(m_glowbrick18->boundingRect().width() - width()) * ff * 5.06, m_glowbrick18->y());

    m_warpTube->setPos(800+(m_warpTube->boundingRect().width() - width()) * ff * 5.15, m_warpTube->y());
    m_warpTube2->setPos(3000+(m_warpTube->boundingRect().width() - width()) * ff * 5.15, m_warpTube->y());
    m_goomba->setPos(600+(m_goomba->boundingRect().width() - width()) * ff * 5.15, m_goomba->y());
    m_questbox->setPos(640+(m_questbox->boundingRect().width() - width()) * ff * 5.06, m_questbox->y());
    m_questbox2->setPos(2753+(m_questbox2->boundingRect().width() - width()) * ff * 5.06, m_questbox2->y());
    m_questbox3->setPos(2658+(m_questbox3->boundingRect().width() - width()) * ff * 5.06, m_questbox3->y());
    m_turtle->setPos(994+(m_turtle->boundingRect().width() - width()) * ff * 5.15, m_turtle->y());
    m_piranha->setPos(773+(m_piranha->boundingRect().width() - width()) * ff * 5.4, m_piranha->y());
    m_piranha2->setPos(2965+(m_piranha2->boundingRect().width() - width()) * ff * 5.4, m_piranha2->y());
    m_ground->setPos(-(m_ground->boundingRect().width() - width()) * ff  , m_ground->y());

}

void MyScene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running) {
        handleCollisionWithPlatform();
    }
}

void MyScene::jumpPlayer(){

    checkColliding();
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
        return;

    const qreal y = (m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;

    QGraphicsItem* platform = collidingPlatforms();
    if(!platform || platform == m_platform) {
        qDebug() << "change pos2";
        m_player->setPos(m_player->pos().x(), y);
    }


}


// All animations inside the playing field are done by moving items, not the scene.
void MyScene::initPlayField(){
    // setItemIndexMethod(NoIndex);
    //setItemIndexMethod(QGraphicsScene::NoIndex);

    setSceneRect(0,0,1280,720);

    m_groundLevel = 660;

    //add sky
    m_sky = new BackgroundItem(QPixmap(":images/sky"));
    addItem(m_sky);

    //add ground
    m_ground = new BackgroundItem(QPixmap(":images/ground"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //add scene image
    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);
/*
    m_cluster9 = new BackgroundItem(QPixmap(":images/cluster9"));
    m_cluster9->setPos(2000, m_groundLevel - m_cluster9->boundingRect().height());
    addItem(m_cluster9);

    m_cluster8 = new BackgroundItem(QPixmap(":images/cluster8"));
    m_cluster8->setPos(2050, m_groundLevel - m_cluster8->boundingRect().height()-50);
    addItem(m_cluster8);

    m_cluster7 = new BackgroundItem(QPixmap(":images/cluster7"));
    m_cluster7->setPos(2089, m_groundLevel - m_cluster7->boundingRect().height()-100);
    addItem(m_cluster7);

    m_cluster6 = new BackgroundItem(QPixmap(":images/cluster6"));
    m_cluster6->setPos(2134, m_groundLevel - m_cluster6->boundingRect().height()-150);
    addItem(m_cluster6);

    m_cluster5 = new BackgroundItem(QPixmap(":images/cluster5"));
    m_cluster5->setPos(2182, m_groundLevel - m_cluster5->boundingRect().height()-200);
    addItem(m_cluster5);

    m_cluster4 = new BackgroundItem(QPixmap(":images/cluster4"));
    m_cluster4->setPos(2228, m_groundLevel - m_cluster4->boundingRect().height()-250);
    addItem(m_cluster4);

    m_cluster3 = new BackgroundItem(QPixmap(":images/cluster3"));
    m_cluster3->setPos(2276, m_groundLevel - m_cluster3->boundingRect().height()-300);
    addItem(m_cluster3);

    m_cluster2 = new BackgroundItem(QPixmap(":images/cluster2"));
    m_cluster2->setPos(2322, m_groundLevel - m_cluster2->boundingRect().height()-350);
    addItem(m_cluster2);
*/
    //add warp tube
    m_warpTube = new BackgroundItem(QPixmap(":images/Warp.png"));
    m_warpTube->setPos(800, m_groundLevel - m_warpTube->boundingRect().height());
    addItem(m_warpTube);

    m_warpTube2 = new BackgroundItem(QPixmap(":images/Warp.png"));
    m_warpTube2->setPos(3000, m_groundLevel - m_warpTube2->boundingRect().height());
    addItem(m_warpTube2);

    //add flag
    m_flag = new BackgroundItem(QPixmap(":images/flag"));
    m_flag->setPos(6700, m_groundLevel - m_flag->boundingRect().height());
    addItem(m_flag);

    m_castle = new BackgroundItem(QPixmap(":images/castle"));
    m_castle->setPos(7230, m_groundLevel - m_castle->boundingRect().height());
    addItem(m_castle);

    m_coins = new Coin();
    m_coins->setPos(1300, m_groundLevel - m_coins->boundingRect().height()-200);
    addItem(m_coins);
    startTimer( 100 );

    m_coins2 = new Coin();
    m_coins2->setPos(1300, m_groundLevel - m_coins2->boundingRect().height()-250);
    addItem(m_coins2);    

    m_coins3 = new Coin();
    m_coins3->setPos(1300, m_groundLevel - m_coins3->boundingRect().height()-300);
    addItem(m_coins3);    

    m_coins4 = new Coin();
    m_coins4->setPos(1300, m_groundLevel - m_coins4->boundingRect().height()-350);
    addItem(m_coins4);  

    m_coins5 = new Coin();
    m_coins5->setPos(1350, m_groundLevel - m_coins5->boundingRect().height()-350);
    addItem(m_coins5);    

    m_coins6 = new Coin();
    m_coins6->setPos(1400, m_groundLevel - m_coins6->boundingRect().height()-350);
    addItem(m_coins6);  

    m_coins7 = new Coin();
    m_coins7->setPos(1400, m_groundLevel - m_coins7->boundingRect().height()-300);
    addItem(m_coins7);

    m_coins8 = new Coin();
    m_coins8->setPos(1350, m_groundLevel - m_coins8->boundingRect().height()-250);
    addItem(m_coins8);

    m_coins9 = new Coin();
    m_coins9->setPos(1400, m_groundLevel - m_coins9->boundingRect().height()-200);
    addItem(m_coins9);

    m_coins10 = new Coin();
    m_coins10->setPos(1500, m_groundLevel - m_coins10->boundingRect().height()-200);
    addItem(m_coins10);

    m_coins11 = new Coin();
    m_coins11->setPos(1500, m_groundLevel - m_coins11->boundingRect().height()-250);
    addItem(m_coins11);

    m_coins12 = new Coin();
    m_coins12->setPos(1500, m_groundLevel - m_coins12->boundingRect().height()-300);
    addItem(m_coins12);

    m_coins13 = new Coin();
    m_coins13->setPos(1500, m_groundLevel - m_coins13->boundingRect().height()-350);
    addItem(m_coins13);

    m_coins14 = new Coin();
    m_coins14->setPos(1550, m_groundLevel -  m_coins14->boundingRect().height()-350);
    addItem( m_coins14);

    m_coins15 = new Coin();
    m_coins15->setPos(1600, m_groundLevel - m_coins15->boundingRect().height()-350);
    addItem(m_coins15);

    m_coins16 = new Coin();
    m_coins16->setPos(1500, m_groundLevel - m_coins16->boundingRect().height()-200);
    addItem(m_coins16);

    m_coins17 = new Coin();
    m_coins17->setPos(1550, m_groundLevel - m_coins17->boundingRect().height()-200);
    addItem(m_coins17);

    m_coins18 = new Coin();
    m_coins18->setPos(1600, m_groundLevel - m_coins18->boundingRect().height()-200);
    addItem(m_coins18);

    m_coins19 = new Coin();
    m_coins19->setPos(1700, m_groundLevel - m_coins19->boundingRect().height()-200);
    addItem(m_coins19);

    m_coins20 = new Coin();
    m_coins20->setPos(1700, m_groundLevel - m_coins20->boundingRect().height()-250);
    addItem(m_coins20);

    m_coins21 = new Coin();
    m_coins21->setPos(1700, m_groundLevel - m_coins21->boundingRect().height()-300);
    addItem(m_coins21);

    m_coins22 = new Coin();
    m_coins22->setPos(1700, m_groundLevel - m_coins22->boundingRect().height()-350);
    addItem(m_coins22);

    m_coins23 = new Coin();
    m_coins23->setPos(1750, m_groundLevel - m_coins23->boundingRect().height()-350);
    addItem(m_coins23);

    m_coins24 = new Coin();
    m_coins24->setPos(1800, m_groundLevel - m_coins24->boundingRect().height()-350);
    addItem(m_coins24);

    m_coins25 = new Coin();
    m_coins25->setPos(1750, m_groundLevel - m_coins25->boundingRect().height()-200);
    addItem(m_coins25);

    m_coins26 = new Coin();
    m_coins26->setPos(1800, m_groundLevel - m_coins26->boundingRect().height()-200);
    addItem(m_coins26);

   //Add Goomba
    m_goomba = new Goomba();
    m_goomba->setPos(600, m_groundLevel - m_goomba->boundingRect().height()-150);
    addItem(m_goomba);

   //Add Questionbox
    m_questbox = new QuestBox();
    m_questbox->setPos(640, m_groundLevel - m_questbox->boundingRect().height()-100);
    addItem(m_questbox);

    m_questbox2 = new QuestBox();
    m_questbox2->setPos(2753, m_groundLevel - m_questbox2->boundingRect().height()-100);
    addItem(m_questbox2);

    m_questbox3 = new QuestBox();
    m_questbox3->setPos(2658, m_groundLevel - m_questbox3->boundingRect().height()-100);
    addItem(m_questbox3);

    m_glowbrick = new GlowBrick();
    m_glowbrick->setPos(592, m_groundLevel - m_glowbrick->boundingRect().height()-100);
    addItem(m_glowbrick);

    m_glowbrick2 = new GlowBrick();
    m_glowbrick2->setPos(545, m_groundLevel - m_glowbrick2->boundingRect().height()-100);
    addItem(m_glowbrick2);

    m_glowbrick3 = new GlowBrick();
    m_glowbrick3->setPos(498, m_groundLevel - m_glowbrick3->boundingRect().height()-100);
    addItem(m_glowbrick3);

    m_glowbrick4 = new GlowBrick();
    m_glowbrick4->setPos(451, m_groundLevel - m_glowbrick4->boundingRect().height()-100);
    addItem(m_glowbrick4);

    m_glowbrick5 = new GlowBrick();
    m_glowbrick5->setPos(1000, m_groundLevel - m_glowbrick5->boundingRect().height()-150);
    addItem(m_glowbrick5);

    m_glowbrick6 = new GlowBrick();
    m_glowbrick6->setPos(1000, m_groundLevel - m_glowbrick6->boundingRect().height()-100);
    addItem(m_glowbrick6);

    m_glowbrick7 = new GlowBrick();
    m_glowbrick7->setPos(1047, m_groundLevel - m_glowbrick7->boundingRect().height()-100);
    addItem(m_glowbrick7);

    m_glowbrick8 = new GlowBrick();
    m_glowbrick8->setPos(1094, m_groundLevel - m_glowbrick8->boundingRect().height()-100);
    addItem(m_glowbrick8);

    m_glowbrick9 = new GlowBrick();
    m_glowbrick9->setPos(1141, m_groundLevel - m_glowbrick9->boundingRect().height()-100);
    addItem(m_glowbrick9);

    m_glowbrick10 = new GlowBrick();
    m_glowbrick10->setPos(1188, m_groundLevel - m_glowbrick10->boundingRect().height()-100);
    addItem(m_glowbrick10);

    m_glowbrick11 = new GlowBrick();
    m_glowbrick11->setPos(1188, m_groundLevel - m_glowbrick11->boundingRect().height()-150);
    addItem(m_glowbrick11);

    m_glowbrick12 = new GlowBrick();
    m_glowbrick12->setPos(404, m_groundLevel - m_glowbrick12->boundingRect().height()-100);
    addItem(m_glowbrick12);

    m_glowbrick13 = new GlowBrick();
    m_glowbrick13->setPos(1335, m_groundLevel - m_glowbrick13->boundingRect().height()-150);
    addItem(m_glowbrick13);

    m_glowbrick14 = new GlowBrick();
    m_glowbrick14->setPos(1535, m_groundLevel - m_glowbrick14->boundingRect().height()-150);
    addItem(m_glowbrick14);

    m_glowbrick15 = new GlowBrick();
    m_glowbrick15->setPos(1735, m_groundLevel - m_glowbrick15->boundingRect().height()-150);
    addItem(m_glowbrick15);

    m_glowbrick16 = new GlowBrick();
    m_glowbrick16->setPos(2800, m_groundLevel - m_glowbrick16->boundingRect().height()-100);
    addItem(m_glowbrick16);

    m_glowbrick17 = new GlowBrick();
    m_glowbrick17->setPos(2706, m_groundLevel - m_glowbrick17->boundingRect().height()-100);
    addItem(m_glowbrick17);

    m_glowbrick18 = new GlowBrick();
    m_glowbrick18->setPos(2610, m_groundLevel - m_glowbrick18->boundingRect().height()-100);
    addItem(m_glowbrick18);

    m_turtle = new Turtle();
    m_turtle->setPos(994, m_groundLevel - m_turtle->boundingRect().height()-200);
    addItem(m_turtle);

    m_piranha = new Piranha();
    m_piranha->setPos(773, m_groundLevel - m_piranha->boundingRect().height()-95);
    addItem(m_piranha);

    m_piranha2 = new Piranha();
    m_piranha2->setPos(2965, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha2);

    //add player
    m_player = new Player();
    m_minX = m_player->boundingRect().width()/2 ;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 1.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() );
    m_realPos = m_minX;
    addItem(m_player);

    //int xrang = (m_maxX - m_minX) * 0.94;
    h_castle = new Castle();
    h_castle->setPos(7230, m_groundLevel - h_castle->boundingRect().height());
    addItem(h_castle);
}

//TIMER EVENT ADDED FOR ANIMATIONS
void MyScene::timerEvent(QTimerEvent *){

    m_coins->nextFrame2();
    m_coins2->nextFrame2();
    m_coins3->nextFrame2();
    m_coins4->nextFrame2();
    m_coins5->nextFrame2();
    m_coins6->nextFrame2();
    m_coins7->nextFrame2();
    m_coins8->nextFrame2();
    m_coins9->nextFrame2();
    m_coins10->nextFrame2();
    m_coins11->nextFrame2();
    m_coins12->nextFrame2();
    m_coins13->nextFrame2();
    m_coins14->nextFrame2();
    m_coins15->nextFrame2();
    m_coins16->nextFrame2();
    m_coins17->nextFrame2();
    m_coins18->nextFrame2();
    m_coins19->nextFrame2();
    m_coins20->nextFrame2();
    m_coins21->nextFrame2();
    m_coins22->nextFrame2();
    m_coins23->nextFrame2();
    m_coins24->nextFrame2();
    m_coins25->nextFrame2();
    m_coins26->nextFrame2();

    m_goomba->nextFrame3();
    m_questbox->nextFrame4();
    m_questbox2->nextFrame4();
    m_questbox3->nextFrame4();

    m_glowbrick->nextFrame5();
    m_glowbrick2->nextFrame5();
    m_glowbrick3->nextFrame5();
    m_glowbrick4->nextFrame5();
    m_glowbrick5->nextFrame5();
    m_glowbrick6->nextFrame5();
    m_glowbrick7->nextFrame5();
    m_glowbrick8->nextFrame5();
    m_glowbrick9->nextFrame5();
    m_glowbrick10->nextFrame5();
    m_glowbrick11->nextFrame5();
    m_glowbrick12->nextFrame5();
    m_glowbrick13->nextFrame5();
    m_glowbrick14->nextFrame5();
    m_glowbrick15->nextFrame5();
    m_glowbrick16->nextFrame5();
    m_glowbrick17->nextFrame5();
    m_glowbrick18->nextFrame5();

    m_turtle->nextFrame6();
    m_piranha->nextFrame7();
    m_piranha2->nextFrame7();
}


qreal MyScene::jumpFactor() const{
    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor){
    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}

void MyScene::checkTimer(){


    if (0 == m_player->direction())//If player is not moving, stop the timer
        m_timer.stop();

    else if (!m_timer.isActive()) // check if timer is already active, it will only start if not already active.
        m_timer.start();
}


//-------------------------------------------------------------COLLISION DETECTION-----------------------------------------------//

QGraphicsItem* MyScene::collidingPlatforms() {
    QList<QGraphicsItem*> items =  collidingItems(m_player);
    foreach(QGraphicsItem *item, items) {
        if(GlowBrick *glowbrick = qgraphicsitem_cast<GlowBrick *>(item)) {
            return glowbrick;
        }
    }
    return 0;
}

void MyScene::handleCollisionWithPlatform() {
    QGraphicsItem* platform =  collidingPlatforms();
    if(platform) {
        QPointF glowbrickPos = platform->pos();
        QPointF pos = m_player->pos();
        if (pos.y() >= glowbrickPos.y()  + platform->boundingRect().height()) {            
            qDebug() << "change pos3";
            m_player->setPos(m_player->pos().x(), glowbrickPos.y() - m_player->boundingRect().height());
            m_platform = platform;
            qDebug() << "Walking on brick";
        }
    } else {
        m_platform = 0;
    }
}

void MyScene::checkColliding() {

    QList<QGraphicsItem*> items = collidingItems(m_player);
    foreach (QGraphicsItem* item, items) {

        Coin* c = qgraphicsitem_cast<Coin*>(item);
        if(c){
            removeItem(c);

            if (coinSound->state() == QMediaPlayer::PlayingState){
                coinSound->setPosition(0);
            }
            else if (coinSound->state() == QMediaPlayer::StoppedState){
                coinSound->play();
            }
        }
    }
}









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
#include "coincounter.h"
#include "warptube.h"
#include "flag.h"

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
  , m_player(0)
  , m_sky(0)
  , m_Scene(0)
  , m_coins(0)
  , h_castle(0)
  , m_goomba(0)
  , m_questbox(0)
  , m_glowbrick(0)
  , m_turtle(0)
  , m_piranha(0)
  , m_platform(0)
  , m_count(0)

{
    initPlayField();

   //Timer emits a timeout signal every 20 milliseconds
   //Then we connect that signal to the scene's slot called movePlayer()
   //Pressing the arrow keys starts the timer

    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    //Add sound for jump
    jumpSound = new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/audio/jump.mp3"));

    //Add sound for coin collection
    coinSound = new QMediaPlayer();
    coinSound->setMedia(QUrl("qrc:/audio/coin.mp3"));

    //Jump animation
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

    const int rightBorder = 670 - m_player->boundingRect().width(); //How far the character can move before view moves
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
    Move the background and items
    ff is the minimum shift (0 * shift, which equals 0) and the maximum shift (1 * shift, which equals shift).
    The calculation reads: If we subtract the width of the view (width()) from the virtual field's width m_fieldWidth, we have the area
    where the player isn't moved by (m_player->moveBy()) because in that range only thebackground should move.
    How often the moving of the player was skipped is saved in m_skippedMoving. So by
    dividing m_skippedMoving through m_fieldWidth – width(), we get the needed factor.
    */

    qreal ff = qMin(1.0, m_skippedMoving/(m_fieldWidth - width()));

    //sky speed and position
    m_sky->setPos(-(m_sky->boundingRect().width() - width()) * ff, 0);

    //RCC Coins speed and position
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

    //First rock structure coins speed and position
    m_coins27->setPos(2970+(m_coins27->boundingRect().width() - width()) * ff * 5.06, m_coins27->y());
    m_coins28->setPos(3020+(m_coins28->boundingRect().width() - width()) * ff * 5.06, m_coins28->y());
    m_coins29->setPos(3070+(m_coins29->boundingRect().width() - width()) * ff * 5.06, m_coins29->y());
    m_coins30->setPos(3120+(m_coins30->boundingRect().width() - width()) * ff * 5.06, m_coins30->y());
    m_coins31->setPos(3810+(m_coins31->boundingRect().width() - width()) * ff * 5.06, m_coins31->y());

   //Third rock structure coins speed and position
    m_coins32->setPos(3310+(m_coins32->boundingRect().width() - width()) * ff * 5.06, m_coins32->y());
    m_coins33->setPos(3360+(m_coins33->boundingRect().width() - width()) * ff * 5.06, m_coins33->y());
    m_coins34->setPos(3410+(m_coins34->boundingRect().width() - width()) * ff * 5.06, m_coins34->y());
    m_coins35->setPos(3460+(m_coins35->boundingRect().width() - width()) * ff * 5.06, m_coins35->y());
    m_coins36->setPos(3510+(m_coins36->boundingRect().width() - width()) * ff * 5.06, m_coins36->y());
    m_coins37->setPos(3560+(m_coins37->boundingRect().width() - width()) * ff * 5.06, m_coins37->y());
    m_coins38->setPos(3610+(m_coins38->boundingRect().width() - width()) * ff * 5.06, m_coins38->y());
    m_coins39->setPos(3660+(m_coins39->boundingRect().width() - width()) * ff * 5.06, m_coins39->y());
    m_coins40->setPos(3710+(m_coins40->boundingRect().width() - width()) * ff * 5.06, m_coins40->y());
    m_coins41->setPos(3760+(m_coins41->boundingRect().width() - width()) * ff * 5.06, m_coins41->y());
    m_coins42->setPos(3810+(m_coins42->boundingRect().width() - width()) * ff * 5.06, m_coins42->y());
    m_coins43->setPos(3860+(m_coins43->boundingRect().width() - width()) * ff * 5.06, m_coins43->y());
    m_coins44->setPos(3910+(m_coins44->boundingRect().width() - width()) * ff * 5.06, m_coins44->y());
    m_coins45->setPos(3960+(m_coins45->boundingRect().width() - width()) * ff * 5.06, m_coins45->y());
    m_coins46->setPos(4010+(m_coins46->boundingRect().width() - width()) * ff * 5.06, m_coins46->y());
    m_coins47->setPos(4060+(m_coins47->boundingRect().width() - width()) * ff * 5.06, m_coins47->y());

    //Background scene speed and position
    m_Scene->setPos(-(m_Scene->boundingRect().width() - width()) * ff, m_Scene->y());

    //Flag pole speed and position
    m_flag->setPos(6700+(m_flag->boundingRect().width() - width()) * ff * 5.5, m_flag->y());

    //Castle speed and position and half castle so it can look like mario goes inside castle
    m_castle->setPos(7230+(m_castle->boundingRect().width() - width()) * ff * 6.9, m_castle->y());
    h_castle->setPos(7230+(h_castle->boundingRect().width() - width()) * ff * 6.9, h_castle->y());

    //Stair structure before flag speed and position
    m_cluster9->setPos(6125+(m_cluster9->boundingRect().width() - width()) * ff * 7.41, m_cluster9->y());
    m_cluster8->setPos(6178+(m_cluster8->boundingRect().width() - width()) * ff * 7.01, m_cluster8->y());
    m_cluster7->setPos(6206+(m_cluster7->boundingRect().width() - width()) * ff * 6.63, m_cluster7->y());
    m_cluster6->setPos(6237+(m_cluster6->boundingRect().width() - width()) * ff * 6.29, m_cluster6->y());
    m_cluster5->setPos(6285+(m_cluster5->boundingRect().width() - width()) * ff * 6.0, m_cluster5->y());
    m_cluster4->setPos(6327+(m_cluster4->boundingRect().width() - width()) * ff * 5.73, m_cluster4->y());
    m_cluster3->setPos(6377+(m_cluster3->boundingRect().width() - width()) * ff * 5.49, m_cluster3->y());
    m_cluster2->setPos(6417+(m_cluster2->boundingRect().width() - width()) * ff * 5.26, m_cluster2->y());

    //Bricks speed and position
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
    m_glowbrick19->setPos(2890+(m_glowbrick19->boundingRect().width() - width()) * ff * 5.06, m_glowbrick19->y());
    m_glowbrick20->setPos(700+(m_glowbrick20->boundingRect().width() - width()) * ff * 5.06, m_glowbrick20->y());

    //Rock wall structures speed and position
    m_wall2->setPos(3100+(m_wall2->boundingRect().width() - width()) * ff * 6.9, m_wall2->y());
    m_wall->setPos(2900+(m_wall->boundingRect().width() - width()) * ff * 6.44, m_wall->y());
    m_wall3->setPos(3300+(m_wall3->boundingRect().width() - width()) * ff * 13.10, m_wall3->y());

    //Warp tube speed and position
    m_warpTube->setPos(800+(m_warpTube->boundingRect().width() - width()) * ff * 5.15, m_warpTube->y());
    m_warpTube2->setPos(3000+(m_warpTube2->boundingRect().width() - width()) * ff * 5.15, m_warpTube2->y());

    //Arrow sign speed and position
    m_sign->setPos(150+(m_sign->boundingRect().width() - width()) * ff * 5.2, m_sign->y());

    //Goomba speed and position
    m_goomba->setPos(600+(m_goomba->boundingRect().width() - width()) * ff * 5.15, m_goomba->y());
    m_goomba2->setPos(3300+(m_goomba2->boundingRect().width() - width()) * ff * 5.15, m_goomba2->y());

    //Question box speed and position
    m_questbox->setPos(640+(m_questbox->boundingRect().width() - width()) * ff * 5.06, m_questbox->y());
    m_questbox2->setPos(2753+(m_questbox2->boundingRect().width() - width()) * ff * 5.06, m_questbox2->y());
    m_questbox3->setPos(2658+(m_questbox3->boundingRect().width() - width()) * ff * 5.06, m_questbox3->y());
    m_questbox4->setPos(3350+(m_questbox4->boundingRect().width() - width()) * ff * 5.06, m_questbox4->y());
    m_questbox5->setPos(3750+(m_questbox5->boundingRect().width() - width()) * ff * 5.06, m_questbox5->y());

    //Turtle speed and position
    m_turtle->setPos(994+(m_turtle->boundingRect().width() - width()) * ff * 5.15, m_turtle->y());
    m_turtle2->setPos(2550+(m_turtle2->boundingRect().width() - width()) * ff * 5.15, m_turtle2->y());

    //Piranha plant speed and position
    m_piranha->setPos(773+(m_piranha->boundingRect().width() - width()) * ff * 5.4, m_piranha->y());
    m_piranha2->setPos(2965+(m_piranha2->boundingRect().width() - width()) * ff * 5.4, m_piranha2->y());

    //Animated flag speed and position
    m_flag2->setPos(6786+(m_flag2->boundingRect().width() - width()) * ff * 5.35, m_flag2->y());

    //Ground speed and position
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

    //Set the scene size
    setSceneRect(0,0,1280,720);

    //Specify the ground level
    m_groundLevel = 660;

    //add sky
    m_sky = new BackgroundItem(QPixmap(":images/sky"));
    addItem(m_sky);

    //Add ground
    m_ground = new BackgroundItem(QPixmap(":images/ground"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //Add scene image
    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

    //Add Coin image for the counter
    m_countLogo = new BackgroundItem(QPixmap(":images/count"));
    m_countLogo->setPos(30, m_groundLevel -640 );
    addItem(m_countLogo);

    //Add Stair structure before flag
    m_cluster9 = new BackgroundItem(QPixmap(":images/cluster9"));
    m_cluster9->setPos(6125, m_groundLevel - m_cluster9->boundingRect().height());
    addItem(m_cluster9);

    m_cluster8 = new BackgroundItem(QPixmap(":images/cluster8"));
    m_cluster8->setPos(6175, m_groundLevel - m_cluster8->boundingRect().height()-50);
    addItem(m_cluster8);

    m_cluster7 = new BackgroundItem(QPixmap(":images/cluster7"));
    m_cluster7->setPos(6206, m_groundLevel - m_cluster7->boundingRect().height()-100);
    addItem(m_cluster7);

    m_cluster6 = new BackgroundItem(QPixmap(":images/cluster6"));
    m_cluster6->setPos(6237, m_groundLevel - m_cluster6->boundingRect().height()-150);
    addItem(m_cluster6);

    m_cluster5 = new BackgroundItem(QPixmap(":images/cluster5"));
    m_cluster5->setPos(6285, m_groundLevel - m_cluster5->boundingRect().height()-200);
    addItem(m_cluster5);

    m_cluster4 = new BackgroundItem(QPixmap(":images/cluster4"));
    m_cluster4->setPos(6327, m_groundLevel - m_cluster4->boundingRect().height()-250);
    addItem(m_cluster4);

    m_cluster3 = new BackgroundItem(QPixmap(":images/cluster3"));
    m_cluster3->setPos(6377, m_groundLevel - m_cluster3->boundingRect().height()-300);
    addItem(m_cluster3);

    m_cluster2 = new BackgroundItem(QPixmap(":images/cluster2"));
    m_cluster2->setPos(6417, m_groundLevel - m_cluster2->boundingRect().height()-350);
    addItem(m_cluster2);

    //Add wall structures
    m_wall2 = new BackgroundItem(QPixmap(":images/wallg.png"));
    m_wall2->setPos(3100, m_groundLevel - m_wall2->boundingRect().height());
    addItem(m_wall2);

    m_wall = new BackgroundItem(QPixmap(":images/wallf2.png"));
    m_wall->setPos(2900, m_groundLevel - m_wall->boundingRect().height());
    addItem(m_wall);

    m_wall3 = new BackgroundItem(QPixmap(":images/walli.png"));
    m_wall3->setPos(3350, m_groundLevel - m_wall3->boundingRect().height());
    addItem(m_wall3);

    //Add warp tube
    m_warpTube = new WarpTube();
    m_warpTube->setPos(800, m_groundLevel - m_warpTube->boundingRect().height());
    addItem(m_warpTube);

    m_warpTube2 = new WarpTube();
    m_warpTube2->setPos(3000, m_groundLevel - m_warpTube2->boundingRect().height());
    addItem(m_warpTube2);

    //Add Sign
    m_sign = new BackgroundItem(QPixmap(":images/sign.png"));
    m_sign->setPos(150, m_groundLevel - m_sign->boundingRect().height());
    addItem(m_sign);

    //Add flag
    m_flag = new BackgroundItem(QPixmap(":images/flag"));
    m_flag->setPos(6700, m_groundLevel - m_flag->boundingRect().height());
    addItem(m_flag);

    //Add castle
    m_castle = new BackgroundItem(QPixmap(":images/castle"));
    m_castle->setPos(7230, m_groundLevel - m_castle->boundingRect().height());
    addItem(m_castle);

    //Add coins
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

    m_coins27 = new Coin();
    m_coins27->setPos(2970, m_groundLevel - m_coins27->boundingRect().height()-290);
    addItem(m_coins27);

    m_coins28 = new Coin();
    m_coins28->setPos(3020, m_groundLevel - m_coins28->boundingRect().height()-290);
    addItem(m_coins28);

    m_coins29 = new Coin();
    m_coins29->setPos(3070, m_groundLevel - m_coins29->boundingRect().height()-290);
    addItem(m_coins29);

    m_coins30 = new Coin();
    m_coins30->setPos(3120, m_groundLevel - m_coins30->boundingRect().height()-290);
    addItem(m_coins30);

    m_coins31 = new Coin();
    m_coins31->setPos(3810, m_groundLevel - m_coins31->boundingRect().height()-150);
    addItem(m_coins31);

    m_coins32 = new Coin();
    m_coins32->setPos(3310, m_groundLevel - m_coins32->boundingRect().height()-150);
    addItem(m_coins32);

    m_coins33 = new Coin();
    m_coins33->setPos(3360, m_groundLevel - m_coins33->boundingRect().height()-150);
    addItem(m_coins33);

    m_coins34 = new Coin();
    m_coins34->setPos(3410, m_groundLevel - m_coins34->boundingRect().height()-150);
    addItem(m_coins34);

    m_coins35 = new Coin();
    m_coins35->setPos(3460, m_groundLevel - m_coins35->boundingRect().height()-150);
    addItem(m_coins35);

    m_coins36 = new Coin();
    m_coins36->setPos(3510, m_groundLevel - m_coins36->boundingRect().height()-150);
    addItem(m_coins36);

    m_coins37 = new Coin();
    m_coins37->setPos(3560, m_groundLevel - m_coins37->boundingRect().height()-150);
    addItem(m_coins37);

    m_coins38 = new Coin();
    m_coins38->setPos(3610, m_groundLevel - m_coins38->boundingRect().height()-150);
    addItem(m_coins38);

    m_coins39 = new Coin();
    m_coins39->setPos(3660, m_groundLevel - m_coins39->boundingRect().height()-150);
    addItem(m_coins39);

    m_coins40 = new Coin();
    m_coins40->setPos(3710, m_groundLevel - m_coins40->boundingRect().height()-150);
    addItem(m_coins40);

    m_coins41 = new Coin();
    m_coins41->setPos(3760, m_groundLevel - m_coins41->boundingRect().height()-150);
    addItem(m_coins41);

    m_coins42 = new Coin();
    m_coins42->setPos(3810, m_groundLevel - m_coins42->boundingRect().height()-150);
    addItem(m_coins42);

    m_coins43 = new Coin();
    m_coins43->setPos(3860, m_groundLevel - m_coins43->boundingRect().height()-150);
    addItem(m_coins43);

    m_coins44 = new Coin();
    m_coins44->setPos(3910, m_groundLevel - m_coins44->boundingRect().height()-150);
    addItem(m_coins44);

    m_coins45 = new Coin();
    m_coins45->setPos(3960, m_groundLevel - m_coins45->boundingRect().height()-150);
    addItem(m_coins45);

    m_coins46 = new Coin();
    m_coins46->setPos(4010, m_groundLevel - m_coins46->boundingRect().height()-150);
    addItem(m_coins46);

    m_coins47 = new Coin();
    m_coins47->setPos(4060, m_groundLevel - m_coins47->boundingRect().height()-150);
    addItem(m_coins47);

   //Add Goomba
    m_goomba = new Goomba();
    m_goomba->setPos(600, m_groundLevel - m_goomba->boundingRect().height()-150);
    addItem(m_goomba);

    m_goomba2 = new Goomba();
    m_goomba2->setPos(3300, m_groundLevel - m_goomba2->boundingRect().height()-350);
    addItem(m_goomba2);

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

    m_questbox4 = new QuestBox();
    m_questbox4->setPos(3550, m_groundLevel - m_questbox4->boundingRect().height()-450);
    addItem(m_questbox4);

    m_questbox5 = new QuestBox();
    m_questbox5->setPos(3750, m_groundLevel - m_questbox5->boundingRect().height()-250);
    addItem(m_questbox5);

    //Add bricks
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

    m_glowbrick19 = new GlowBrick();
    m_glowbrick19->setPos(2890, m_groundLevel - m_glowbrick19->boundingRect().height()-150);
    addItem(m_glowbrick19);

    m_glowbrick20 = new GlowBrick();
    m_glowbrick20->setPos(700, m_groundLevel - m_glowbrick20->boundingRect().height()-200);
    addItem(m_glowbrick20);

    //Add turtle
    m_turtle = new Turtle();
    m_turtle->setPos(994, m_groundLevel - m_turtle->boundingRect().height()-200);
    addItem(m_turtle);

    m_turtle2 = new Turtle();
    m_turtle2->setPos(2550, m_groundLevel - m_turtle2->boundingRect().height());
    addItem(m_turtle2);

    //Add piranha plant
    m_piranha = new Piranha();
    m_piranha->setPos(773, m_groundLevel - m_piranha->boundingRect().height()-95);
    addItem(m_piranha);

    m_piranha2 = new Piranha();
    m_piranha2->setPos(2965, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha2);

    //Add Coin COunter
    m_count = new CoinCounter();
    m_count->setPos(65, m_groundLevel - m_count->boundingRect().height()-590);
    addItem(m_count);

    //Add Flag Animation
    m_flag2 = new Flag();
    m_flag2->setPos(6786, m_groundLevel - m_flag2->boundingRect().height()-285);
    addItem(m_flag2);

    //Add player
    m_player = new Player();
    m_minX = m_player->boundingRect().width()/2 ;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 1.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() );
    m_realPos = m_minX;
    addItem(m_player);

    //Add half castle placed here specifically so mario will disappear when walking in castle
    h_castle = new Castle();
    h_castle->setPos(7230, m_groundLevel - h_castle->boundingRect().height());
    addItem(h_castle);
}

//Timer event for animations
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
    m_coins27->nextFrame2();
    m_coins28->nextFrame2();
    m_coins29->nextFrame2();
    m_coins30->nextFrame2();
    m_coins31->nextFrame2();

    m_coins32->nextFrame2();
    m_coins33->nextFrame2();
    m_coins34->nextFrame2();
    m_coins35->nextFrame2();
    m_coins36->nextFrame2();

    m_coins37->nextFrame2();
    m_coins38->nextFrame2();
    m_coins39->nextFrame2();
    m_coins40->nextFrame2();
    m_coins41->nextFrame2();
    m_coins42->nextFrame2();
    m_coins43->nextFrame2();
    m_coins44->nextFrame2();
    m_coins45->nextFrame2();
    m_coins46->nextFrame2();
    m_coins47->nextFrame2();

    m_goomba->nextFrame3();
    m_goomba2->nextFrame3();

    m_questbox->nextFrame4();
    m_questbox2->nextFrame4();
    m_questbox3->nextFrame4();
    m_questbox4->nextFrame4();
    m_questbox5->nextFrame4();

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
    m_glowbrick19->nextFrame5();
    m_glowbrick20->nextFrame5();

    m_turtle->nextFrame6();
    m_turtle2->nextFrame6();

    m_piranha->nextFrame7();
    m_piranha2->nextFrame7();

    m_flag2->nextFrame8();
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
            m_count->increase();
            if (coinSound->state() == QMediaPlayer::PlayingState){
                coinSound->setPosition(0);
            }
            else if (coinSound->state() == QMediaPlayer::StoppedState){
                coinSound->play();
            }
        }
    }
}









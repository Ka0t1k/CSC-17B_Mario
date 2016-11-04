#include "myscene.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "coin.h"
#include "backgrounditem.h"


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
{
    initPlayField();

    //timer emits a timeout signal every 20 milliseconds
    //Then we connect that signal to the scene's slot called movePlayer()
    //Pressing the arrow keys starts the timer
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    jumpSound = new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/audio/jump.mp3"));

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &MyScene::jumpFactorChanged, this, &MyScene::jumpPlayer);

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
    m_player->nextFrame();

    int direction = m_player->direction();     //Cache the player's current direction in a local variable to avoid multiple calls of direction()
    if (0 == direction)                       //check whether the player is moving at all. If they aren't, we exit the function
        return;


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
    const int leftBorder = 970;

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
    m_Scene->setPos(-(m_Scene->boundingRect().width() - width()) * ff, m_Scene->y());
    m_flag->setPos(6500+(m_flag->boundingRect().width() - width()) * ff * 5, m_flag->y());
    m_brick->setPos(400+(m_brick->boundingRect().width() - width()) * ff * 6, m_brick->y());
    m_brick2->setPos(1000+(m_brick2->boundingRect().width() - width()) * ff * 6, m_brick2->y());
    m_oneBrick->setPos(1000+(m_oneBrick->boundingRect().width() - width()) * ff * 5.06, m_oneBrick->y());
    m_oneBrick2->setPos(1192+(m_oneBrick2->boundingRect().width() - width()) * ff * 5.06, m_oneBrick2->y());
    m_qbox->setPos(640+(m_qbox->boundingRect().width() - width()) * ff * 5.06, m_qbox->y());
    m_warpTube->setPos(800+(m_warpTube->boundingRect().width() - width()) * ff * 5, m_warpTube->y());
    m_ground->setPos(-(m_ground->boundingRect().width() - width()) * ff, m_ground->y());

   // checkColliding();
}

void MyScene::jumpPlayer(){

    if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
        return;

    const qreal y = (m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    m_player->setPos(m_player->pos().x(), y);

    //checkColliding();
}

// All animations inside the playing field are done by moving items, not the scene.
void MyScene::initPlayField(){

    setSceneRect(0,0,1280,720);
    m_groundLevel = 660;

    //add sky
    m_sky = new BackgroundItem(QPixmap(":images/sky"));
    addItem(m_sky);

    //add ground
    m_ground = new BackgroundItem(QPixmap(":images/ground"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //add scene
    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

    //add brick
    m_brick = new BackgroundItem(QPixmap(":images/brick_cluster2"));
    m_brick->setPos(400, m_groundLevel - m_brick->boundingRect().height()-100);
    addItem(m_brick);

    m_brick2 = new BackgroundItem(QPixmap(":images/brick_cluster2"));
    m_brick2->setPos(1000, m_groundLevel - m_brick2->boundingRect().height()-100);
    addItem(m_brick2);

    m_oneBrick = new BackgroundItem(QPixmap(":images/single_block"));
    m_oneBrick->setPos(1000, m_groundLevel - m_oneBrick->boundingRect().height()-150);
    addItem(m_oneBrick);

    m_oneBrick2 = new BackgroundItem(QPixmap(":images/single_block"));
    m_oneBrick2->setPos(1192, m_groundLevel - m_oneBrick2->boundingRect().height()-150);
    addItem(m_oneBrick2);

    //add qestion box
    m_qbox = new BackgroundItem(QPixmap(":images/qbox"));
    m_qbox->setPos(640, m_groundLevel - m_qbox->boundingRect().height()-100);
    addItem(m_qbox);

    //add warp tube
    m_warpTube = new BackgroundItem(QPixmap(":images/Warp.png"));
    m_warpTube->setPos(800, m_groundLevel - m_warpTube->boundingRect().height());
    addItem(m_warpTube);

    //add flag
    m_flag = new BackgroundItem(QPixmap(":images/flag"));
    m_flag->setPos(6500, m_groundLevel - m_flag->boundingRect().height());
    addItem(m_flag);

    m_coins = new Coin();
    m_coins->setPos(1300, m_groundLevel - m_coins->boundingRect().height()-200);
    addItem(m_coins);
    startTimer( 100 );

    m_coins2 = new Coin();
    m_coins2->setPos(1300, m_groundLevel - m_coins2->boundingRect().height()-250);
    addItem(m_coins2);
    //startTimer( 100 );

    m_coins3 = new Coin();
    m_coins3->setPos(1300, m_groundLevel - m_coins3->boundingRect().height()-300);
    addItem(m_coins3);
    //startTimer( 100 );

    m_coins4 = new Coin();
    m_coins4->setPos(1300, m_groundLevel - m_coins4->boundingRect().height()-350);
    addItem(m_coins4);
    //startTimer( 100 );

    m_coins5 = new Coin();
    m_coins5->setPos(1350, m_groundLevel - m_coins5->boundingRect().height()-350);
    addItem(m_coins5);
    //startTimer( 100 );

    m_coins6 = new Coin();
    m_coins6->setPos(1400, m_groundLevel - m_coins6->boundingRect().height()-350);
    addItem(m_coins6);
    //startTimer( 100 );

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

    //add player
    m_player = new Player();
    m_minX = m_player->boundingRect().width()/2 ;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 1.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() );
    m_realPos = m_minX;
    addItem(m_player);
/*
    Coin *C = new Coin();
    C->setPos(1000, m_groundLevel - C->boundingRect().height()-200);
    addItem(C);
    m_coins.append(C);
    startTimer( 100 );

    Coin *A = new Coin();
    A->setPos(1050, m_groundLevel - A->boundingRect().height()-200);
    addItem(A);
    m_coins.append(A);
    startTimer( 100 );
*/
/*
      //ADD COINS
      int xrange = (m_maxX - m_minX) * 0.94;
      int hrange = m_jumpHeight;

      for (int i = 0; i < 55; ++i) {
        Coin *C = new Coin();
        C->setPos(m_minX + qrand()%xrange, qrand()%hrange+400);
        addItem(C);
        m_coins.append(C);
      }

      startTimer( 100 );
      */
}

//TIMER EVENT ADDED FOR COINS
void MyScene::timerEvent(QTimerEvent *){

    m_coins-> nextFrame2();
    m_coins2-> nextFrame2();
    m_coins3-> nextFrame2();
    m_coins4-> nextFrame2();
    m_coins5-> nextFrame2();
    m_coins6-> nextFrame2();
    m_coins7-> nextFrame2();
    m_coins8-> nextFrame2();
    m_coins9-> nextFrame2();
    m_coins10-> nextFrame2();
    m_coins11-> nextFrame2();
    m_coins12-> nextFrame2();
    m_coins13-> nextFrame2();
    m_coins14-> nextFrame2();
    m_coins15-> nextFrame2();
    m_coins16-> nextFrame2();
    m_coins17-> nextFrame2();
    m_coins18-> nextFrame2();
    m_coins19-> nextFrame2();
    m_coins20-> nextFrame2();
    m_coins21-> nextFrame2();
    m_coins22-> nextFrame2();
    m_coins23-> nextFrame2();
    m_coins24-> nextFrame2();
    m_coins25-> nextFrame2();
    m_coins26-> nextFrame2();

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

    //If player is not moving, stop the timer
    if (0 == m_player->direction())
        m_timer.stop();
    // check if timer is already active, it will only start if not already active.
    else if (!m_timer.isActive())
        m_timer.start();
}



/*
void MyScene::checkColliding()
{
    QList<QGraphicsItem*> items =  collidingItems(m_player);
   for (int i = 0, total = items.count(); i < total; ++i) {
        if (Coin *c = qgraphicsitem_cast<Coin*>(items.at(i)))
           c->explode();
    }

}

*/

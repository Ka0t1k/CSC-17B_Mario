#include "myscene.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QPen>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "coin.h"
#include "backgrounditem.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
  , m_velocity(4)
  , m_skippedMoving(0)
  , m_groundLevel(0)
  , m_minX(0)
  , m_maxX(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(180)
  , m_fieldWidth(5500)
  , m_player(0)
  , m_sky(0)
  , m_Scene(0)
  , m_grass(0)
  , m_coins(0)
  ,m_item(0)


{
    initPlayField();
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    jumpSound = new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/music/jump.mp3"));

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
    if (event->isAutoRepeat())
        return;

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
    int direction = m_player->direction();
    if (0 == direction)
        return;

    const int dx = direction * m_velocity;
    qreal newPos = m_realPos + dx;
    if (newPos < m_minX)
        newPos = m_minX;
    else if (newPos > m_maxX)
        newPos = m_maxX;
    if (newPos == m_realPos)
        return;
    m_realPos = newPos;

    const int rightBorder = 350 - m_player->boundingRect().width();
    const int leftBorder = 150;

    if (direction > 0) {

        if (m_realPos > m_fieldWidth - (width() - rightBorder)) {
            m_player->moveBy(dx, 0);
        } else {
            if (m_realPos - m_skippedMoving < rightBorder) {
                m_player->moveBy(dx, 0);
            } else {
                m_skippedMoving += dx;
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


    qreal ff = qMin(1.0, m_skippedMoving/(m_fieldWidth - width()));
    m_sky->setPos(-(m_sky->boundingRect().width() - width()) * ff, 0);
    m_grass->setPos(-(m_grass->boundingRect().width() - width()) * ff, m_grass->y());
    m_Scene->setPos(-(m_Scene->boundingRect().width() - width()) * ff, m_Scene->y());
    m_coins->setPos(-(m_coins->boundingRect().width() - width()) * ff, m_coins->y());
    m_item->setPos(200+(m_item->boundingRect().width() - width()) * ff, m_item->y());
    checkColliding();
}

void MyScene::jumpPlayer()
{
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
        return;

    const qreal y = (m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    m_player->setPos(m_player->pos().x(), y);

    checkColliding();
}

void MyScene::initPlayField()
{
    setSceneRect(0,0,800,340);
    m_groundLevel = 300;

    m_sky = new BackgroundItem(QPixmap(":images/sky"));
    addItem(m_sky);

    BackgroundItem *ground = new BackgroundItem(QPixmap(":images/ground"));
    addItem(ground);
    ground->setPos(0, m_groundLevel );

    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

    m_grass = new BackgroundItem(QPixmap(":images/grass"));
    m_grass->setPos(0,m_groundLevel - m_grass->boundingRect().height());
    addItem(m_grass);

    m_item = new BackgroundItem(QPixmap(":images/Warp"));
    m_item->setPos(200,m_groundLevel - m_item->boundingRect().height());
    addItem(m_item);

    m_player = new Player();
    m_minX = m_player->boundingRect().width() / 2.0;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 1.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() );
    m_realPos = m_minX;
    addItem(m_player);


    // Add some coins
    int xrange = (m_maxX - m_minX) * 0.94;
    int hrange = m_jumpHeight;
    m_coins = new QGraphicsRectItem(0,0,m_fieldWidth, m_jumpHeight);
    m_coins->setPen(Qt::NoPen);
    for (int i = 0; i < 25; ++i) {
        Coin *c = new Coin(m_coins);
        c->setPos(m_minX + qrand()%xrange, qrand()%hrange);
    }
    addItem(m_coins);
    m_coins->setPos(0, m_groundLevel - m_jumpHeight);
}

qreal MyScene::jumpFactor() const
{
    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor)
{
    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}

void MyScene::checkTimer()
{
    if (0 == m_player->direction())
        m_timer.stop();
    else if (!m_timer.isActive())
        m_timer.start();
}

void MyScene::checkColliding()
{
    QList<QGraphicsItem*> items =  collidingItems(m_player);
    for (int i = 0, total = items.count(); i < total; ++i) {
        if (Coin *c = qgraphicsitem_cast<Coin*>(items.at(i)))
            c->explode();
    }

}

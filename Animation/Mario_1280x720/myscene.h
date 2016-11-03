#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include<QMediaPlayer>

class QGraphicsPixmapItem;
class QPropertyAnimation;
class Coin;
class BackgroundItem;
class Player;

class Tube;
class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit MyScene(QObject *parent = 0);

    void timerEvent(QTimerEvent *);

    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void movePlayer();
    void jumpPlayer();
    void checkTimer();
    //void checkColliding();

signals:
    void jumpFactorChanged(qreal);

private:
    void initPlayField();

    int m_velocity;
    int m_skippedMoving;
    qreal m_groundLevel;
    qreal m_minX;
    qreal m_maxX;
    QTimer m_timer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight;
    int m_fieldWidth;
    qreal m_realPos; //The actual position of character

    Player* m_player;
    BackgroundItem *m_sky;
    BackgroundItem *m_Scene;
    BackgroundItem *m_ground;
    BackgroundItem *flag;
    QList<Coin *> m_coins;
    Tube *m_tube;
    QMediaPlayer* jumpSound;
};

#endif // MYSCENE_H

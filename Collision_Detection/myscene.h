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
class Castle;
class Goomba;
class QuestBox;
class GlowBrick;
class Turtle;
class Piranha;


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
    void checkColliding();

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

    BackgroundItem *m_flag;

    BackgroundItem *m_warpTube;
    BackgroundItem *m_warpTube2;
    BackgroundItem *m_castle;
    BackgroundItem *m_cluster9;
    BackgroundItem *m_cluster8;
    BackgroundItem *m_cluster7;
    BackgroundItem *m_cluster6;
    BackgroundItem *m_cluster5;
    BackgroundItem *m_cluster4;
    BackgroundItem *m_cluster3;
    BackgroundItem *m_cluster2;

    Coin  *m_coins;
    Coin  *m_coins2;
    Coin  *m_coins3;
    Coin  *m_coins4;
    Coin  *m_coins5;
    Coin  *m_coins6;
    Coin  *m_coins7;
    Coin  *m_coins8;
    Coin  *m_coins9;
    Coin  *m_coins10;
    Coin  *m_coins11;
    Coin  *m_coins12;
    Coin  *m_coins13;
    Coin  *m_coins14;
    Coin  *m_coins15;
    Coin  *m_coins16;
    Coin  *m_coins17;
    Coin  *m_coins18;
    Coin  *m_coins19;
    Coin  *m_coins20;
    Coin  *m_coins21;
    Coin  *m_coins22;
    Coin  *m_coins23;
    Coin  *m_coins24;
    Coin  *m_coins25;
    Coin  *m_coins26;

    Castle *h_castle;
    Goomba *m_goomba;
    QuestBox *m_questbox;
    QuestBox *m_questbox2;
    QuestBox *m_questbox3;


    GlowBrick *m_glowbrick;
    GlowBrick *m_glowbrick2;
    GlowBrick *m_glowbrick3;
    GlowBrick *m_glowbrick4;
    GlowBrick *m_glowbrick5;
    GlowBrick *m_glowbrick6;
    GlowBrick *m_glowbrick7;
    GlowBrick *m_glowbrick8;
    GlowBrick *m_glowbrick9;
    GlowBrick *m_glowbrick10;
    GlowBrick *m_glowbrick11;
    GlowBrick *m_glowbrick12;
    GlowBrick *m_glowbrick13;
    GlowBrick *m_glowbrick14;
    GlowBrick *m_glowbrick15;
    GlowBrick *m_glowbrick16;
    GlowBrick *m_glowbrick17;
    GlowBrick *m_glowbrick18;

    Turtle *m_turtle;
    Piranha *m_piranha;
    Piranha *m_piranha2;

    //QList<Coin *> m_coins;
    //QList<Coin *> m_coins2;
    QMediaPlayer* jumpSound;
};

#endif // MYSCENE_H

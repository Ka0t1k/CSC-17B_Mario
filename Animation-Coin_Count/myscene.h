#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include<QMediaPlayer>
#include <QAbstractAnimation>

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
class CoinCounter;
class WarpTube;
class Flag;

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
    void handleCollisionWithPlatform();
    QGraphicsItem* collidingPlatforms();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);


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

    BackgroundItem *m_castle;
    BackgroundItem *m_cluster9;
    BackgroundItem *m_cluster8;
    BackgroundItem *m_cluster7;
    BackgroundItem *m_cluster6;
    BackgroundItem *m_cluster5;
    BackgroundItem *m_cluster4;
    BackgroundItem *m_cluster3;
    BackgroundItem *m_cluster2;
    BackgroundItem *m_countLogo;
    BackgroundItem *m_sign;
    BackgroundItem *m_wall2;
    BackgroundItem *m_wall;
    BackgroundItem *m_wall3;

    WarpTube *m_warpTube;
    WarpTube *m_warpTube2;

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
    Coin  *m_coins27;
    Coin  *m_coins28;
    Coin  *m_coins29;
    Coin  *m_coins30;
    Coin  *m_coins31;

    Coin  *m_coins32;
    Coin  *m_coins33;
    Coin  *m_coins34;
    Coin  *m_coins35;
    Coin  *m_coins36;

    Coin  *m_coins37;
    Coin  *m_coins38;
    Coin  *m_coins39;
    Coin  *m_coins40;
    Coin  *m_coins41;

    Coin  *m_coins42;
    Coin  *m_coins43;
    Coin  *m_coins44;
    Coin  *m_coins45;
    Coin  *m_coins46;
    Coin  *m_coins47;


    Castle *h_castle;

    Goomba *m_goomba;
    Goomba *m_goomba2;

    QuestBox *m_questbox;
    QuestBox *m_questbox2;
    QuestBox *m_questbox3;
    QuestBox *m_questbox4;
    QuestBox *m_questbox5;

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
    GlowBrick *m_glowbrick19;
    GlowBrick *m_glowbrick20;

    Turtle *m_turtle;
    Turtle *m_turtle2;

    Piranha *m_piranha;
    Piranha *m_piranha2;

    Flag * m_flag2;

    QGraphicsItem* m_platform;
    CoinCounter * m_count;

    QMediaPlayer* jumpSound;
    QMediaPlayer* coinSound;


};

#endif // MYSCENE_H

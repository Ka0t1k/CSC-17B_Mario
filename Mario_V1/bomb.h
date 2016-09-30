#ifndef BOMB_H
#define BOMB_H

#include "brick.h"

class Bomb : public Brick
{
public:
    Bomb(int, int);
    static int currentFrame;
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    ~Bomb();
};

#endif // BOMB_H

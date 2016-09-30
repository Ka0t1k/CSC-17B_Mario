#ifndef SMASH_H
#define SMASH_H

#include "brick.h"

class Smash : public Brick
{
public:
    Smash(int, int);
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    ~Smash();
    static int currentFrame;
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }

private:
    bool show = false;
};

#endif // SMASH_H

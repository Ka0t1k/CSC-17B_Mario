#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "person.h"

class PiranhaPlant : public Person
{
public:
    PiranhaPlant(int, int);
    ~PiranhaPlant();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int m){ this->moveCount = m; }

private:
    int moveCount = 50;
};

#endif // PIRANHAPLANT_H

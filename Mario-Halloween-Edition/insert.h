
#ifndef INSERT_H
#define INSERT_H

#include "brick.h"
#include <QString>

enum struct InsertType {};

class Insert : public Brick
{
public:
    Insert(int, int, QString);
    ~Insert();
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }
    inline void setType(InsertType type){ this->type = type; }
    inline InsertType getType(){ return this->type; }

private:
    bool show = false;
    InsertType type;
};

#endif // INSERT_H


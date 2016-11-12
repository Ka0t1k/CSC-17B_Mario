#ifndef CASTLE_H
#define CASTLE_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Castle : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:
     explicit Castle(QGraphicsItem *parent = 0);
     enum { Type = UserType + 1 };
         int type() const;


private:



};



#endif // CASTLE_H

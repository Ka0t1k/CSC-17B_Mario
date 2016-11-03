#ifndef TUBE_H
#define TUBE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Tube: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT


public:
    explicit Tube(QGraphicsItem *parent = 0);
    enum { Type = UserType + 2};
    int type() const;

private:


};
#endif // TUBE_H

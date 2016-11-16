#ifndef WARPTUBE_H
#define WARPTUBE_H
#include <QGraphicsItem>
#include <QPixmap>

class WarpTube : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT

public:
    explicit WarpTube(QGraphicsItem *parent = 0);
    enum { Type = UserType + 5 };
    int type() const;

private:



};
#endif // WARPTUBE_H

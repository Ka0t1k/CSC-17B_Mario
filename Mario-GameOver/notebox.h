#ifndef NOTEBOX_H
#define NOTEBOX_H
#include <QGraphicsItem>
#include <QPixmap>

class NoteBox : public QGraphicsItem
{
public:
    NoteBox(QGraphicsItem *parent = 0);
    void nextFrame10();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame10;
    QPixmap mPixmap10;
};
#endif // NOTEBOX_H

#ifndef QUESTBOX_H
#define QUESTBOX_H
#include <QGraphicsItem>
#include <QPixmap>


class QuestBox : public QGraphicsItem
{
public:
    QuestBox(QGraphicsItem *parent = 0);
    void nextFrame4();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:

    int mCurrentFrame4;
    QPixmap mPixmap4;

};
#endif // QUESTBOX_H

#include "coin.h"

#include <QParallelAnimationGroup>
#include <QPen>
#include <QPropertyAnimation>

Coin::Coin(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
  , m_explosion(false)
{
    setPen(QPen(QColor(241, 190, 56), 2));
    setBrush(QColor(252, 253, 151));
    setRect(-12, -12, 24, 24);
}

int Coin::type() const
{
    return Type;
}

void Coin::explode()
{
    if (m_explosion)
        return;

    m_explosion = true;
    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    QPropertyAnimation *ani = new QPropertyAnimation(this, "opacity", this);
    ani->setDuration(700);
    ani->setStartValue(1);
    ani->setEndValue(0);
    ani->setEasingCurve(QEasingCurve::OutQuart);
    group->addAnimation(ani);

    ani = new QPropertyAnimation(this, "rect", this);
    ani->setDuration(700);
    QRectF r = rect();
    ani->setStartValue(r);
    ani->setEndValue(QRectF(r.topLeft() - r.bottomRight(), r.size() * 2));
    ani->setEasingCurve(QEasingCurve::OutQuart);
    group->addAnimation(ani);

    group->start();
}

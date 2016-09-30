#include "header.h"

Header::Header()
{
    this->rect = QRect(0, 0, 900, 40);
    this->color = QColor(Qt::white);
    this->text = QString("vie");
    gold.load(":images/gold_small.png");
    this->goldSize = gold.rect();
    this->goldPosition = QPoint(this->getRect().width() + 40, this->getRect().height() - 10);
}

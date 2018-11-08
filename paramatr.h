#ifndef PARAMATR_H
#define PARAMATR_H

#include <QGraphicsTextItem>

class paramatr : public QGraphicsTextItem
{
    Q_OBJECT
public:
    paramatr(void)
    {
        setOpacity(0.4);
        setFlags(QGraphicsItem::ItemIsSelectable);
    }
};

#endif // PARAMATR_H

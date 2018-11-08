#ifndef PARAMSUZH_H
#define PARAMSUZH_H

#include <QGraphicsTextItem>

class paramsuzh : public QGraphicsTextItem
{
    Q_OBJECT
public:
    paramsuzh(void)
    {
        //this->setRect(QRectF(-40,-40,20,20));
        //this->setData(0,"ParamSuzh");

        //setPen(QPen(QBrush(Qt::black), 1));
        //setBrush(QBrush(Qt::white));
        setOpacity(0.4);

        setFlags(QGraphicsItem::ItemIsSelectable);
    }
};

#endif // PARAMSUZH_H

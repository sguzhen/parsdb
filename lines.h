#ifndef LINES
#define LINES
#include <QGraphicsItem>
#include <QPen>

class lineS : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    lineS(void)
    {
        setPen(QPen(QBrush(Qt::black), 1));
        //setBrush(QBrush(Qt::black));
        //setOpacity(1);

        setFlag(QGraphicsItem::ItemStacksBehindParent);
    }
};
//

#endif // LINES


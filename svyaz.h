#ifndef SVYAZ
#define SVYAZ


#include <QGraphicsPolygonItem>
#include <QPen>

class svyaz : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    svyaz(void)
    {
        setPen(QPen(QBrush(Qt::black), 1));
        setBrush(QBrush(Qt::white));

        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemStacksBehindParent);
        QPolygonF polygone;
        polygone << QPointF(0, 0) << QPointF(60, -40) << QPointF(120, 0) << QPointF(60, 40);
        this->setPolygon(polygone);
    }

    int xx,yy;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public slots:
    void recPosXSuzhSvyaz(int XX, int YY);

signals:
    void sendPosSuzhSvyaz(int);
};


#endif // SVYAZ


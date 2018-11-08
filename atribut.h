#ifndef ATRIBUT
#define ATRIBUT
#include "atrparam.h"
#include <QGraphicsItem>
#include <QPen>

class atribut : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    atribut(void)
    {
        setPen(QPen(QBrush(Qt::black), 1));
        setBrush(QBrush(Qt::white));

        this->setData(0,"Atribut");
        this->setData(7,0);      //kolvo simvolov/razmera tipa dannih iznachalno 0
        this->setData(8,0);     //flag proverki dobavlyaem mi atribut na scenu ili net, 0 - net, 1 - da
        this->setRect(QRectF(-30,-30,120,80));

        this->setAcceptHoverEvents(true);   //razreshit sobitiya navedeniya

        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemStacksBehindParent);
    }

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

    atrparam* aparam;

    int xx;
    int yy;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent* event);

public slots:
    void recTip(const QString& aa, const QString& bb, int KolSimv, const QString& nameAtr, bool st);

signals:
    void sendAtrText(QString, QString, QString, int);
    void sendTekuzhAtr(QGraphicsItem*);

    void netwSetAtr(QGraphicsItem*, QString, QString, QString, QString);
};
//

#endif // ATRIBUT


#ifndef SUZHNOST
#define SUZHNOST

#include "suzhparam.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QPen>

class suzhnost : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    suzhnost(void)
    {
        this->setRect(QRectF(-30,-30,120,80));
        this->setData(0,"Suzhnost");

        setPen(QPen(QBrush(Qt::black), 1));
        setBrush(QBrush(Qt::white));

        this->setData(11,"0");          //obnulyaem flag

        this->setAcceptHoverEvents(true);

        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    }

    bool checkNetw = false;
    suzhparam* sparam;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //pri navedenii na suzhnosti mishyu
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent* event)
    {
        if (this->data(0).toString() == "Suzhnost")
        {
            emit sendTekuzhSuzh(this);  //sohranim ukazatel na suzhnost na kotoroy mish
            for (int i = 0; i<this->childItems().count();i++)
            {
                if ((this->childItems().value(i)->data(0).toString() == "ParamSuzhAdd") || (this->childItems().value(i)->data(0).toString() == "ParamSuzhDel") || (this->childItems().value(i)->data(0).toString() == "ParamSuzhSv"))
                {
                    this->childItems().value(i)->setVisible(true);
                }
            }
        }
        return QGraphicsItem::hoverEnterEvent(event);
    }

    //pri uhode mishi s suzhnosti
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent* event)
    {
        for (int i = 0; i<this->childItems().count();i++)
        {
            if ((this->childItems().value(i)->data(0).toString() == "ParamSuzhAdd") || (this->childItems().value(i)->data(0).toString() == "ParamSuzhDel") || (this->childItems().value(i)->data(0).toString() == "ParamSuzhSv"))
            {
                this->childItems().value(i)->setVisible(false);
            }
        }
        return QGraphicsItem::hoverLeaveEvent(event);
    }

    //dvoinoe nazhatie na suzhnosi
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    //odinocnoe nazhatie na suzhnosi - otpusk
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

public slots:
    void recNameSuzh(const QString&);

signals:
    void sendTekuzhSuzh(QGraphicsItem*);
    void sendSuzhText(const QString&);

    //void netwSendPosSuzh(QGraphicsItem*, QPoint);
    void checkNetwork(bool);
    void sendPosSuzhNetwork(QGraphicsItem*, double, double);
};



#endif // SUZHNOST


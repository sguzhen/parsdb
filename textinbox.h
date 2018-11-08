#ifndef TEXTINBOX
#define TEXTINBOX

#include <QGraphicsTextItem>
#include <QDebug>

class textinbox : public QGraphicsTextItem
{
    Q_OBJECT
public:
    //textinbox(QGraphicsItem * parent = 0);
    textinbox(void)
    {
        //setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    }

    //dvoinoe nazhatie po teksty na suzhnosti
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    //{
        //if (textInteractionFlags() == Qt::NoTextInteraction) setTextInteractionFlags(Qt::TextEditorInteraction);
        //QGraphicsItem::mouseDoubleClickEvent(event);
    //}
};


#endif // TEXTINBOX


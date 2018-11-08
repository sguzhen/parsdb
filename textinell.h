#ifndef TEXTINELL
#define TEXTINELL

#include <QGraphicsTextItem>
#include <QDebug>

class textinell : public QGraphicsTextItem
{
    Q_OBJECT
public:
    //textinell(QGraphicsItem * parent = 0);
    textinell (void)
    {
        //setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    }

    //dvoinoe nazhatie po teksty na atribute
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    //{
    //    if (textInteractionFlags() == Qt::NoTextInteraction) setTextInteractionFlags(Qt::TextEditorInteraction);
    //    QGraphicsItem::mouseDoubleClickEvent(event);
    //}
};

#endif // TEXTINELL


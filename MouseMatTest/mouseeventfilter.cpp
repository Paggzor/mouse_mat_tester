#include "mouseeventfilter.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

bool MouseEventFilter::eventFilter(QObject */*obj*/, QEvent *event)
{
    QGraphicsSceneMouseEvent *me = dynamic_cast<QGraphicsSceneMouseEvent*>(event);

    if(me)
    {
        emit mousePos( me->scenePos() );
    }

    return false;
}

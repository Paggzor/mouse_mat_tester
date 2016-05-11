#ifndef MOUSEEVENTFILTER_H
#define MOUSEEVENTFILTER_H

#include <QObject>

class MouseEventFilter : public QObject
{
    Q_OBJECT

public:
    signals:
        void mousePos( const QPointF& pos );

    protected:
          bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MOUSEEVENTFILTER_H

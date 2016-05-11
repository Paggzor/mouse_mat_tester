#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene();

    QGraphicsEllipseItem *m_target;
    QGraphicsRectItem    *m_bounds;
    QPainterPath         m_path;

    double              m_percent;
    QTime               m_lastFrame;  //Timestamp of m_percent
    QTime               m_lastLap;    //Timestamp of last time m_percent was 0
    QPointF             m_mouseScenePos;

    int                 m_period_ms;

    double m_error;
    double m_errorMsecs;

private slots:
    void advanceTime();
    void setCursorScenePos(QPointF pos );

};


#endif // MAINWINDOW_H

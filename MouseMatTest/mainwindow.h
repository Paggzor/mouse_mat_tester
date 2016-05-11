#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

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
    QPointF m_dt;

private slots:
    void advanceTime();

};


#endif // MAINWINDOW_H

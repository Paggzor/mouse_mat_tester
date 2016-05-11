#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QTimer>
#include <QDebug>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dt(1,1)
{
    ui->setupUi(this);

    QTimer *tmr = new QTimer(this);
    tmr->start(1000/40);
    connect(tmr, SIGNAL(timeout()), this, SLOT(advanceTime()));

    ui->graphicsView->setScene(new QGraphicsScene());

    m_target = scene()->addEllipse( 0,0,5,5, QPen( Qt::red) , QBrush(Qt::red) );

    m_bounds = scene()->addRect(0,0,1024,768 );

    resize(1100,900);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsScene *MainWindow::scene()
{
    return ui->graphicsView->scene();
}

void MainWindow::advanceTime()
{
    QPointF pos = m_target->pos();
    if(pos.x() < 0 )
        m_dt.setX( 1 );
    else if( pos.x() > m_bounds->boundingRect().width() )
        m_dt.setX( -1 );

    if(pos.y() < 0 )
        m_dt.setY( 1 );
    else if( pos.y() > m_bounds->boundingRect().height() )
        m_dt.setY( -1 );

    m_target->setPos( pos + m_dt );
//    qDebug() << "pos:" << pos << ", delta:" << m_dt ;
}

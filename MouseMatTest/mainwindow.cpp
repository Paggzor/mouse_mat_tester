#include "mainwindow.h"
#include "mouseeventfilter.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QTimer>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QtMath>
#include <QTime>
#include <QGraphicsSceneMouseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_percent(0)
    , m_error(0)
    , m_errorMsecs(0)
    , m_lastLap( QTime::currentTime() )
    , m_period_ms(3000)
{
    ui->setupUi(this);

    QTimer *tmr = new QTimer(this);
    tmr->start(10);  //100 FPS Max
    connect(tmr, SIGNAL(timeout()), this, SLOT(advanceTime()));

    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->setCursor( Qt::CrossCursor );
    ui->graphicsView->setMouseTracking(true);

    m_target = scene()->addEllipse( 0,0,5,5, QPen( Qt::red) , QBrush(Qt::red) );

    m_bounds = scene()->addRect(0,0,1024,768 );

    QVector<QPointF> points;
    m_path.moveTo( QPointF(100,100 ) );
    points.push_back( QPointF( 150,  50 ) );
    points.push_back( QPointF(200,100 ) );
    points.push_back( QPointF(250,150 ) );
    points.push_back( QPointF(200,200 ) );
    points.push_back( QPointF(150,250 ) );
    points.push_back( QPointF(100,200 ) );

    points.push_back( QPointF( 50,150 ) );
    points.push_back( QPointF(100,100 ) );

    for(int t=0; t<points.size(); t+=2 )
    {
        m_path.quadTo( points.at(t), points.at((t+1) % points.size() ) );
    }


//    scene()->addPath( m_path );

    MouseEventFilter *m = new MouseEventFilter();
    connect(m, SIGNAL(mousePos(QPointF)), this, SLOT(setCursorScenePos(QPointF)) );

    scene()->installEventFilter( m );

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
    QPointF err = m_target->scenePos() - m_mouseScenePos;

    QTime curr   = QTime::currentTime();
    int delta_ms = m_lastFrame.msecsTo( curr );

    m_error += delta_ms* QPointF::dotProduct( err, err );
    m_errorMsecs += delta_ms;

    // Calculation of next frame
    if( m_lastLap.msecsTo( curr ) > m_period_ms )
    {
        ui->statusBar->showMessage( QString("Error: %1").arg( (int) (m_error/m_errorMsecs) ) );
        m_errorMsecs = 0;
        m_error = 0;
        m_lastLap = curr;
    }

    m_percent    = ((double) m_lastLap.msecsTo( curr )) / m_period_ms;

    m_target->setPos( m_path.pointAtPercent( m_percent ) );

    m_lastFrame   = curr;
}

void MainWindow::setCursorScenePos(QPointF pos)
{
    m_mouseScenePos = pos;
}

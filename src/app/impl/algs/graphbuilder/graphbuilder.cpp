#include "graphbuilder.h"
#include <QApplication>
#include <QGridLayout>
#include <qcustomplot/qcustomplot.h>
#include <QtPrintSupport/QPrinter>
#include <algorithm>
#include <vector>
#include <string>
#include <QString>
#include <QRandomGenerator>
#include <QColor>
#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QMouseEvent>
#include <QPixmap>
#include <QFileDialog>
#include <QDateTime>
#include <QImageWriter>
#include <QInputDialog>
#include <bits/stdc++.h>
#include <QUrl>
#include <QDesktopServices>
#include <QVector3D>
#include <cmath>
#include <QWidget>

GraphBuilder::GraphBuilder( QWidget* parent )
    : QWidget(parent)

{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    layout = new QVBoxLayout( this );
    graph2d = new QCustomPlot( this );
    graph3d = new GL3DGraphBuilder( this );

    //graph2d->setVisible(false);

    textItem = new QCPItemText( graph2d );
    textItem->setVisible( false );
    connect( graph2d, &QCustomPlot::mouseMove, this, &GraphBuilder::onMousMove );
    connect( graph2d, &QCustomPlot::mouseMove, this, &GraphBuilder::textVisible );

    graph2d->setMinimumSize( 550, 500 );

    tracer = new QCPItemTracer( graph2d );
    tracer->setGraph( graph2d->graph( 0 ) );

    graph2d->xAxis->setLabel( "x" );
    graph2d->yAxis->setLabel( "y" );
    graph2d->xAxis->setRange( xmin, xmax );
    graph2d->yAxis->setRange( ymin, ymax );

    graph2d->replot();

    graph3d->setMinimumSize( 550, 500 );
    graph3d->hide();

    layout->addWidget( graph2d );
    layout->addWidget( graph3d );
}


void GraphBuilder::updateGraphState( const GraphState& state )
{
    auto graphInfoList = state.graphInfoList;
    auto name = state.name;
    auto xAxis = state.xAxis;
    auto yAxis = state.yAxis;
    auto scatterOn = state.scatterOn;
    auto graphOn = state.graphOn;
    auto fillingOn = state.fillingOn;


    graph2d->clearGraphs();
    i = 0;
    for( const GraphInfo& info : currentState->graphInfoList )
    {
        if ( i >= graph2d->graphCount() )
        {
            graph2d->addGraph();
        }
        graph2d->graph( i )->setData( info.xAxis, info.yAxis );


        QColor color = QColor::fromRgb( QRandomGenerator::global()->bounded( 172 ),
                                       QRandomGenerator::global()->bounded( 172 ),
                                       QRandomGenerator::global()->bounded( 172 ) );
        QPen pin( color );

        if( info.fillingOn == true ){
        QColor fillColor = color;
        fillColor.setAlpha(128);
        graph2d->graph(i)->setBrush(QBrush(fillColor));
        }

        graph2d->graph()->setPen( pin );
        if (scatterOn == false){
            //graph2d->graph(i)->setScatterStyle();
        }else {
            graph2d->graph()->setScatterStyle( QCPScatterStyle::ssCircle );
        }
        QPen pen = graph2d->graph()->pen();
        pen.setWidth( 4 );
        graph2d->graph( i )->setPen( pen );

        // Устанавливаем стили линий и точек
        graph2d->graph( i )->setLineStyle( info.graphOn ? QCPGraph::lsLine : QCPGraph::lsNone );
        graph2d->graph( i )->setScatterStyle( info.scatterOn ? QCPScatterStyle::ssCircle : QCPScatterStyle::ssNone );

        // Устанавливаем видимость графика
        graph2d->graph( i )->setVisible( info.graphOn || info.scatterOn );

        graph2d->graph( i )->setName( info.name );
        ++i;
    }
    graph2d->replot();
}

void GraphBuilder::PaintG( const QVector<double>& xAxis, const QVector<double>& yAxis, const QString& name, bool graphOn, bool scatterOn, bool fillingOn, const std::optional<QVector<double>> z )
{

    if( z->size() > 0 )
    {
        auto _x = std::vector<double>( xAxis.begin(), xAxis.end() );
        auto _y = std::vector<double>( yAxis.begin(), yAxis.end() );
        auto _z = std::vector<double>( z->begin(), z->end() );
        QVector<QVector3D> points;

        for( size_t i = 0; i < _x.size(); ++i )
        {
            qDebug() << "x[" << i << "]: " << _x[i] << " " << "y[" << i << "]: " << _y[i] << " " << "z[" << i << "]: " << _z[i] << " " << "\n";
            points.append( QVector3D( _x[i], _y[i], _z[i] ) );
        }
        graph3d->buildGraph( points );
    }

    GraphInfo newGraphInfo( name, xAxis, yAxis, graphOn, scatterOn, fillingOn);

    if ( std::find_if( graphInfoList.begin(), graphInfoList.end(), [ & ] ( const GraphInfo& info ) {
            return info.name == newGraphInfo.name && info.xAxis == newGraphInfo.xAxis && info.yAxis == newGraphInfo.yAxis;
        } ) != graphInfoList.end() )
    {
        return;
    }

    graphInfoList.append( newGraphInfo );

    GraphState newState;
    newState.graphInfoList = graphInfoList;

    graphStates.push_back( newState );
    currentState = std::prev( graphStates.end() );

    auto maxXElement = std::max_element( xAxis.begin(), xAxis.end() );
    auto minXElement = std::min_element( xAxis.begin(), xAxis.end() );
    auto maxYElement = std::max_element( yAxis.begin(), yAxis.end() );
    auto minYElement = std::min_element( yAxis.begin(), yAxis.end() );
    if ( xmax < *maxXElement )
    {
        if( xmin > *minXElement )
        {
            xmax = *maxXElement;
            xmin = *minXElement;
            graph2d->xAxis->setRange( xmin, xmax );
            graph2d->replot();
            graph2d->update();
        }
        else
        {
            xmax = *maxXElement;
            graph2d->xAxis->setRange( xmin, xmax );
            graph2d->replot();
            graph2d->update();
        }
    }
    else if( xmin > *minXElement )
    {
        xmin = *minXElement;
        graph2d->xAxis->setRange( xmin, xmax );
        graph2d->replot();
        graph2d->update();

    }
    if ( ymax < *maxYElement )
    {
        if( ymin > *minYElement )
        {
            ymax = *maxYElement;
            ymin = *minYElement;
            graph2d->yAxis->setRange( ymin, ymax );
            graph2d->replot();
            graph2d->update();
        }
        else
        {
            ymax = *maxYElement;
            graph2d->yAxis->setRange( ymin, ymax );
            graph2d->replot();
            graph2d->update();
        }
    }
    else if( ymin > *minYElement )
    {
        ymin = *minYElement;
        graph2d->yAxis->setRange( ymin, ymax );
        graph2d->replot();
        graph2d->update();
    }

    if (xmax-xmin < ymax-ymin )
    {
        ymax = xmax;
        ymin = xmin;
        graph2d->yAxis->setRange(ymin, ymax);
        graph2d->xAxis->setRange(xmin, xmax);
        graph2d->replot();
        graph2d->update();
    }

    if (xmax-xmin > ymax-ymin )
    {
        xmax = ymax;
        xmin = ymin;
        graph2d->yAxis->setRange(ymin, ymax);
        graph2d->xAxis->setRange(xmin, xmax);
        graph2d->replot();
        graph2d->update();
    }

    if ( i >= graph2d->graphCount() )
    {
        graph2d->addGraph();
    }
    graph2d->graph( i )->setData( xAxis, yAxis );
    graph2d->graph( i )->setLineStyle( graphOn ? QCPGraph::lsLine : QCPGraph::lsNone );
    QColor color = QColor::fromRgb( QRandomGenerator::global()->bounded( 172 ),
                                   QRandomGenerator::global()->bounded( 172 ),
                                   QRandomGenerator::global()->bounded( 172 ) );
    QPen pin( color );

    if( fillingOn == true){
    QColor fillColor = color;
    fillColor.setAlpha(128);
    graph2d->graph(i)->setBrush(QBrush(fillColor));    
    }

    graph2d->graph( i )->setPen( pin );
    graph2d->graph( i )->setScatterStyle( scatterOn ? QCPScatterStyle::ssCircle : QCPScatterStyle::ssNone );
    QPen pen = graph2d->graph( i )->pen();
    pen.setWidth( 4 );
    graph2d->graph( i )->setPen( pen );
    graph2d->graph( i )->setName( name );
    graph2d->graph( i )->setVisible( graphOn || scatterOn );
    graph2d->replot();

    ++i;
    graph2d->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectPlottables );
    emit couldSavePlotAsImage( true );
}

void GraphBuilder::onClearButtonClicked()
{
    for( int g{}; g < i; ++g )
    {
        graph2d->graph( g )->data()->clear();
    }
    graph2d->legend->clear();
    graph2d->legend->setVisible( false );
    xmax = 2.0;
    xmin = -2.0;
    ymax = 2.0;
    ymin = -2.0;
    graph2d->xAxis->setRange( xmin, xmax );
    graph2d->yAxis->setRange( ymin, ymax );
    graph2d->replot();
    graph2d->update();
    graphInfoList.clear();
    emit couldSavePlotAsImage( false );
}

void GraphBuilder::resetZoom(){
    graph2d->xAxis->setRange( xmin, xmax );
    graph2d->yAxis->setRange( ymin, ymax );
    graph2d->replot();
    graph2d->update();
}

void GraphBuilder::onMousMove( QMouseEvent *event )
{
    QCustomPlot* customPlot = qobject_cast<QCustomPlot*>( sender() );
    double x = customPlot->xAxis->pixelToCoord( event->pos().x() );
    double y = customPlot->yAxis->pixelToCoord( event->pos().y() );
    textItem->setText( QString( "(%1, %2)" ).arg( x ).arg( y ) );
    textItem->position->setCoords( QPointF( x,y ) );
    textItem->setFont( QFont( font().family(), 10 ) );
    //textItem->setVisible(true);
    customPlot->replot();
}

void GraphBuilder::textVisible( QMouseEvent *event )
{
    QPoint pos = event->pos();
    QCPAbstractPlottable* plottable = graph2d-> plottableAt( pos,false );
    if ( plottable )
    {
        textItem->setVisible( true );
    }
    else
    {
        textItem->setVisible( false );
    }
}

void GraphBuilder::moveLegend(){
    if(l == 0){
        graph2d->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignRight);
        graph2d->replot();
    }
    if( l == 1 )
    {
        graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignRight );
        graph2d->replot();
    }
    if( l == 2 )
    {
        graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignVCenter );
        graph2d->replot();
    }
    if( l == 3 )
    {
        graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignLeft );
        graph2d->replot();
    }
    if( l == 4 )
    {
        graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignCenter|Qt::AlignLeft );
        graph2d->replot();
    }
    if( l == 5 )
    {
       graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignLeft );
       graph2d->replot();
    }
    if( l == 6 )
    {
       graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignCenter );
       graph2d->replot();
    }
    if( l == 7 )
    {
       graph2d->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignRight );
       graph2d->replot();
       l = -1;
    }
    l++;
}

void GraphBuilder::showLegend()
{
    if( !graph2d->legend->visible() )
    {
       graph2d->legend->setVisible( true );
       graph2d->replot();
    }
}

void GraphBuilder::hideLegend()
{
    if( graph2d->legend->visible() )
    {
       graph2d->legend->setVisible( false );
       graph2d->replot();
    }
}


void GraphBuilder::GoBack()
{
    if( graphStates.empty() )
    {
       return;
    }
    if( currentState != graphStates.begin() )
    {
       --currentState;
       updateGraphState( *currentState );
    }
}

void GraphBuilder::GoFront()
{
    if( graphStates.empty() )
    {
       return;
    }
    if( currentState != graphStates.end() - 1 )
    {
       ++currentState;
       updateGraphState( *currentState );
    }
}

void GraphBuilder::zoomIn()
{
    QCPRange xRange = graph2d->xAxis->range();
    QCPRange yRange = graph2d->yAxis->range();

    double xCenter = xRange.center();
    double yCenter = yRange.center();

    double xWidth = xRange.size() / 2;
    double yWidth = yRange.size() / 2;

    graph2d->xAxis->setRange( xCenter - xWidth / 2, xCenter + xWidth / 2 );
    graph2d->yAxis->setRange( yCenter - yWidth / 2, yCenter + yWidth / 2 );
    graph2d->replot();
}

void GraphBuilder::zoomOut()
{
    QCPRange xRange = graph2d->xAxis->range();
    QCPRange yRange = graph2d->yAxis->range();

    double xCenter = xRange.center();
    double yCenter = yRange.center();

    double xWidth = xRange.size() * 2;
    double yWidth = yRange.size() * 2;

    graph2d->xAxis->setRange( xCenter - xWidth / 2, xCenter + xWidth / 2 );
    graph2d->yAxis->setRange( yCenter - yWidth / 2, yCenter + yWidth / 2 );
    graph2d->replot();
}

void GraphBuilder::savePlotAsImage()
{
    QFileDialog fileDialog( nullptr, "Save Plot",  QDir::homePath(), "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*)" );
    fileDialog.setAcceptMode( QFileDialog::AcceptSave );
    fileDialog.setOption( QFileDialog::DontConfirmOverwrite, false );
    fileDialog.setDirectory( "/home" );

    if (fileDialog.exec() == QFileDialog::Accepted)
    {
        QString fileName = fileDialog.selectedFiles().first();
        QPixmap pixmap(graph2d->size());
        graph2d->render(&pixmap);
        if (!fileName.endsWith(".png") && !fileName.endsWith(".jpg"))
        {
            QStringList imageFormats = QStringList() << "PNG" << "JPG";
            QString selectedFormat = QInputDialog::getItem(this, "Сохранить график", "Выберите формат изображения:", imageFormats, 0, false);
            pixmap.save(fileName + "." + selectedFormat.toLower());
        }
        else
        {
            pixmap.save(fileName);
        }
    }
}

void GraphBuilder::setupThreeCView( void )
{
    setGeometry(0, 0, 550, 500);
}

void GraphBuilder::switchToGL3DGraphBuilder( void )
{
    graph2d->setVisible( false );
    graph3d->setVisible( true );
}

void GraphBuilder::switchToGraphBuilder( void )
{
    graph2d->setVisible( true );
    graph3d->setVisible( false );
}

void GraphBuilder::mousePressEventd(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        lastPos = event->pos();
    }
}

void GraphBuilder::mouseMoveEventd(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        float dx = (event->x() - lastPos.x()) * 0.3f;
        float dy = (event->y() - lastPos.y()) * 0.3f;
        lastPos = event->pos();

        xRot += dy;
        yRot += dx;
        //QOpenGLWidget::update();

    }
}

void GraphBuilder::wheelEventd(QWheelEvent* event) {
    float d = event->delta() / 120.0f * 0.1f;
    scale += d;
    if (scale < 0.1f)
        scale = 0.1f;
    //QOpenGLWidget::update();
}

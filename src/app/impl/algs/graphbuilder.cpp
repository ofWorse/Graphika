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


GraphBuilder::GraphBuilder( QWidget* parent )
    : QWidget( parent )
{
    layout = new QGridLayout( this );
    wGraphic = new QCustomPlot( this );

    textItem = new QCPItemText( wGraphic );
    textItem->setVisible( false );
    connect( wGraphic, &QCustomPlot::mouseMove, this, &GraphBuilder::onMousMove );
    connect( wGraphic, &QCustomPlot::mouseMove, this, &GraphBuilder::textVisible );


    wGraphic->setMinimumSize( 550, 500 );


    tracer = new QCPItemTracer( wGraphic );
    tracer->setGraph( wGraphic->graph( 0 ) );

    wGraphic->xAxis->setLabel( "x" );
    wGraphic->yAxis->setLabel( "y" );

    wGraphic->xAxis->setRange( xmin, xmax );
    wGraphic->yAxis->setRange( ymin, ymax );

    wGraphic->replot();

    layout->addWidget( wGraphic );
}


void GraphBuilder::updateGraphState( const GraphState& state )
{
    auto graphInfoList = state.graphInfoList;
    auto name = state.name;
    auto xAxis = state.xAxis;
    auto yAxis = state.yAxis;
    auto scatterOn = state.scatterOn;
    auto graphOn = state.graphOn;


    wGraphic->clearGraphs();
    i = 0;
    for( const GraphInfo& info : currentState->graphInfoList )
    {
        if ( i >= wGraphic->graphCount() )
        {
            wGraphic->addGraph();
        }
        wGraphic->graph( i )->setData( info.xAxis, info.yAxis );


        QColor color = QColor::fromRgb( QRandomGenerator::global()->bounded( 172 ),
                                       QRandomGenerator::global()->bounded( 172 ),
                                       QRandomGenerator::global()->bounded( 172 ) );
        QPen pin( color );
        wGraphic->graph()->setPen( pin );
        if (scatterOn == false){
            //wGraphic->graph(i)->setScatterStyle();
        }else {
            wGraphic->graph()->setScatterStyle( QCPScatterStyle::ssCircle );
        }
        QPen pen = wGraphic->graph()->pen();
        pen.setWidth( 4 );
        wGraphic->graph( i )->setPen( pen );

        // Устанавливаем стили линий и точек
        wGraphic->graph( i )->setLineStyle( info.graphOn ? QCPGraph::lsLine : QCPGraph::lsNone );
        wGraphic->graph( i )->setScatterStyle( info.scatterOn ? QCPScatterStyle::ssCircle : QCPScatterStyle::ssNone );

        // Устанавливаем видимость графика
        wGraphic->graph( i )->setVisible( info.graphOn || info.scatterOn );

        wGraphic->graph( i )->setName( info.name );
        ++i;
    }
    wGraphic->replot();
}


void GraphBuilder::PaintG( const QVector<double>& xAxis, const QVector<double>& yAxis, const QString& name, bool graphOn, bool scatterOn )
{
    GraphInfo newGraphInfo( name, xAxis, yAxis, graphOn, scatterOn );

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
            wGraphic->xAxis->setRange( xmin, xmax );
            wGraphic->replot();
            wGraphic->update();
        }
        else
        {
            xmax = *maxXElement;
            wGraphic->xAxis->setRange( xmin, xmax );
            wGraphic->replot();
            wGraphic->update();
        }
    }
    else if( xmin > *minXElement )
    {
        xmin = *minXElement;
        wGraphic->xAxis->setRange( xmin, xmax );
        wGraphic->replot();
        wGraphic->update();

    }
    if ( ymax < *maxYElement )
    {
        if( ymin > *minYElement )
        {
            ymax = *maxYElement;
            ymin = *minYElement;
            wGraphic->yAxis->setRange( ymin, ymax );
            wGraphic->replot();
            wGraphic->update();
        }
        else
        {
            ymax = *maxYElement;
            wGraphic->yAxis->setRange( ymin, ymax );
            wGraphic->replot();
            wGraphic->update();
        }
    }
    else if( ymin > *minYElement )
    {
        ymin = *minYElement;
        wGraphic->yAxis->setRange( ymin, ymax );
        wGraphic->replot();
        wGraphic->update();
    }

    if ( i >= wGraphic->graphCount() )
    {
        wGraphic->addGraph();
    }
    wGraphic->graph( i )->setData( xAxis, yAxis );
    wGraphic->graph( i )->setLineStyle( graphOn ? QCPGraph::lsLine : QCPGraph::lsNone );
    QColor color = QColor::fromRgb( QRandomGenerator::global()->bounded( 172 ),
                                   QRandomGenerator::global()->bounded( 172 ),
                                   QRandomGenerator::global()->bounded( 172 ) );
    QPen pin( color );
    wGraphic->graph( i )->setPen( pin );
    wGraphic->graph( i )->setScatterStyle( scatterOn ? QCPScatterStyle::ssCircle : QCPScatterStyle::ssNone );
    QPen pen = wGraphic->graph( i )->pen();
    pen.setWidth( 4 );
    wGraphic->graph( i )->setPen( pen );
    wGraphic->graph( i )->setName( name );
    wGraphic->graph( i )->setVisible( graphOn || scatterOn );
    wGraphic->replot();
    ++i;
    wGraphic->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectPlottables );
    emit couldSavePlotAsImage( true );
}

void GraphBuilder::onClearButtonClicked()
{
    for( int g{}; g < i; ++g )
    {
        wGraphic->graph( g )->data()->clear();
    }
    wGraphic->legend->clear();
    wGraphic->legend->setVisible( false );
    xmax = 2.0;
    xmin = -2.0;
    ymax = 2.0;
    ymin = -2.0;
    wGraphic->xAxis->setRange( xmin, xmax );
    wGraphic->yAxis->setRange( ymin, ymax );
    wGraphic->replot();
    wGraphic->update();
    graphInfoList.clear();
    emit couldSavePlotAsImage( false );
}

void GraphBuilder::resetZoom(){
    wGraphic->xAxis->setRange( xmin, xmax );
    wGraphic->yAxis->setRange( ymin, ymax );
    wGraphic->replot();
    wGraphic->update();
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
    QCPAbstractPlottable* plottable = wGraphic-> plottableAt( pos,false );
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
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignRight);
        wGraphic->replot();
    }
    if( l == 1 )
    {
        wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignRight );
        wGraphic->replot();
    }
    if( l == 2 )
    {
        wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignVCenter );
        wGraphic->replot();
    }
    if( l == 3 )
    {
        wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignBottom|Qt::AlignLeft );
        wGraphic->replot();
    }
    if( l == 4 )
    {
        wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignCenter|Qt::AlignLeft );
        wGraphic->replot();
    }
    if( l == 5 )
    {
       wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignLeft );
       wGraphic->replot();
    }
    if( l == 6 )
    {
       wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignCenter );
       wGraphic->replot();
    }
    if( l == 7 )
    {
       wGraphic->axisRect()->insetLayout()->setInsetAlignment( 0,Qt::AlignTop|Qt::AlignRight );
       wGraphic->replot();
       l = -1;
    }
    l++;
}

void GraphBuilder::showLegend()
{
    if( !wGraphic->legend->visible() )
    {
       wGraphic->legend->setVisible( true );
       wGraphic->replot();
    }
}

void GraphBuilder::hideLegend()
{
    if( wGraphic->legend->visible() )
    {
       wGraphic->legend->setVisible( false );
       wGraphic->replot();
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
    QCPRange xRange = wGraphic->xAxis->range();
    QCPRange yRange = wGraphic->yAxis->range();

    double xCenter = xRange.center();
    double yCenter = yRange.center();

    double xWidth = xRange.size() / 2;
    double yWidth = yRange.size() / 2;

    wGraphic->xAxis->setRange( xCenter - xWidth / 2, xCenter + xWidth / 2 );
    wGraphic->yAxis->setRange( yCenter - yWidth / 2, yCenter + yWidth / 2 );
    wGraphic->replot();
}

void GraphBuilder::zoomOut()
{
    QCPRange xRange = wGraphic->xAxis->range();
    QCPRange yRange = wGraphic->yAxis->range();

    double xCenter = xRange.center();
    double yCenter = yRange.center();

    double xWidth = xRange.size() * 2;
    double yWidth = yRange.size() * 2;

    wGraphic->xAxis->setRange( xCenter - xWidth / 2, xCenter + xWidth / 2 );
    wGraphic->yAxis->setRange( yCenter - yWidth / 2, yCenter + yWidth / 2 );
    wGraphic->replot();
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
        QPixmap pixmap(wGraphic->size());
        wGraphic->render(&pixmap);
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


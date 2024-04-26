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


GraphBuilder::GraphBuilder( QWidget* parent )
    : QWidget( parent )
{
    layout = new QGridLayout( this );
    wGraphic = new QCustomPlot( this );
    plots = new QList<QCustomPlot*>(  );

    textItem = new QCPItemText(wGraphic);
    connect( wGraphic, &QCustomPlot::mouseMove, this, &GraphBuilder::onMousMove );

    wGraphic->setMinimumSize( 550, 500 );




    tracer = new QCPItemTracer( wGraphic );
    tracer->setGraph( wGraphic->graph( 0 ) );

    wGraphic->xAxis->setLabel( "x" );
    wGraphic->yAxis->setLabel( "y" );

    wGraphic->xAxis->setRange( xmin, xmax );
    wGraphic->yAxis->setRange( ymin, ymax );

    wGraphic->replot();

    //layout->addWidget(new QToolBar(this));

    layout->addWidget( wGraphic );
}

void GraphBuilder::PaintG( QVector<double>& xAxis, QVector<double>& yAxis, const QString& name, bool graphOn, bool scatterOn )
{
    GraphInfo newGraphInfo( name, xAxis, yAxis, graphOn, scatterOn );


    if ( std::find_if( graphInfoList.begin(), graphInfoList.end(), [ & ] ( const GraphInfo& info ) {
            return info.name == newGraphInfo.name && info.xAxis == newGraphInfo.xAxis && info.yAxis == newGraphInfo.yAxis;
        } ) != graphInfoList.end() )
    {
        return;
    }

    graphInfoList.append( newGraphInfo );

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

    wGraphic->addGraph( wGraphic->xAxis, wGraphic->yAxis );
    if( !xAxis.isEmpty() && !yAxis.isEmpty() )
        wGraphic->graph( i )->setData( xAxis, yAxis );
    if (graphOn == false){
        wGraphic->graph(i)->setLineStyle(QCPGraph::lsNone);
    }
    //wGraphic->graph(i)->setInterpolation(trou);
    QColor color = QColor::fromRgb( QRandomGenerator::global()->bounded( 255 ),
                                    QRandomGenerator::global()->bounded( 255 ),
                                    QRandomGenerator::global()->bounded( 255 ) );
    QPen pin( color );
    wGraphic->graph( i )->setPen( pin );
    if (scatterOn == false){
        //wGraphic->graph(i)->setScatterStyle();
    }else {
    wGraphic->graph( i )->setScatterStyle( QCPScatterStyle::ssCircle );
    }
    wGraphic->graph( i )->setName( name );
    QPen pen = wGraphic->graph( i )->pen();
    pen.setWidth( 4 );
    wGraphic->graph( i )->setPen( pen );
    i++;
    wGraphic->replot();
    QCustomPlot* plot = wGraphic;
    plots->append(plot);
    qDebug() << plots->size() << "\n";
    qDebug() << plots->size() << "\n";
    currentindex = plots->size() - 1;
    wGraphic->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectPlottables);
}




void GraphBuilder::on_clearButton_clicked()
{
    wGraphic->clearGraphs();
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
    data.clear();
    graphInfoList.clear();
}

void GraphBuilder::ZoomB(){
    wGraphic->xAxis->setRange( xmin, xmax );
    wGraphic->yAxis->setRange( ymin, ymax );
    wGraphic->replot();
    wGraphic->update();
}

void GraphBuilder::onMousMove(QMouseEvent *event){
    QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(sender());
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());
    textItem->setText(QString("(%1, %2)").arg(x).arg(y));
    textItem->position->setCoords(QPointF(x,y));
    textItem->setFont(QFont(font().family(), 10));
    customPlot->replot();
}

void GraphBuilder::LegendGo(){
    if(l == 0){
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignRight);
        l++;
        wGraphic->replot();
    }
    if(l == 1){
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignBottom|Qt::AlignRight);
        wGraphic->replot();
    }
    if(l == 2){
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignBottom|Qt::AlignVCenter);
        wGraphic->replot();
    }
    if(l == 3){
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignBottom|Qt::AlignLeft);
        wGraphic->replot();
    }
    if(l == 4){
        wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignLeft);
        wGraphic->replot();
    }
    if(l == 5){
       wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
       wGraphic->replot();
    }
    if(l == 6){
       wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignCenter);
       wGraphic->replot();
    }
    if(l == 7){
       wGraphic->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
       wGraphic->replot();
       l = -1;
    }
    l++;

}

void GraphBuilder::LegentSee(){
    if(wGraphic->legend->visible()){
       wGraphic->legend->setVisible( false );
       wGraphic->replot();
    }else {
       wGraphic->legend->setVisible( true );
       wGraphic->replot();
    }
}

void GraphBuilder::GoBack(){
    //if (currentindex > 0 && plots->size() > 0) {

      // wGraphic->clearGraphs();
      // wGraphic = plots[currentindex];
       //wGraphic->replot();
       //wGraphic->update();
    //}
    //currentindex--;


}

void GraphBuilder::GoFront(){

}




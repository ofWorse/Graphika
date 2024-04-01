#include "graphbuilder.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
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

GraphBuilder::GraphBuilder(QWidget *parent)
    : QWidget(parent)
{

    wGraphic = new QCustomPlot();

    tracer = new QCPItemTracer(wGraphic);
    tracer->setGraph(wGraphic->graph(0));

    wGraphic->xAxis->setLabel("x");
    wGraphic->yAxis->setLabel("y");

    wGraphic->xAxis->setRange(xmin,xmax);
    wGraphic->yAxis->setRange(ymin,ymax);

    wGraphic->replot();




}

void GraphBuilder::PaintG( QVector <double> xAxis, QVector <double> yAxis, const QString name)
{
    auto maxXElement = std::max_element(xAxis.begin(), xAxis.end());
    auto minXElement = std::min_element(xAxis.begin(), xAxis.end());
    auto maxYElement = std::max_element(yAxis.begin(), yAxis.end());
    auto minYElement = std::min_element(yAxis.begin(), yAxis.end());
    if (xmax<*maxXElement){
        if(xmin>*minXElement){
            xmax = *maxXElement;
            xmin = *minXElement;
            wGraphic->xAxis->setRange(xmin, xmax);
            wGraphic->replot();
            wGraphic->update();
        } else {
            xmax = *maxXElement;
            wGraphic->xAxis->setRange(xmin, xmax);
            wGraphic->replot();
            wGraphic->update();
        }
    }else if(xmin>*minXElement){
        xmin = *minXElement;
        wGraphic->xAxis->setRange(xmin, xmax);
        wGraphic->replot();
        wGraphic->update();

    }
    if (ymax<*maxYElement){
        if(ymin>*minYElement){
            ymax = *maxYElement;
            ymin = *minYElement;
            wGraphic->yAxis->setRange(ymin, ymax);
            wGraphic->replot();
            wGraphic->update();
        } else {
            ymax = *maxYElement;
            wGraphic->xAxis->setRange(ymin, ymax);
            wGraphic->replot();
            wGraphic->update();
        }
    }else if(ymin>*minYElement){
        ymin = *minYElement;
        wGraphic->xAxis->setRange(ymin, ymax);
        wGraphic->replot();
        wGraphic->update();

    }



    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(i)->setData(xAxis,yAxis);
    //wGraphic->graph(i)->setInterpolation(trou);
    QColor color = QColor::fromRgb(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
    QPen pin(color);
    wGraphic->graph(i)->setPen(pin);
    wGraphic->graph(i)->setScatterStyle(QCPScatterStyle::ssCircle);
    wGraphic->graph(i)->setName(name);
    wGraphic->legend->setVisible(true);
    QPen pen = wGraphic->graph(i)->pen();
    pen.setWidth(4);
    wGraphic->graph(i)->setPen(pen);
    i++;

}


void GraphBuilder::on_clearButton_clicked()
{
    for(int c = 0; c < i; ++c){
    wGraphic->graph(c)->data()->clear();
    }
    wGraphic->legend->clear();
    wGraphic->legend->setVisible(false);
    wGraphic->replot();
    wGraphic->update();


}


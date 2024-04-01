#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <QMainWindow>
#include <qcustomplot/qcustomplot.h>
#include <QDebug>
#include <string>
#include <QString>
#include <QWidget>




class GraphBuilder : public QWidget
{
    Q_OBJECT
public:
    explicit GraphBuilder(QWidget *parent = 0);
    int i = 0;
    double xmax = 2.0;
    double xmin = -2.0;

    double ymax = 2.0;
    double ymin = -2.0;

private:
    QCustomPlot *wGraphic;
    QCPItemTracer *tracer;
//Collichestvo tochek neobhodimo ykazivat
public slots:
    void PaintG(QVector <double> x,QVector <double> y,const QString name);
    void on_clearButton_clicked();
private slots:

};
#endif // GRAPHBUILDER_H

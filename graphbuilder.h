#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <QMainWindow>
#include <qcustomplot/qcustomplot.h>
#include <QDebug>
#include <string>
#include <QString>
#include <QWidget>

namespace Ui
{
class MainWindow;
}

class GraphBuilder : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QCustomPlot* wGraphic;
    QCPItemTracer* tracer;

public:
    explicit GraphBuilder( QWidget *parent = nullptr );
    int i = 0;
    double xmax = 2.0;
    double xmin = -2.0;

    double ymax = 2.0;
    double ymin = -2.0;

public slots:
    void PaintG( QVector<double>& x, QVector<double>& y, const QString& name );
    void on_clearButton_clicked( void );

};
#endif // GRAPHBUILDER_H

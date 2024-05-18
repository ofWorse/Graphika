/*!
 * \class GraphBuilder
 *
 * \brief The GraphBuilder class for painting graphics
 *
 * \company Dnevnie Mechaniki
 *
 * \author Vilenskiy Kirill Romanovich
 *
 * \date last update: 18.05.2024
 */

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <QMainWindow>
#include <qcustomplot/qcustomplot.h>
#include <QDebug>
#include <string>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include_next "graphInfo.h"

struct GraphState
{
    QVector<GraphInfo> graphInfoList;
    QString name;
    QVector<double> xAxis;
    QVector<double> yAxis;
    bool graphOn;
    bool scatterOn;
};

class GraphBuilder : public QWidget
{
    Q_OBJECT

private:
    QCPItemTracer* tracer;
    QGridLayout* layout;
    QCPItemText* textItem;
    QList<QCustomPlot*>* plots;

    int i = 0;
    int l = 0;
    int currentindex;

    double xmax = 2.0;
    double xmin = -2.0;
    double ymax = 2.0;
    double ymin = -2.0;

    QVector<GraphInfo> graphInfoList;

    std::vector<GraphState> graphStates;
    std::vector<GraphState>::iterator currentState;

    bool unpinned = false;

public:
    QCustomPlot* wGraphic;

public:
    explicit GraphBuilder( QWidget *parent = nullptr );

private:
    void updateGraphState( const GraphState& state );

public slots:
    void PaintG( const QVector<double>& x, const QVector<double>& y, const QString& name, bool graphOn, bool scatterOn );
    void on_clearButton_clicked( void );
    void ZoomB();
    void onMousMove(QMouseEvent* event);
    void textVisible(QMouseEvent* event);
    void LegendGo();
    void showLegend();
    void hideLegend();
    void GoBack();
    void GoFront();
    void zoomIn();
    void zoomOut();
    void saveG();

signals:
    void couldSavePlotAsImage( bool couldSave );



};

#endif // GRAPHBUILDER_H

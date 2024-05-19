#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <QString>
#include <QVector>
#include <QColor>

class GraphInfo
{
public:
    QString name;
    QVector<double> xAxis;
    QVector<double> yAxis;
    QColor color;
    bool graphOn;
    bool scatterOn;

    GraphInfo( const QString& name, const QVector<double>& xAxis, const QVector<double>& yAxis, bool graphOn, bool scatterOn )
        : name(name), xAxis(xAxis), yAxis(yAxis), graphOn(graphOn), scatterOn(scatterOn) {}
};

#endif // GRAPHINFO_H

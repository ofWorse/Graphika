/*!
 * \attention In development.
 *
 * \author Korshunov Ilya Dmitrievich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <QString>
#include <QVector>
#include <QColor>

/*!
 * \class GraphInfo
 *
 * \brief The GraphInfo class
 */
class GraphInfo
{
public:
    QString name; ///< name of legend.
    QVector<double> xAxis; ///< x data variables.
    QVector<double> yAxis; ///< y data variables.
    QColor color; ///< color of curve or nodes.
    bool graphOn; ///< is curve must be shown.
    bool scatterOn; ///< is nodes must be shown.

    /*!
     * \brief GraphInfo: standard constructor.
     *
     * \param name: name of legend.
     * \param xAxis: x data variables.
     * \param yAxis: y data variables.
     * \param graphOn: color of curve or nodes.
     * \param scatterOn: is nodes must be shown.
     */
    GraphInfo(const QString& name, const QVector<double>& xAxis, const QVector<double>& yAxis, bool graphOn, bool scatterOn)
        : name(name), xAxis(xAxis), yAxis(yAxis), graphOn(graphOn), scatterOn(scatterOn) {}
};

#endif // GRAPHINFO_H

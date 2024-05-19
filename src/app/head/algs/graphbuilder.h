/*!
 * \brief The GraphBuilder class for painting graphics
 *
 * \company Dnevnie Mechaniki
 *
 * \author Vilenskiy Kirill Romanovich
 *
 * \date last update: 20.05.2024
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
    QVector<GraphInfo> graphInfoList; ///< List for saving the graph info.

    QString name; ///< Name of the graph.

    QVector<double> xAxis; ///< Array of X coordinates of the graph.
    QVector<double> yAxis; ///< Array of Y coordinates of the graph.

    bool graphOn; ///< A variable responsible for drawing or not drawing a graph line.
    bool scatterOn; ///< A variable responsible for drawing or not drawing a scatter.
};

/*!
 * \class GraphBuilder.
 *
 * \brief GraphBuilder: A class that builds and edits graphs.
 */
class GraphBuilder : public QWidget
{
    Q_OBJECT

private:
    QCPItemTracer* tracer; ///< Tracer linked to data points.
    QGridLayout* layout; ///< The layout to which all other objects are written.
    QCPItemText* textItem; ///< Item that displays the coordinates of the point where the user is pointing.

    QList<QCustomPlot*>* plots; ///< List that contains all states plot.

    int i = 0; ///< Graph count variable.
    int l = 0; ///< Legend position number.
    int currentindex; ///< Current index.

    double xmax = 2.0; ///< Maximum X coordinate space.
    double xmin = -2.0; ///< Minimum X coordinate space.
    double ymax = 2.0; ///< Maximum Y coordinate space.
    double ymin = -2.0; ///< Minimum Y coordinate space.

    QVector<GraphInfo> graphInfoList; ///< List for saving the graph info.

    std::vector<GraphState> graphStates; ///< Graphic state vector.
    std::vector<GraphState>::iterator currentState; ///< Iterator of the current state graph.

    bool unpinned = false; ///< The variable indicates whether the graph window is detached from the general program.

public:
    QCustomPlot* wGraphic; ///< The object to which all graphs are recorded.

public:
    /*!
     * \brief GraphBuilder: Creates a space where everything happens.
     *
     * \param parent - Pointer to the parent widget.
     */
    explicit GraphBuilder( QWidget *parent = nullptr );

private:
    /*!
     * \brief updateGraphState: Builds python list from std::vector<double>.
     *
     * \param state - Graph state variable.
     *
     * \return Graph state.
     */
    void updateGraphState( const GraphState& state );

public slots:
    /*!
     * \brief PaintG: Create and paint graphs.
     *
     * \param x - An array of vector x coordinates.
     * \param y - An array of vector y coordinates.
     * \param name - Name of the graph.
     * \param graphOn - A variable responsible for drawing or not drawing a graph line.
     * \param scatterOn - A variable responsible for drawing or not drawing a scatter.
     *
     * \return Graph.
     */
    void PaintG( const QVector<double>& x, const QVector<double>& y, const QString& name, bool graphOn, bool scatterOn );

    /*!
     * \brief on_clearButton_clicked: Erases all graphics.
     */
    void on_clearButton_clicked( void );

    /*!
     * \brief resetZoom: Returns the graph window to its original position.
     */
    void resetZoom();

    /*!
     * \brief onMousMove: When you move the cursor, it shows the coordinates of the point. which the user points to.
     *
     * \param event - Event that tracks mouse movement.
     *
     * \return Mouse position.
     */
    void onMousMove(QMouseEvent* event);

    /*!
     * \brief textVisible: Prevents coordinates from being displayed above the graph.
     *
     * \param event - Event that tracks mouse movement.
     *
     * \return Mouse position.
     */
    void textVisible(QMouseEvent* event);

    /*!
     * \brief moveLegend: Moves the graph legend.
     */
    void moveLegend();

    /*!
     * \brief showLegend: Enable graphics display.
     */
    void showLegend();

    /*!
     * \brief hideLegend: Turns off graphics display.
     */
    void hideLegend();

    /*!
     * \brief GoBack: Rolls back the number of charts by one step.
     */
    void GoBack();

    /*!
     * \brief GoFront: Returns the number of graphs one step ahead.
     */
    void GoFront();

    /*!
     * \brief zoomIn: The schedule is approaching.
     */
    void zoomIn();

    /*!
     * \brief zoomOut: Zooms out the chart.
     */
    void zoomOut();

    /*!
     * \brief savePlotAsImage: Saves graphs.
     */
    void savePlotAsImage();

signals:
    /*!
     * \brief couldSavePlotAsImage: Не дает сохранения пустого пространства.
     *
     * \param couldSave - Allow or disable saving the scene.
     */
    void couldSavePlotAsImage( bool couldSave );



};

#endif // GRAPHBUILDER_H

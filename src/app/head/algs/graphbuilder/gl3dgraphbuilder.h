#ifndef GL3DGRAPBUILDER_H
#define GL3DGRAPBUILDER_H

#include "qevent.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <GL/gl.h>


class GL3DGraphBuilder : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 modelView;
    QVector<QVector3D> points;

    QMatrix4x4 cameraTransform;
    QMatrix4x4 rotation;
    QPoint lastMousePos;

    struct GraphData
    {
        QVector<QVector3D> vertices;
        QColor color;
    };

    QVector<GraphData> figures;

    float axisLineWidth;
    float gridLineWidth;
    float pointSize;

public:
    GL3DGraphBuilder( QWidget* parent = nullptr );

    void buildGraph( const QVector<QVector3D>& points )
    {
        /*
        GraphData graph;
        graph.color = getRandomColor();
        graph.vertices = points;

        figures.append( graph );
        this->points = points;
        update();
        */
        GraphData graphData;
        graphData.vertices = points;
        graphData.color = getRandomColor();
        figures.push_back(graphData);
        update();
    }

protected:

    void initializeGL() override;
    void resizeGL( int width, int height ) override;
    void paintGL() override;

    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void wheelEvent( QWheelEvent* event ) override;

private:
    void drawAxes( void );
    void drawGrid( void );
    QColor getRandomColor( void )
    {
        return QColor::fromRgbF( static_cast<float>(rand())/RAND_MAX,
                                static_cast<float>(rand())/RAND_MAX,
                                static_cast<float>(rand())/RAND_MAX );
    }

signals:
    void dataUpdated();
};

#endif //GL3DGRAPBUILDER_H

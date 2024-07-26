#include "gl3dgraphbuilder.h"

GL3DGraphBuilder::GL3DGraphBuilder( QWidget* parent ) : QOpenGLWidget( parent )
{
    axisLineWidth = 5.0f;
    gridLineWidth = 1.0f;
    pointSize = 5.0f;
}

void GL3DGraphBuilder::initializeGL( void )
{
    initializeOpenGLFunctions();
    glEnable( GL_DEPTH_TEST );
}

void GL3DGraphBuilder::resizeGL( int width, int height )
{
    glViewport( 0, 0, width, height );
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective( 45.0f, static_cast<float>(width) / height, 0.1f, 100.0f );
}

void GL3DGraphBuilder::paintGL( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    modelView = cameraTransform * rotation;
    glMultMatrixf( modelView.data() );

    drawGrid();
    drawAxes();

    /*
    if ( !points.isEmpty() ) {
        glPolygonMode( GL_FRONT_FACE, GL_FILL );
        glColor3f( figures[graphIndex].color.redF(), figures[graphIndex].color.greenF(),figures[graphIndex].color.blueF());
        glBegin( GL_QUADS );
        for ( int i = 0; i < points.size() - 1; ++i )
        {
            const QVector3D& p1 = points[i];
            const QVector3D& p2 = points[i + 1];
            glVertex3f( p1.x(), p1.y(), p1.z() );
            glVertex3f( p1.x(), 0.0f, p1.z() );
            glVertex3f( p2.x(), 0.0f, p2.z() );
            glVertex3f( p2.x(), p2.y(), p2.z() );
        }
        glEnd();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    */

    for (const auto& graph : figures) {
        glColor3f(graph.color.redF(), graph.color.greenF(), graph.color.blueF());
        glPolygonMode( GL_FRONT_FACE, GL_FILL );
        glBegin(GL_QUADS);
        for (int i = 0; i < graph.vertices.size() - 1; ++i ) {
            const QVector3D& p1 = graph.vertices[i];
            const QVector3D& p2 = graph.vertices[i + 1];
            glVertex3f( p1.x(), p1.y(), p1.z() );
            glVertex3f( p1.x(), 0.0f, p1.z() );
            glVertex3f( p2.x(), 0.0f, p2.z() );
            glVertex3f( p2.x(), p2.y(), p2.z() );
            //glVertex3f(graph.vertices.x(), graph.vertices.y(), graph.vertices.z());
        }
        glEnd();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
}

void GL3DGraphBuilder::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        lastMousePos = event->pos();
    }
}

void GL3DGraphBuilder::mouseMoveEvent( QMouseEvent* event )
{
    if ( event->buttons() & Qt::LeftButton )
    {
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();

        rotation.rotate( 0.5f * delta.x(), 0.0f, 1.0f, 0.0f );
        rotation.rotate( 0.5f * delta.y(), 1.0f, 0.0f, 0.0f );
        update();
    }
}

void GL3DGraphBuilder::wheelEvent( QWheelEvent* event )
{
    float scaleFactor = 1.0f + ( event->delta() / 1200.0f );
    cameraTransform.scale( scaleFactor, scaleFactor, scaleFactor );
    update();
}

void GL3DGraphBuilder::drawAxes( void )
{
    glLineWidth( axisLineWidth );

    glColor3f( 1.0f, 0.0f, 0.0f );
    glBegin( GL_LINES );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 100.0f, 0.0f, 0.0f );
    glEnd();
    glPointSize( pointSize );
    glBegin( GL_POINTS );
    glVertex3f( 100.0f, 0.0f, 0.0f );
    glEnd();
    glPointSize( 1.0f );

    glColor3f( 0.0f, 1.0f, 0.0f );
    glBegin( GL_LINES );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 100.0f, 0.0f );
    glEnd();
    glPointSize( pointSize );
    glBegin( GL_POINTS );
    glVertex3f( 0.0f, 100.0f, 0.0f );
    glEnd();
    glPointSize( 1.0f );

    glColor3f( 0.0f, 0.0f, 1.0f );
    glBegin( GL_LINES );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 0.0f, 100.0f );
    glEnd();
    glPointSize( pointSize );
    glBegin( GL_POINTS );
    glVertex3f( 0.0f, 0.0f, 100.0f );
    glEnd();
    glPointSize( 1.0f );

    glLineWidth( 1.0f );
}

void GL3DGraphBuilder::drawGrid( void )
{
    glLineWidth( gridLineWidth );
    glColor3f( 0.8f, 0.8f, 0.8f );
    glBegin( GL_LINES );
    for ( int i = -10; i <= 10; ++i )
    {
        glVertex3f( -10.0f, 0.0f, static_cast<float>( i ) );
        glVertex3f( 10.0f, 0.0f, static_cast<float>( i ) );
        glVertex3f( static_cast<float>( i ), 0.0f, -10.0f );
        glVertex3f( static_cast<float>( i ), 0.0f, 10.0f );
    }
    glEnd();
    glLineWidth( 1.0f );
}

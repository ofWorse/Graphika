#include "graphbuilder.h"

void graph::GraphBuilder::buildGraph( const vector<double>& X, const vector<double>& Y )
{
    namedWindow( name.toStdString(), WINDOW_NORMAL );
    resizeWindow( name.toStdString(), GraphBuilder::size, GraphBuilder::size );
    Mat image = Mat::zeros( GraphBuilder::size, GraphBuilder::size, CV_8UC3 );

    switch( axisSpotter( X, Y ) )
    {
        // TODO: CRUTCH. Gonna restrict that later;
    case ( int ) CONS_SPOTTER::NO_CONS :
    {
        // ...
    }
    case ( int ) CONS_SPOTTER::X_CONS :
    {
        // ...
    }
    case ( int ) CONS_SPOTTER::Y_CONS :
    {
        // ...
    }
    }

    Point2d prevPoint( 0, 0 );
    Point2d currentPoint;

    for( int i{}; i < X.size(); ++i )
    {
        double y = Y[i];
        currentPoint = Point2d( X[i] + 50, y + 50 );
        std::cout << prevPoint.x << ", " << prevPoint.y << " : " << currentPoint.x << ", " << currentPoint.y << std::endl;
        line( image, prevPoint, currentPoint, Scalar( 255, 255, 0 ), 2 );
        prevPoint = currentPoint;
    }

    imshow( name.toStdString(), image );
    waitKey();
}

// TODO: ...
int graph::GraphBuilder::axisSpotter(const vector<double> &X, const vector<double> &Y) const
{
    return 0;
}

// TODO: ...
void graph::GraphBuilder::Builder::produceAxis() const
{
    line( image, Point( _beginAxis, _endAxis ),
         Point( _endAxis, _endAxis ), Scalar( 255 ), 2 );
    line( image, Point( _beginAxis, _endAxis ),
         Point( _beginAxis, _beginAxis ), Scalar( 255 ), 2 );
    //
    line( image, Point( _beginAxis, _endAxis ),
         Point( _endAxis, _endAxis ), Scalar( 255 ), 2 );
    line( image, Point( center, _endAxis ),
         Point( center, _beginAxis ), Scalar( 255 ), 2 );
    //
    line( image, Point( _beginAxis, center ),
         Point( _endAxis, center ), Scalar( 255 ), 2 );
    line( image, Point( center, _endAxis ),
         Point( center, _beginAxis ), Scalar( 255 ), 2 );
}

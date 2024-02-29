#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <QString>
#include <vector>

using namespace cv;
using namespace std;

namespace graph
{

enum class CONS_SPOTTER : int
{
    NO_CONS, X_CONS, Y_CONS, BOTH
};

class GraphBuilder
{
private:
    const QString name;
    double size;
    static inline double center;
    static inline double _beginAxis;
    static inline double _endAxis;

public:
    GraphBuilder( const QString& name, double size )
        : name( name )
    {
        this->size = size;
        _beginAxis = ( size/100 ) * 2;
        _endAxis = ( size/100 ) * 98;
        center = size / 2;
    }
    void buildGraph( const vector<double>& X, const vector<double>& Y );

private:
    int axisSpotter( const vector<double>& X, const vector<double>& Y ) const;

private:

    class Builder
    {
    private:
        Mat image;

    public:
        Builder( const Mat& image ) : image( image ) {}
    public:
        void produceAxis() const;
        friend GraphBuilder;
    };

    friend Builder;
};

} // graph namespace

#endif // GRAPHBUILDER_H

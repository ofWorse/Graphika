#include "mathutils.h"


std::vector<double> MathUtils::multipyPoints(const double a, const double b) noexcept
{
    std::vector<double> x;
    for( double i = a; i <= b; i += 0.1 )
    {
        x.push_back( i );
    }
    if( x.back() != b )
    {
        x.push_back( b );
    }
    return x;
}

void MathUtils::setupNodes( std::vector<double>& X, const double node, const double min, const double max ) noexcept
{
    for( auto delta = min; delta <= max; delta += ( abs( min ) + abs( max ) ) / ( node + 1 ) )
    {
        X.push_back( delta );
    }
}

double MathUtils::calculateAverageError( std::vector<double> &X1, std::vector<double> &X2 ) noexcept
{
    if( X1.size() == 0 || X2.size() == 0 )
    {
        return 0.0;
    }

    double error = 0.0;
    for( std::size_t i = 0; i < X1.size(); ++i )
    {
        error += abs( X1[i] - X2[i] );
    }
    error /= X1.size();
    return error;
}

#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QWidget>
#include <vector>
#include <cmath>

class MathUtils
{
public:
    MathUtils( void );
    static std::vector<double> multipyPoints( const double a, const double b ) noexcept;
    static void setupNodes( std::vector<double>& X, const double node, const double min, const double max ) noexcept;
    static double calculateAverageError( std::vector<double>& X1, std::vector<double>& X2 ) noexcept;
};

#endif // MATHUTILS_H

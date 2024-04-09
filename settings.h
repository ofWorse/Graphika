#ifndef SETTINGS_H
#define SETTINGS_H

namespace pymodules
{

const int NODES_LIMIT = 10;

enum class Methods
{
    NEWTON, LAGRANGE, BERRUTA,
    DIFF_2P, DIFF_3P, DIFF_5P,
    NIL
};

enum class Modules
{
    POLYNOMIALS, DIFFERENTIATION, NIL
};
}
#endif // SETTINGS_H

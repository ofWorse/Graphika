#ifndef SETTINGS_H
#define SETTINGS_H

namespace pymodules
{

const int NODES_LIMIT = 10;

enum class Methods
{
    NEWTON, LAGRANGE, BERRUTA,
    DIFF_2P, DIFF_3P, DIFF_5P,
    INTEG_LINEAR, INTEG_TRAP, INTEG_PARAB,
    NIL
};

enum class Modules
{
    POLYNOMIALS, DIFFERENTIATION, INTEGRATION, EQUATIONS, NIL
};

} // pymodules

#endif // SETTINGS_H

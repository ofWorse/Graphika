#ifndef SETTINGS_H
#define SETTINGS_H

namespace limits
{
const int NODES_LIMIT = 10;
const int SIZE_LIMIT = 1002;
} // limits

namespace pymodules
{

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


namespace label
{

enum class TextLine
{
    FUNCTION, DERIVATION, EQUATIONS
};

} // layout

#endif // SETTINGS_H

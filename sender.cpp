#include "sender.h"
#include "settings.h"

Sender::Sender() {}

void Sender::setMacro(pymodules::Methods method, pymodules::Modules module) {

    switch (method) {
    case pymodules::Methods::NEWTON:
        functionName = "newton_polynomial";
        break;
    case pymodules::Methods::LAGRANGE:
        functionName = "lagrange_polynomial";
        break;
    case pymodules::Methods::BERRUTA:
        // Обработка метода BERRUTA
        break;
    default:
        // Обработка некорректного метода
        break;
    }

    switch (module) {
    case pymodules::Modules::POLYNOMIALS:
        moduleName = ":/pyFiles/resources/pymodules/polynomials.py";
        break;
    default:
        // Обработка некорректного модуля
        break;
    }
}

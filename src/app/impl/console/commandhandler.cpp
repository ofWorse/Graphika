#include "commandhandler.h"

std::string CommandHandler::checkoutStatement(const Statement &state)
{
    switch(state)
    {
    case Statement::HOME:
        return "home";
        break;
    case Statement::FUNCTION:
        return "function";
        break;
    case Statement::DERIVATION:
        return "derivation";
        break;
    case Statement::INTEGRAION:
        return "integration";
        break;
    case Statement::EQUATION:
        return "equation";
        break;
    case Statement::INTERPOLATION:
        return "interpolation";
        break;
    }
    [[unlikely]]
    return "";
}

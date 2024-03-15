#include "validatestring.h"

ValidateString::ValidateString( QObject *parent )
    : QObject{ parent }
{
}

void ValidateString::validateExpression( const QString &expr )
{
    if( isValidExpression( expr ) )
    {
        emit validExpression();
    }
    else
    {
        emit invalidExpression();
    }
}

bool ValidateString::isValidExpression( const QString &expr )
{
    return ExpressionValidator::validateExpression( expr );
}

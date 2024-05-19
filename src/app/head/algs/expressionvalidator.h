#ifndef EXPRESSIONVALIDATOR_H
#define EXPRESSIONVALIDATOR_H

#include <iostream>
#include <regex>
#include <stack>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QTableWidget>
#include <QItemDelegate>
/*
 * TODO:
 * Реализовать алгоритм проверки чтобы после x не было иных символов кроме задуманных
*/
class ExpressionValidator
{

public:
    static bool validateExpression( const QString& expression)
    {

        if ( !isExpressionValid( expression ) )
        {
            return false;
        }

        if ( !areParenthesesValid( expression ) )
        {
            return false;
        }

        return true;
    }

    static bool validateTableRow( const QString& firstColumnValue, const QString& secondColumnValue )
    {
        return validateFirstColumn( firstColumnValue ) && validateSecondColumn( secondColumnValue );
    }

private:
    static bool isExpressionValid( const QString& expression )
    {
        QRegularExpression expr( R"(^(?!.*xx)[x([(\d+\.\d+)|(0-9))+\-*/^()%]|sin|sh|asin|cos|ch|acos|tan|cot|th|atan|sqrt|cbrt|ceil|floor|round|ln|lg|abs|exp|\s]+$)" );
        QRegularExpressionMatch match = expr.match( expression.toStdString().c_str() );
        if ( match.hasMatch() )
        {
            return true;
        }
        return false;
    }

    static bool areParenthesesValid( const QString& expression )
    {
        std::stack<char> parenthesesStack;
        for ( char c : expression.toStdString() )
        {
            if ( c == '(' )
            {
                parenthesesStack.push( c );
            }
            else if ( c == ')' )
            {
                if ( parenthesesStack.empty() || parenthesesStack.top() != '(' )
                {
                    return false;
                }
                parenthesesStack.pop();
            }
        }
        return parenthesesStack.empty();
    }

    static bool validateFirstColumn( const QString& value )
    {
        QRegularExpression regex( R"(-?\d+(?:\.\d+)?(?:\s+-?\d+(?:\.\d+)?)*)",
                                 QRegularExpression::UseUnicodePropertiesOption );
        QRegularExpressionMatch match = regex.match( value );
        return match.hasMatch();
    }

    static bool validateSecondColumn( const QString& value )
    {
        QRegularExpression regex( R"(-?\d+(?:\.\d+)?)",
                                 QRegularExpression::UseUnicodePropertiesOption );
        QRegularExpressionMatch match = regex.match( value );
        return match.hasMatch() && match.capturedLength() == value.length();
    }
};


#endif // EXPRESSIONVALIDATOR_H

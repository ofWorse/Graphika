/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef EXPRESSIONVALIDATOR_H
#define EXPRESSIONVALIDATOR_H

#include <iostream>
#include <regex>
#include <stack>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QTableWidget>
#include <QItemDelegate>

/*!
 * \class ExpressionValidator.
 *
 * \brief A class that checks the string given to it for the correctness of a mathematical expression.
 */
class ExpressionValidator
{
public:

    /*!
     * \brief validateExpression: a method that produces the result of parsing a string of mathematical expression given to it
     *
     * \param expression: a string which contains math expression.
     *
     * \return boolean operator.
     */
    static bool validateExpression( const QString& expression )
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

    /*!
     * \brief validateTableRow: a method which validates rows from table widget data.
     *
     * \param firstColumnValue: a string data from the first column ( odds ).
     * \param secondColumnValue: a string data from the second column ( free terms of the equation ).
     *
     * \return boolean operator.
     */
    static bool validateTableRow( const QString& firstColumnValue, const QString& secondColumnValue )
    {
        return validateFirstColumn( firstColumnValue ) && validateSecondColumn( secondColumnValue );
    }

private:

    /*!
     * \brief isExpressionValid: an algorithmic method which contains a regular expression as a SP of comparison.
     *
     * \param expression: a string typed math expression.
     *
     * \return boolean operator.
     */
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

    /*!
     * \brief areParenthesesValid: algorithm that checks the correctness of parentheses.
     *
     * \param expression: a string typed math expression.
     *
     * \return boolean operator.
     */
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

    /*!
     * \brief validateFirstColumn: checking the correctness of the entered coefficients.
     *
     * \param value: a string typed data set of a real numbers.
     *
     * \return boolean operator.
     */
    static bool validateFirstColumn( const QString& value )
    {
        QRegularExpression regex( R"(-?\d+(?:\.\d+)?(?:\s+-?\d+(?:\.\d+)?)*)",
                                 QRegularExpression::UseUnicodePropertiesOption );
        QRegularExpressionMatch match = regex.match( value );
        return match.hasMatch();
    }

    /*!
     * \brief validateSecondColumn: a method that checks the correctness of the introduced free terms of the equation.
     *
     * \param value: a string typed data of a real number.
     *
     * \return boolean operator.
     */
    static bool validateSecondColumn( const QString& value )
    {
        QRegularExpression regex( R"(-?\d+(?:\.\d+)?)",
                                 QRegularExpression::UseUnicodePropertiesOption );
        QRegularExpressionMatch match = regex.match( value );
        return match.hasMatch() && match.capturedLength() == value.length();
    }
};

#endif // EXPRESSIONVALIDATOR_H

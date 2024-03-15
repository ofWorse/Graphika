#include "expressionvalidator.h"



bool ExpressionValidator::validateExpression(const std::string &expression)
{
    if( !isExpressionValid( expression ) )
    {
        return false;
    }

    if( !areParenthesesValid( expression ) )
    {
        return false;
    }

    if( !areFunctionsValid( expression ) )
    {
        return false;
    }

    return true;
}

bool ExpressionValidator::isExpressionValid(const std::string &expression)
{
    std::regex validExpression(R"([0-9+\-*/^()%x]|sin|cos|log|abs)");
    return std::regex_match( expression, validExpression );
}

bool ExpressionValidator::areParenthesesValid(const std::string &expression)
{
    std::stack<char> parenthesesStack;
    for( char c : expression )
    {
        if( c == '(' )
        {
            parenthesesStack.push( c );
        }
        else if( c == ')' )
        {
            if( parenthesesStack.empty() || parenthesesStack.top() != '(' )
            {
                return false;
            }
            parenthesesStack.pop();
        }
    }
    return parenthesesStack.empty();
}

bool ExpressionValidator::areFunctionsValid(const std::string &expression)
{
    std::stack<std::string> functionStack;
    std::regex functions(R"(sin|cos|log|abs)");

    for( std::size_t i{}; i < expression.size(); ++i )
    {
        if( std::isalpha( expression[i] ) )
        {
            std::string functionName;
            while( std::isalpha( expression[i] ) )
            {
                functionName.push_back( expression[i++] );
            }
            if( std::regex_match( functionName, functions ) )
            {
                functionStack.push( functionName );
            }
        }
    }
    return functionStack.empty();
}


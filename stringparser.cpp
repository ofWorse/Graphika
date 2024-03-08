#include "stringparser.h"

parser::Expression parser::StringParser::parseExpression()
{
    return parseBinaryExpression( 0 );
}

std::string parser::StringParser::parseToken()
{
    while( std::isspace( *input ) )
    {
        ++input;
    }


    if(  std::isdigit( *input ) )
    {
        std::string number;
        while( std::isdigit( *input ) || *input == '.' )
        {
            number.push_back( *input++ );
        }
        return number;
    }

    if( *input == 'x' )
    {
        ++input;
        return "x";
    }

    static const std::vector<std::string> tokens =
        { "+", "-", "*", "/", "^", "mod", "abs", "sin", "cos", "log", "(", ")" };
    for( auto& t : tokens )
    {
        if( std::strncmp( input, t.c_str(), t.size() ) == 0 )
        {
            input += t.size();
            return t;
        }
    }

    return "";
}

parser::Expression parser::StringParser::parseSimpleExpression()
{
    auto token = parseToken();

    if( token.empty() )
    {
        throw std::runtime_error( "Invalid input" );
    }

    if ( token == "(" )
    {
        auto result = parseExpression();

        if ( parseToken() != ")" )
        {
            throw std::runtime_error( "Expected ')'" );
        }

        return result;
    }

    if ( std::isdigit( token[0] ) )
    {
        return Expression( token ) ;
    }

    if( token == "x" )
    {
        return Expression( token, true );
    }

    return Expression( token, parseSimpleExpression() );
}

parser::Expression parser::StringParser::parseBinaryExpression( const int minPriority )
{
    auto leftExpr = parseSimpleExpression();

    while( true )
    {
        auto operation = parseToken();
        auto priority = getPriority( operation );

        if( priority <= minPriority )
        {
            input -= operation.size();
            return leftExpr;
        }

        auto rightExpr = parseBinaryExpression( priority );
        leftExpr = Expression( operation, leftExpr, rightExpr );
    }
}

int parser::getPriority( const std::string &token )
{
    if( token == "+" )   return 1;
    if( token == "-" )   return 1;
    if( token == "*" )   return 2;
    if( token == "/" )   return 2;
    if( token == "%" )   return 2;
    if( token == "^" )   return 3;
    return 0;
}

double parser::eval( const Expression &e, double x )
{
    if( e.isVariable )
    {
        return x;
    }

    switch( e.arguments.size() )
    {
    case 2:
    {
        auto a = eval( e.arguments[0], x );
        auto b = eval( e.arguments[1], x );

        if( e.token == "+" )   return a + b;
        if( e.token == "-" )   return a - b;
        if( e.token == "*" )   return a * b;
        if( e.token == "^" )   return pow( a, b );
        if( e.token == "%" )
        {
            if( b == 0 )
            {
                throw std::runtime_error( "Can not divive by zero" );
                exit( EXIT_FAILURE );
            }
            return ( int )a % ( int )b;
        }
        if( e.token == "/" )
        {
            if( b == 0 )
            {
                throw std::runtime_error( "Can not divive by zero" );
                exit( EXIT_FAILURE );
            }
            return a / b;
        }
        throw std::runtime_error( "Unknown binary operator" );
    }
    case 1:
    {
        auto a = eval( e.arguments[0], x );

        if( e.token == "+" )   return +a;
        if( e.token == "-" )   return -a;
        if( e.token == "abs" ) return abs( a );
        if( e.token == "sin" ) return sin( a );
        if( e.token == "cos" ) return cos( a );
        if( e.token == "log" )
        {
            if( a <= 0 )
            {
                throw std::runtime_error( "Function is undefined" );
                exit( EXIT_FAILURE );
            }
            return log( a );
        }
        throw std::runtime_error( "Unknown unary operator" );
    }
    case 0:
    {
        if( e.token == "x" )
        {
            return x;
        }
        return std::strtod( e.token.c_str(), nullptr );
    }
    }

    throw std::runtime_error( "Unknown expression type" );
}

double parser::eval( const Expression &e )
{
    return eval( e, 0.0 );
}

#include "stringparser.h"


parser::StringParser* parser::StringParser::operator=( const StringParser &parent )
{
    return new StringParser( parent.input, parent.x );
}

std::optional<parser::Expression> parser::StringParser::parseExpression()
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

std::optional<parser::Expression> parser::StringParser::parseSimpleExpression()
{
    auto token = parseToken();

    if( token.empty() )
    {
        emit errorOccurred( "Некорректный ввод" );
        return std::nullopt;
    }

    if ( token == "(" )
    {
        auto result = parseExpression();

        if ( parseToken() != ")" )
        {
            std::cout << "err" << std::endl;
            emit errorOccurred( "Требуется ')'" );
            return std::nullopt;
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

    auto nestedExpr = parseSimpleExpression();
    if( !nestedExpr.has_value() )
    {
        return std::nullopt;
    }
    return Expression( token, *nestedExpr );
}

std::optional<parser::Expression> parser::StringParser::parseBinaryExpression( const int minPriority )
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
        if( !rightExpr.has_value() )
        {
            return std::nullopt;
        }
        leftExpr = Expression( operation, leftExpr.value(), rightExpr.value() );
    }
}

int parser::StringParser::getPriority( const std::string &token )
{
    if( token == "+" )   return 1;
    if( token == "-" )   return 1;
    if( token == "*" )   return 2;
    if( token == "/" )   return 2;
    if( token == "%" )   return 2;
    if( token == "^" )   return 3;
    return 0;
}

double parser::StringParser::eval( const std::optional<Expression> &e, double x )
{
    auto expr = e.value();
    if( expr.isVariable )
    {
        return x;
    }

    switch( expr.arguments.size() )
    {
    case 2:
    {
        auto a = eval( expr.arguments[0], x );
        auto b = eval( expr.arguments[1], x );

        if( expr.token == "+" )   return a + b;
        if( expr.token == "-" )   return a - b;
        if( expr.token == "*" )   return a * b;
        if( expr.token == "^" )   return pow( a, b );
        if( expr.token == "%" )
        {
            if( b == 0 )
            {
                emit errorOccurred( "На ноль делить нельзя" );
            }
            return ( int )a % ( int )b;
        }
        if( expr.token == "/" )
        {
            if( b == 0 )
            {
                emit errorOccurred( "На ноль делить нельзя" );
            }
            return a / b;
        }
        emit errorOccurred( "Неизвестный бинарный оператор" );
    }
    case 1:
    {
        auto a = eval( expr.arguments[0], x );

        if( expr.token == "+" )   return +a;
        if( expr.token == "-" )   return -a;
        if( expr.token == "abs" ) return abs( a );
        if( expr.token == "sin" ) return sin( a );
        if( expr.token == "cos" ) return cos( a );
        if( expr.token == "log" )
        {
            if( a <= 0 )
            {
                emit errorOccurred( "Функция не определена" );
            }
            return log( a );
        }
        emit errorOccurred( "Неизвестный унарный оператор" );
    }
    case 0:
    {
        if( expr.token == "x" )
        {
            return x;
        }
        return std::strtod( expr.token.c_str(), nullptr );
    }
    }

    emit errorOccurred( "Неизвестный вид выражения" );
}

double parser::StringParser::eval( const std::optional<Expression> &e )
{
    return eval( e, 0.0 );
}


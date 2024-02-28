#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <QWidget>
#include <QStack>
#include <QPushButton>
#include <QtWidgets>
#include <vector>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace parser
{

    struct Expression
    {
        Expression( std::string token ) :
            token( token ), isVariable( false ) {}
        Expression( std::string token, bool isVariable ) :
            token( token ), isVariable( isVariable ) {}
        Expression( std::string token, Expression a ) :
            token( token ), arguments{ a }, isVariable( false ) {}
        Expression( std::string token, Expression a, Expression b ) :
            token( token ), arguments{ a, b }, isVariable( false ){}

        std::string token; // Операция или число
        std::vector<Expression> arguments; // Выражения - аргументы операции
        bool isVariable;
    };

    class StringParser : public QObject
    {
        Q_OBJECT
    private:
        const char* input;
        const double x;

    public:
        explicit StringParser( const char* input, const double x )
            : input( input ), x( x ) {}
        Expression parseExpression();

    private:
        std::string parseToken();
        Expression parseSimpleExpression();
        Expression parseBinaryExpression( const int minPriority );

    };

    int getPriority( const std::string& token );

    double eval( const Expression& e, double x );
    double eval( const Expression& e );

} // parser namespace


#endif // STRINGPARSER_H

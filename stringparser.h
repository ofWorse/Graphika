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
        Expression( std::string token ) : token( token ) {}
        Expression( std::string token, Expression a ) : token( token ), arguments{ a } {}
        Expression( std::string token, Expression a, Expression b ) : token( token ), arguments{ a, b } {}

        std::string token; // Операция или число
        std::vector<Expression> arguments; // Выражения - аргументы операции
    };

    class StringParser : public QObject
    {
        Q_OBJECT
    private:
        const char* input;

    public:
        explicit StringParser( const char* input ) : input( input ) {}
        Expression parseExpression();

    private:
        std::string parseToken();
        Expression parseSimpleExpression();
        Expression parseBinaryExpression( const int minPriority );

    };

    int getPriority( const std::string& token );

    double eval( const Expression& e );

} // parser namespace


#endif // STRINGPARSER_H

#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <QtWidgets>
#include <QStack>
#include <QPushButton>
#include <QtWidgets>
#include <optional>
#include <vector>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <optional>

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
            token( token ), arguments{ a, b }, isVariable( false ){};

        std::string token;
        std::vector<Expression> arguments;
        bool isVariable;
    };

    class StringParser : public QObject
    {
        Q_OBJECT
    private:
        const char* input;
        double x;

    public:
        explicit StringParser( const char* input, const double x )
            : input( input ), x( x ) {}
        explicit StringParser( const char* input )
            : input( input ) {}
        StringParser* operator=( const StringParser& parent );

        std::optional<Expression> parseExpression();

        void setX( const double& x ) { this->x = x; }

        double eval( const std::optional<Expression>& e, double x );
        double eval( const std::optional<Expression>& e );

    private:
        std::string parseToken();
        std::optional<Expression> parseSimpleExpression();
        std::optional<Expression> parseBinaryExpression( const int minPriority );

        int getPriority( const std::string& token );

    signals:
        void errorOccurred( const QString& err );
    };

} // parser namespace


#endif // STRINGPARSER_H

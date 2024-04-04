#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <QtWidgets>
#include <optional>
#include <vector>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <optional>

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
        unsigned const char* input;
        double x;

        std::vector<double> xTable;
    public:
        explicit StringParser( QObject *parent = nullptr );
        explicit StringParser( unsigned char* input, const double x )
            : input( input ), x( x ) {}
        explicit StringParser( unsigned char* input )
            : input( input ) {}

        std::optional<Expression> parseExpression();
        std::vector<double> parseExpression( QString input );

        void setX( const double& x ) { this->x = x; }
        void setDataX( const std::vector<double> x ) { xTable = x; }

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



#endif // STRINGPARSER_H

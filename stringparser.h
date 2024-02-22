#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <QWidget>
#include <QStack>
#include <QPushButton>
#include <QtWidgets>
#include <vector>
#include <cstring>

namespace parser
{

    struct Expression
    {
        Expression( QString token ) : token( token ) {}
        Expression( QString token, Expression a ) : token( token ), arguments{ a } {}
        Expression( QString token, Expression a, Expression b ) : token( token ), arguments{ a, b } {}

        QString token; // Операция или число
        std::vector<Expression> arguments; // Выражения - аргументы операции
    };

    class StringParser : public QObject
    {
        Q_OBJECT
    private:
        QString input;

    public:
        explicit StringParser( const QString& input ) : input( input ) {}
        Expression parseExpression();

    private:
        QString parseToken();
        Expression parseSimpleExpression();
        Expression parseBinaryExpression( const int minPriority );

    public slots:
    private slots:

    };

    int getPriority( const QString& token );

    double eval( const Expression& e );

} // parser namespace


#endif // STRINGPARSER_H
